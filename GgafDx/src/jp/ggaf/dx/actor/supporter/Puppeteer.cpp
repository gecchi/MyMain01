#include "jp/ggaf/dx/actor/supporter/Puppeteer.h"

#include "jp/ggaf/dx/exception/CriticalException.h"
#include "jp/ggaf/dx/model/BoneAniMeshModel.h"
#include "jp/ggaf/dx/actor/BoneAniMeshActor.h"

using namespace GgafDx;


Puppeteer::Performance::Performance() {
    _pAnimationSet = nullptr;
    _animation_set_index = 0;
    _one_loop_frames    = 60;
    _local_time._t_value = 0.0;
//    _local_time_inc = 0.0;
    _target_loop        = -1;
    _loop_count         = 0;
    _period             = 1.0;
    _weight._t_value = 1.0;
    _method             = NO_CHENGE;
}
void Puppeteer::Performance::setAnimationSet(LPD3DXANIMATIONSET prm_pAnimationSet, UINT prm_animation_set_index) {
    _pAnimationSet = prm_pAnimationSet;
    _animation_set_index = prm_animation_set_index;
    _period = _pAnimationSet->GetPeriod();
}
Puppeteer::Performance::~Performance() {
}



Puppeteer::Puppeteer(ID3DXAnimationController* prm_pAc_cloned) : GgafCore::Object() {
    _num_perform = 0;
    _paPerformances = nullptr;
    _pAc = prm_pAc_cloned;
//    _track_speed = prm_track_speed;
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
        _paPerformances[i]._period = _paPerformances[i]._pAnimationSet->GetPeriod();
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
//        _paPerformances[i]._period = _paPerformances[i]._pAnimationSet->GetPeriod();
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
          frame prm_one_loop_frames,
          double prm_loopnum,
          PuppeteerMethod prm_method) {
    if (prm_performance_no > _num_perform-1) {
        throwCriticalException("Puppeteer::play() アニメIDが範囲外です。prm_performance_no="<<prm_performance_no);
    }
    Performance* p = &(_paPerformances[prm_performance_no]);
    p->_one_loop_frames = prm_one_loop_frames;
//    p->_local_time._t_value = 0.0;
//    p->_local_time_inc =  p->_period / p->_one_loop_frames;
    p->_local_time.accelerateByDt(
            p->_period,           //VAL_TYPE prm_target_value_distance,
            p->_one_loop_frames, //frame prm_frame_of_target,
            0.4, 0.6,            //double prm_p1, double prm_p2,
            0.0,                  //VAL_TYPE prm_end_velo,
            true                  //bool prm_zero_acc_end_flg
    );




    p->_target_loop = prm_loopnum;
    p->_loop_count = 0;
    p->_method     = prm_method;
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
//                p->_local_time._t_value += (p->_local_time_inc);

                if (p->_local_time.isAccelerating()) {
                    p->_local_time.behave();
                } else {
                     p->_method = NO_CHENGE;
                }

//                //ループ完判定
//                if (p->_target_loop > 0 && p->_target_loop < ABS(p->_local_time._t_value) / p->_period) {
//                    if (p->_local_time._t_value > 0) {
//                        //理想値に補正
//                        p->_local_time._t_value = p->_target_loop * p->_period;
//                    } else {
//                        //理想値に補正
//                        p->_local_time._t_value = - (p->_target_loop * p->_period);
//                    }
//                    p->_method = NO_CHENGE;
//                }
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
            hr = pAc->SetTrackPosition(tno, pPerformance->_local_time._t_value);
            checkDxException(hr, D3D_OK, "失敗しました。");
            hr = pAc->SetTrackSpeed(tno, pPerformance->_period);
            checkDxException(hr, D3D_OK, "失敗しました。");
            hr = pAc->SetTrackWeight(tno, pPerformance->_weight._t_value);
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

