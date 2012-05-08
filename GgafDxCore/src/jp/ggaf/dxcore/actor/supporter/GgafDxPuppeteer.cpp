#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;

GgafDxPuppeteer::GgafDxPuppeteer(GgafDxD3DXAniMeshActor* prm_pPuppet) : GgafObject() {
    _pPuppet = prm_pPuppet;
    _pModel = (GgafDxD3DXAniMeshModel*)_pPuppet->_pModel;
    _num_perform = 0;
    _paPerformances = NULL;
    _pAc = NULL;
    //操り棒情報初期化
    //左手の操り棒
    _aStick[GgafDxPuppeteerStick::LEFT_HAND]._no = 0;
    _aStick[GgafDxPuppeteerStick::LEFT_HAND]._pPerformance = NULL;
    //右手の操り棒
    _aStick[GgafDxPuppeteerStick::RIGHT_HAND]._no = 1;
    _aStick[GgafDxPuppeteerStick::RIGHT_HAND]._pPerformance = NULL;
#ifdef MY_DEBUG
    if (!_pModel->_pAcBase) {
        throwGgafCriticalException("GgafDxPuppeteer::GgafDxPuppeteer アニメーションコントローラーが存在しません");
    }
#endif
    HRESULT hr = _pModel->_pAcBase->CloneAnimationController(
                                        _pModel->_pAcBase->GetMaxNumAnimationOutputs(),
                                        _pModel->_pAcBase->GetMaxNumAnimationSets(),
                                        _pModel->_pAcBase->GetMaxNumTracks(),
                                        _pModel->_pAcBase->GetMaxNumEvents(),
                                        &_pAc);
    checkDxException(hr, D3D_OK, "GgafDxPuppeteer::GgafDxPuppeteer() アニメーションコントローラーのクローンに失敗しました。name="<<_pPuppet->getName());
    _num_perform = _pAc->GetMaxNumAnimationSets();
#ifdef MY_DEBUG
    if (_pAc->GetMaxNumTracks() < 2) {
        throwGgafCriticalException("GgafDxPuppeteer::GgafDxPuppeteer()  アニメーショントラックが少なくとも2つ必要です。ご使用のビデオカードではトラック機能がありません。");
        _paPerformances = NULL;
        return;
    }
#endif
    _TRACE_("_pAc->GetMaxNumTracks()="<<_pAc->GetMaxNumTracks());
    _TRACE_("_pAc->GetMaxNumAnimationSets()="<<_pAc->GetMaxNumAnimationSets());
    //int x = 'o'  ^0^  -~-  -0-  ~-~  +0+  0-0  *0*  0*0;

    //モーション情報初期化
    _paPerformances = NEW Performance[_num_perform];
    for (UINT i = 0; i < _num_perform; i++) {
        hr = _pAc->GetAnimationSet(i, &(_paPerformances[i]._pAnimationSet)); //アニメーションセット保持
        checkDxException(hr, D3D_OK, "失敗しました。");
        _paPerformances[i]._time_of_one_loop   = _paPerformances[i]._pAnimationSet->GetPeriod();
//        _paPerformances[i]._local_time         = 0.0;
//        _paPerformances[i]._target_loop        = -1;
//        _paPerformances[i]._target_speed       = 1.0;
//        _paPerformances[i]._speed              = 1.0;
//        _paPerformances[i]._inc_speed          = 0.0;
//        _paPerformances[i]._is_shifting_speed  = false;
//        _paPerformances[i]._target_weight      = 1.0;
//        _paPerformances[i]._weight             = 1.0;
//        _paPerformances[i]._inc_weight         = 0.0;
//        _paPerformances[i]._is_shifting_weight = false;
//        _paPerformances[i]._method             = PLAY_LOOPING;
    }

    //グローバル時間を0にする
    hr = _pAc->ResetTime();
    checkDxException(hr, D3D_OK, "失敗しました。");

    //トラック初期設定
    //トラック０
    int tno = 0;
    hr = _pAc->SetTrackEnable(tno, FALSE);
    checkDxException(hr, D3D_OK, "失敗しました。");
    hr = _pAc->SetTrackPosition(tno, 0);
    checkDxException(hr, D3D_OK, "失敗しました。");
    hr = _pAc->SetTrackSpeed(tno, 1.0f);
    checkDxException(hr, D3D_OK, "失敗しました。");
    hr = _pAc->SetTrackWeight(tno, 1.0f);
    checkDxException(hr, D3D_OK, "失敗しました。");
    //トラック１
    tno++;
    hr = _pAc->SetTrackEnable(tno, FALSE);
    checkDxException(hr, D3D_OK, "失敗しました。");
    hr = _pAc->SetTrackPosition(tno, 0);
    checkDxException(hr, D3D_OK, "失敗しました。");
    hr = _pAc->SetTrackSpeed(tno, 1.0f);
    checkDxException(hr, D3D_OK, "失敗しました。");
    hr = _pAc->SetTrackWeight(tno, 1.0f);
    checkDxException(hr, D3D_OK, "失敗しました。");

    //0秒進める（ことによって反映させる）。
    hr = _pAc->AdvanceTime(0,NULL);
    checkDxException(hr, D3D_OK, "失敗しました。");
}

void GgafDxPuppeteer::exchangPerformance() {
    Performance* p2 = _aStick[RIGHT_HAND]._pPerformance;
    _aStick[RIGHT_HAND]._pPerformance = _aStick[LEFT_HAND]._pPerformance;
    _aStick[LEFT_HAND]._pPerformance = p2;

    HRESULT hr;
    if (_aStick[RIGHT_HAND]._pPerformance) {
        hr = _pAc->SetTrackAnimationSet(_aStick[RIGHT_HAND]._no, _aStick[RIGHT_HAND]._pPerformance->_pAnimationSet);
        checkDxException(hr, D3D_OK, "失敗しました。");
        hr = _pAc->SetTrackEnable(_aStick[RIGHT_HAND]._no, TRUE);
        checkDxException(hr, D3D_OK, "失敗しました。");
    } else {
        hr = _pAc->SetTrackEnable(_aStick[RIGHT_HAND]._no, FALSE);
        checkDxException(hr, D3D_OK, "失敗しました。");
    }

    if (_aStick[LEFT_HAND]._pPerformance) {
        hr = _pAc->SetTrackAnimationSet(_aStick[LEFT_HAND]._no, _aStick[LEFT_HAND]._pPerformance->_pAnimationSet);
        checkDxException(hr, D3D_OK, "失敗しました。");
        hr = _pAc->SetTrackEnable(_aStick[LEFT_HAND]._no, TRUE);
        checkDxException(hr, D3D_OK, "失敗しました。");
    } else {
        hr = _pAc->SetTrackEnable(_aStick[LEFT_HAND]._no, FALSE);
        checkDxException(hr, D3D_OK, "失敗しました。");
    }

}

void GgafDxPuppeteer::play(GgafDxPuppeteerStick prm_handed,
                           UINT prm_performance_no,
                           double prm_loopnum,
                           double prm_target_speed,
                           frame prm_shift_speed_frames,
                           double prm_target_weight,
                           frame prm_shift_weight_frames,
                           GgafDxPuppeteerMethod prm_method ) {
    _aStick[prm_handed]._pPerformance = &(_paPerformances[prm_performance_no]);
    Performance* p = _aStick[prm_handed]._pPerformance;
    p->_time_of_one_loop = p->_pAnimationSet->GetPeriod();
    p->_target_loop      = prm_loopnum;

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
            p->_local_time = p->_time_of_one_loop - fmod(GgafUtil::abs(p->_local_time), p->_time_of_one_loop);
        } else {
            p->_local_time = 0.0;
        }
    } else if (prm_target_speed < 0) {
        if (p->_local_time > 0) {
            p->_local_time = fmod(p->_local_time, p->_time_of_one_loop) - p->_time_of_one_loop;
        } else if (p->_local_time < 0) {
            p->_local_time = -fmod(GgafUtil::abs(p->_local_time), p->_time_of_one_loop);
        } else {
            p->_local_time = 0.0;
        }
    } else {
        p->_local_time = 0.0;
    }

    p->_method = (prm_method == NO_CHENGE ? p->_method : prm_method);

    HRESULT hr;
    hr = _pAc->SetTrackAnimationSet(_aStick[prm_handed]._no, p->_pAnimationSet);
    checkDxException(hr, D3D_OK, "失敗しました。");
    hr = _pAc->SetTrackEnable(_aStick[prm_handed]._no, TRUE);
    checkDxException(hr, D3D_OK, "失敗しました。");
}


void GgafDxPuppeteer::behave() {
//    _advance_time_per_draw += (1.0/60.0);
    for (UINT i = 0; i < 2; i++) {
        Performance* p = _aStick[i]._pPerformance;
        if (p) {
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
            if (p->_target_loop > 0 && p->_target_loop < abs(p->_local_time) / p->_time_of_one_loop) {
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

                _aStick[i]._pPerformance = NULL;
            }
        }
    }

//    //シフト処理
//    if (_is_shifting_performance) {
//        _shifted++;
//        if (_shifted < _shift_duaration) {
//            //シフト時
//            double weight = 1.0 * _shifted / _shift_duaration;
//            HRESULT hr = _pAc->SetTrackWeight(_pStickActive->_no, weight);
//            checkDxException(hr, D3D_OK, "失敗しました。");
//            hr = _pAc->SetTrackWeight(!(_pStickActive->_no), 1.00-weight);
//            checkDxException(hr, D3D_OK, "失敗しました。");
//        } else if (_shifted == _shift_duaration) {
//            //シフト完了時
//            HRESULT hr = _pAc->SetTrackWeight(_pStickActive->_no, 1.0);
//            checkDxException(hr, D3D_OK, "失敗しました。");
//            hr = _pAc->SetTrackEnable(!(_pStickActive->_no), FALSE);
//            checkDxException(hr, D3D_OK, "失敗しました。");
//            hr = _pAc->SetTrackWeight(!(_pStickActive->_no), 1.00);
//            checkDxException(hr, D3D_OK, "失敗しました。");
//            _is_shifting_performance = false;
//        }
//    }

}

void GgafDxPuppeteer::unpause(GgafDxPuppeteerStick prm_handed) {
    if (_aStick[prm_handed]._pPerformance) {
        HRESULT hr = _pAc->SetTrackEnable(_aStick[prm_handed]._no, TRUE);
        checkDxException(hr, D3D_OK, "失敗しました。");
    }
}

void GgafDxPuppeteer::pause(GgafDxPuppeteerStick prm_handed) {
    if (_aStick[prm_handed]._pPerformance) {
        HRESULT hr = _pAc->SetTrackEnable(_aStick[prm_handed]._no, FALSE);
        checkDxException(hr, D3D_OK, "失敗しました。");
        _aStick[prm_handed]._pPerformance = NULL;
    }
}

void GgafDxPuppeteer::stop() {
    HRESULT hr;
    //トラック０
    int tno = 0;
    hr = _pAc->SetTrackEnable(tno, FALSE);
    checkDxException(hr, D3D_OK, "失敗しました。");
    hr = _pAc->SetTrackPosition(tno, 0);
    checkDxException(hr, D3D_OK, "失敗しました。");
    hr = _pAc->SetTrackSpeed(tno, 1.0f);
    checkDxException(hr, D3D_OK, "失敗しました。");
    hr = _pAc->SetTrackWeight(tno, 1.00);
    checkDxException(hr, D3D_OK, "失敗しました。");
    //トラック１
    tno++;
    hr = _pAc->SetTrackEnable(tno, FALSE);
    checkDxException(hr, D3D_OK, "失敗しました。");
    hr = _pAc->SetTrackPosition(tno, 0);
    checkDxException(hr, D3D_OK, "失敗しました。");
    hr = _pAc->SetTrackSpeed(tno, 1.0f);
    checkDxException(hr, D3D_OK, "失敗しました。");
    hr = _pAc->SetTrackWeight(tno, 1.00);
    checkDxException(hr, D3D_OK, "失敗しました。");
    //0秒進める（ことによって反映させる）。
    hr = _pAc->AdvanceTime(0,NULL);
    checkDxException(hr, D3D_OK, "失敗しました。");
}


void GgafDxPuppeteer::work() {
    //アニメーションを進める。
    for (UINT i = 0; i < 2; i++) {
        Performance* p = _aStick[i]._pPerformance;
        if (p) {
            HRESULT hr = _pAc->SetTrackPosition(i, p->_local_time); //トラックローカル時間
            checkDxException(hr, D3D_OK, "失敗しました。");
        }
    }

    HRESULT hr = _pAc->AdvanceTime(0, NULL );
    checkDxException(hr, D3D_OK, "失敗しました。");
//    _advance_time_per_draw = 0; //リセット
    //モデルのワールド変換行列更新
    _pModel->_stackWorldMat.SetWorldMatrix(&(_pPuppet->_matWorld));
    _pModel->_stackWorldMat.UpdateFrame(_pModel->_pFR);
}

GgafDxPuppeteer::~GgafDxPuppeteer() {
    DELETEARR_IMPOSSIBLE_NULL(_paPerformances);
}

