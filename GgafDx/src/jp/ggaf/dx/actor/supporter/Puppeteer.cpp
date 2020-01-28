#include "jp/ggaf/dx/actor/supporter/Puppeteer.h"

#include "jp/ggaf/dx/exception/CriticalException.h"
#include "jp/ggaf/dx/model/BoneAniMeshModel.h"
#include "jp/ggaf/dx/actor/BoneAniMeshActor.h"


using namespace GgafDx;

Puppeteer::Puppeteer(ID3DXAnimationController* prm_pAc_cloned, FLOAT prm_track_speed) : GgafCore::Object() {
    _num_perform = 0;
    _paPerformances = nullptr;
    _pAc = prm_pAc_cloned;
    _track_speed = prm_track_speed;
    HRESULT hr;
    _num_perform = _pAc->GetMaxNumAnimationSets();
#ifdef MY_DEBUG
    if (_pAc->GetMaxNumTracks() < 2) {
        throwCriticalException("アニメーショントラックが少なくとも2つ必要です。ご使用のビデオカードではトラック機能がありません。");
        _paPerformances = nullptr;
        return;
    }
#endif
    //int x = 'o'  ^0^  -~-  -0-  ~-~  +0+  0-0  *0*  0*0;


    //モーション情報初期化
    _paPerformances = NEW Performance[_num_perform];
    for (UINT i = 0; i < _num_perform; i++) {
        LPD3DXANIMATIONSET pAnimationSet;
        hr = _pAc->GetAnimationSet(i, &(pAnimationSet)); //アニメーションセット保持
        _paPerformances[i].setAnimationSet(pAnimationSet, i);
        checkDxException(hr, D3D_OK, "失敗しました。");
        _paPerformances[i]._time_of_one_loop = _paPerformances[i]._pAnimationSet->GetPeriod();
    }

    //グローバル時間を0にする
    hr = _pAc->ResetTime();
    checkDxException(hr, D3D_OK, "失敗しました。");

    //Stick初期化(トラック初期設定)
    _aStick[LEFT_HAND]._tno = 0;
    _aStick[LEFT_HAND]._enable_motion_blend = TRUE;
    _aStick[LEFT_HAND]._pPerformance = &(_paPerformances[0]);

    _aStick[RIGHT_HAND]._tno = 1;
    _aStick[RIGHT_HAND]._enable_motion_blend = FALSE;
    _aStick[RIGHT_HAND]._pPerformance = nullptr;

//    int as = _pAc->GetMaxNumAnimationSets();
//    for (int i = 0; i < as; i++) {
//        ID3DXAnimationSet* pAs = _paPerformances[i]._pAnimationSet;
//        _TRACE_("["<<i<<"] GetName="<<pAs->GetName());
//        int numAnims = pAs->GetNumAnimations();
//        for (int j = 0; j < numAnims; ++j) {
//            LPCSTR name;
//            hr = pAs->GetAnimationNameByIndex(j, &name);
//            checkDxException(hr, D3D_OK, "失敗しましと。");
//            _TRACE_("["<<i<<"] GetAnimationNameByIndex("<<j<<")="<<name);
//        }
//    }
}

//void Puppeteer::restore(ID3DXAnimationController* prm_pAc_cloned) {
//    _pAc = prm_pAc_cloned;
//    HRESULT hr;
//    for (UINT i = 0; i < _num_perform; i++) {
//        LPD3DXANIMATIONSET pAnimationSet;
//        hr = _pAc->GetAnimationSet(i, &(pAnimationSet)); //アニメーションセット保持
//        _paPerformances[i].setAnimationSet(pAnimationSet, i);
//        checkDxException(hr, D3D_OK, "失敗しました。");
//        _paPerformances[i]._time_of_one_loop = _paPerformances[i]._pAnimationSet->GetPeriod();
//    }
//}

void Puppeteer::exchangPerformance() {
    Performance* p2 = _aStick[RIGHT_HAND]._pPerformance;
    _aStick[RIGHT_HAND]._pPerformance = _aStick[LEFT_HAND]._pPerformance;
    _aStick[LEFT_HAND]._pPerformance = p2;

    HRESULT hr;
    if (_aStick[RIGHT_HAND]._pPerformance) {
        hr = _pAc->SetTrackAnimationSet(_aStick[RIGHT_HAND]._tno, _aStick[RIGHT_HAND]._pPerformance->_pAnimationSet);
        checkDxException(hr, D3D_OK, "失敗しました。");
        hr = _pAc->SetTrackEnable(_aStick[RIGHT_HAND]._tno, TRUE);
        checkDxException(hr, D3D_OK, "失敗しました。");
    } else {
        hr = _pAc->SetTrackEnable(_aStick[RIGHT_HAND]._tno, FALSE);
        checkDxException(hr, D3D_OK, "失敗しました。");
    }

    if (_aStick[LEFT_HAND]._pPerformance) {
        hr = _pAc->SetTrackAnimationSet(_aStick[LEFT_HAND]._tno, _aStick[LEFT_HAND]._pPerformance->_pAnimationSet);
        checkDxException(hr, D3D_OK, "失敗しました。");
        hr = _pAc->SetTrackEnable(_aStick[LEFT_HAND]._tno, TRUE);
        checkDxException(hr, D3D_OK, "失敗しました。");
    } else {
        hr = _pAc->SetTrackEnable(_aStick[LEFT_HAND]._tno, FALSE);
        checkDxException(hr, D3D_OK, "失敗しました。");
    }

}

void Puppeteer::play(PuppeteerStick prm_handed,
                     UINT prm_performance_no,
                     double prm_loopnum,
                     double prm_target_speed,
                     frame prm_shift_speed_frames,
                     double prm_target_weight,
                     frame prm_shift_weight_frames,
                     PuppeteerMethod prm_method ) {
    if (prm_performance_no > _num_perform-1) {
        throwCriticalException("Puppeteer::play() アニメIDが範囲外です。prm_performance_no="<<prm_performance_no);
    }
    Performance* p = &(_paPerformances[prm_performance_no]);
    p->_time_of_one_loop = p->_pAnimationSet->GetPeriod();
    p->_target_loop      = prm_loopnum;
    p->_method           = prm_method;
    if (prm_shift_speed_frames == 0) {
        p->_speed              = prm_target_speed;
        p->_inc_speed          = 0;
        p->_is_shifting_speed  = false;
        p->_target_speed       = prm_target_speed;
    } else {
        p->_inc_speed          = (prm_target_speed - p->_speed) / prm_shift_speed_frames;
        p->_is_shifting_speed  = true;
        p->_target_speed       = prm_target_speed;
    }
    if (prm_shift_weight_frames == 0) {
        p->_weight             = prm_target_weight;
        p->_inc_weight         = 0;
        p->_is_shifting_weight = false;
        p->_target_weight      = prm_target_weight;
    } else {
        p->_inc_weight         = (prm_target_weight - p->_weight) / prm_shift_weight_frames;
        p->_is_shifting_weight = true;
        p->_target_weight      = prm_target_weight;
    }

    //ローカル時間を単純化する。
    //target_speed が正の場合            0 <= _local_time <  1ループ時間 の範囲に、
    //target_speed が負の場合 -1ループ時間 <  _local_time <= 0           の範囲に、落とし込む
    if (prm_target_speed > 0) {
        if (p->_local_time > 0) {
            p->_local_time = fmod(p->_local_time, p->_time_of_one_loop);
        } else if (p->_local_time < 0) {
            p->_local_time = p->_time_of_one_loop - fmod(ABS(p->_local_time), p->_time_of_one_loop);
        } else {
            p->_local_time = 0.0;
        }
    } else if (prm_target_speed < 0) {
        if (p->_local_time > 0) {
            p->_local_time = fmod(p->_local_time, p->_time_of_one_loop) - p->_time_of_one_loop;
        } else if (p->_local_time < 0) {
            p->_local_time = -fmod(ABS(p->_local_time), p->_time_of_one_loop);
        } else {
            p->_local_time = 0.0;
        }
    } else {
        p->_local_time = 0.0;
    }

//    p->_method = (prm_method == NO_CHENGE ? p->_method : prm_method);
//
//    HRESULT hr;
//    hr = _pAc->SetTrackAnimationSet(_aStick[prm_handed]._tno, p->_pAnimationSet);
//    checkDxException(hr, D3D_OK, "失敗しました。");
//    hr = _pAc->SetTrackEnable(_aStick[prm_handed]._tno, TRUE);
//    checkDxException(hr, D3D_OK, "失敗しました。");
    _aStick[prm_handed]._enable_motion_blend = TRUE;
    _aStick[prm_handed]._pPerformance = p;
}


void Puppeteer::behave() {
//    _advance_time_per_draw += (1.0/60.0);
    for (UINT i = 0; i < 2; i++) {
        Performance* p = _aStick[i]._pPerformance;
        if (p) {
            if (p->_method == NO_CHENGE) {
                break;
            } else if (p->_method == PLAY_LOOPING) {
                if (p->_is_shifting_speed) {
                    if (p->_target_speed > 0 && p->_speed > p->_target_speed) {
                        p->_speed = p->_target_speed;
                        p->_is_shifting_speed = false;
                    } else if (p->_target_speed < 0 && p->_speed < p->_target_speed) {
                        p->_speed = p->_target_speed;
                        p->_is_shifting_speed = false;
                    } else {
                        p->_speed += p->_inc_speed;
                    }
                }
                if (p->_is_shifting_weight) {
                    if (p->_weight > 0 && p->_weight > p->_target_weight) {
                        p->_weight = p->_target_weight;
                        p->_is_shifting_weight = false;
                    } else if (p->_weight < 0 && p->_weight < p->_target_weight) {
                        p->_weight = p->_target_weight;
                        p->_is_shifting_weight = false;
                    } else {
                        p->_weight += p->_inc_weight;
                    }
                }
                p->_local_time += (p->_speed / 60.0);

                //ループ完判定
                if (p->_target_loop > 0 && p->_target_loop < ABS(p->_local_time) / p->_time_of_one_loop) {
                    if (p->_local_time > 0) {
                        //理想値に補正
                        p->_local_time = p->_target_loop * p->_time_of_one_loop;
                    } else {
                        //理想値に補正
                        p->_local_time = - (p->_target_loop * p->_time_of_one_loop);
                    }
                    p->_inc_speed          = 0;
                    p->_is_shifting_speed  = false;

                    p->_inc_weight         = 0;
                    p->_is_shifting_weight = false;

                    p->_method = NO_CHENGE;
                }
            } else {
                throwCriticalException("そんなメソッドはは未サポートです。 p->_method="<<p->_method);
            }
        }
    }

//    //シフト処理
//    if (_is_shifting_performance) {
//        _shifted++;
//        if (_shifted < _shift_duaration) {
//            //シフト時
//            double weight = 1.0 * _shifted / _shift_duaration;
//            HRESULT hr = _pAc->SetTrackWeight(_pStickActive->_tno, weight);
//            checkDxException(hr, D3D_OK, "失敗しました。");
//            hr = _pAc->SetTrackWeight(!(_pStickActive->_tno), 1.00-weight);
//            checkDxException(hr, D3D_OK, "失敗しました。");
//        } else if (_shifted == _shift_duaration) {
//            //シフト完了時
//            HRESULT hr = _pAc->SetTrackWeight(_pStickActive->_tno, 1.0);
//            checkDxException(hr, D3D_OK, "失敗しました。");
//            hr = _pAc->SetTrackEnable(!(_pStickActive->_tno), FALSE);
//            checkDxException(hr, D3D_OK, "失敗しました。");
//            hr = _pAc->SetTrackWeight(!(_pStickActive->_tno), 1.00);
//            checkDxException(hr, D3D_OK, "失敗しました。");
//            _is_shifting_performance = false;
//        }
//    }

}

void Puppeteer::stop() {
    for (UINT hand = 0; hand < 2; hand++) {
        Performance* p = _aStick[hand]._pPerformance;
        if (p) {
            p->_method = NO_CHENGE;
        }
    }
}

void Puppeteer::updateAnimationTrack() {
    HRESULT hr;

    ID3DXAnimationController* pAc = _pAc;
    for (UINT hand = 0; hand < 2; hand++) {
        Stick* s = &(_aStick[hand]);
        UINT tno = s->_tno; //トラック番号
        hr = pAc->SetTrackEnable(tno, s->_enable_motion_blend);
        checkDxException(hr, D3D_OK, "失敗しました。");
        Performance* pPerformance = s->_pPerformance;
        if (pPerformance) {
            hr = pAc->SetTrackAnimationSet(tno, pPerformance->_pAnimationSet);
            checkDxException(hr, D3D_OK, "失敗しました。");
            hr = pAc->SetTrackPosition(tno, pPerformance->_local_time);
            checkDxException(hr, D3D_OK, "失敗しました。");
            hr = pAc->SetTrackSpeed(tno, pPerformance->_speed * _track_speed);
            checkDxException(hr, D3D_OK, "失敗しました。");
            hr = pAc->SetTrackWeight(tno, pPerformance->_weight);
            checkDxException(hr, D3D_OK, "失敗しました。");
            _paAs[tno] = pPerformance->_pAnimationSet;
        } else {
            _paAs[tno] = nullptr;
        }
    }
    //0秒進める（ことによって反映させる）。
    hr = pAc->AdvanceTime(0, nullptr);
    checkDxException(hr, D3D_OK, "失敗しました。");
}


Puppeteer::~Puppeteer() {
    GGAF_DELETEARR(_paPerformances);
}

