#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;

GgafDx9Puppeteer::GgafDx9Puppeteer(GgafDx9D3DXAniMeshActor* prm_pPuppet) : GgafObject() {
    _pPuppet = prm_pPuppet;
    _pModel = (GgafDx9D3DXAniMeshModel*)_pPuppet->_pGgafDx9Model;
    HRESULT hr = _pModel->_pAcBase->CloneAnimationController(
                                        _pModel->_pAcBase->GetMaxNumAnimationOutputs(),
                                        _pModel->_pAcBase->GetMaxNumAnimationSets(),
                                        _pModel->_pAcBase->GetMaxNumTracks(),
                                        _pModel->_pAcBase->GetMaxNumEvents(),
                                        &_pAc);
    checkDxException(hr, D3D_OK, "GgafDx9Puppeteer::GgafDx9Puppeteer() アニメーションコントローラーのクローンに失敗しました。name="<<_pPuppet->getName());
    _num_tricks = _pAc->GetMaxNumAnimationSets();
    if (_pAc->GetMaxNumTracks() < 2) {
    throwGgafCriticalException("GgafDx9Puppeteer アニメーショントラックは少なくとも2つ必要です。");
    }
    _TRACE_("_pAc->GetMaxNumTracks()="<<_pAc->GetMaxNumTracks());
    _TRACE_("_pAc->GetMaxNumAnimationSets()="<<_pAc->GetMaxNumAnimationSets());

//    _advance_time_per_frame = 1.0 / 60.0; //60分の1秒
    _advance_time_per_draw = 0.0;

    //モーション初期化
    _paPerformances = NEW Performance[_num_tricks];
    for (UINT i = 0; i < _num_tricks; i++) {
        hr = _pAc->GetAnimationSet(i, &(_paPerformances[i]._pAnimationSet)); //アニメーションセット保持
        checkDxException(hr, D3D_OK, "失敗しました。");
        _paPerformances[i]._is_playing = false;
        _paPerformances[i]._method = NO_MOTION;
        _paPerformances[i]._speed = 1.0;
        _paPerformances[i]._weight = 1.0;
        _paPerformances[i]._target_time = 0.0;
        _paPerformances[i]._total_time = _paPerformances[i]._pAnimationSet->GetPeriod();
//        _paPerformances[i]._one_loop_time = _paPerformances[i]._total_time * _paPerformances[i]._speed ;
//        _paPerformances[i]._velo_time = (1.0 / 60.0) * _paPerformances[i]._speed;
        _paPerformances[i]._local_time = 0.0;

    }

    hr = _pAc->ResetTime();//グローバル時間を0にする
    checkDxException(hr, D3D_OK, "失敗しました。");

    //トラック初期化
    for (UINT i = 0; i < 2; i++) {
        hr = _pAc->SetTrackEnable(i, FALSE);
        checkDxException(hr, D3D_OK, "失敗しました。");
        hr = _pAc->SetTrackPosition(i, 0); //トラックローカル時間を0にする
        checkDxException(hr, D3D_OK, "失敗しました。");
        hr = _pAc->SetTrackSpeed(i, 1.0f);  //トラックスピードを設定。
        checkDxException(hr, D3D_OK, "失敗しました。");
        hr = _pAc->SetTrackWeight(i, 1.00);
        checkDxException(hr, D3D_OK, "失敗しました。");
    }

    hr = _pAc->AdvanceTime(0,NULL);//0秒進める（それを反映させる）。
    checkDxException(hr, D3D_OK, "失敗しました。");

//    for (DWORD i = 0; i < (DWORD)_pAc->GetMaxNumTracks(); i++) {
//        hr = _pAc->SetTrackEnable(i, FALSE);
//        checkDxException(hr, D3D_OK, "失敗しました。");
//    }
    _aStick[LEFT_HANDED]._no = 0;
    _aStick[LEFT_HANDED]._pPerformance = NULL;
    _aStick[RIGHT_HANDED]._no = 0;
    _aStick[RIGHT_HANDED]._pPerformance = NULL;
    _pStickActive = &_aStick[LEFT_HANDED];
}

void GgafDx9Puppeteer::play(UINT performance_no, GgafDx9MotionMethod method) {
    _paPerformances[performance_no]._is_playing = true;
    _paPerformances[performance_no]._method = method;
    _pStickActive->_pPerformance = &(_paPerformances[performance_no]);

    HRESULT hr = _pAc->SetTrackAnimationSet(_pStickActive->_no, _pStickActive->_pPerformance->_pAnimationSet);//motion_id番のアニメーションセットをトラック0番にセット
    checkDxException(hr, D3D_OK, "失敗しました。");
    hr = _pAc->SetTrackEnable(_pStickActive->_no, TRUE);
    checkDxException(hr, D3D_OK, "失敗しました。");
}
void GgafDx9Puppeteer::play() {
    HRESULT hr = _pAc->SetTrackEnable(_pStickActive->_no, TRUE);
    checkDxException(hr, D3D_OK, "失敗しました。");
}
void GgafDx9Puppeteer::stop() {
    HRESULT hr = _pAc->SetTrackEnable(_pStickActive->_no, FALSE);
    checkDxException(hr, D3D_OK, "失敗しました。");
}

void GgafDx9Puppeteer::behave() {
    _advance_time_per_draw += (1.0/60.0);
    for (UINT i = 0; i < 2; i++) {
        if (_aStick[i]._pPerformance && _aStick[i]._pPerformance->_is_playing) {
            _aStick[i]._pPerformance->_local_time += ((1.0 / 60.0) * _paPerformances[i]._speed);
        }
    }
}
void GgafDx9Puppeteer::work() {
    //アニメーションを進める。
    for (UINT i = 0; i < 2; i++) {
        if (_aStick[i]._pPerformance) {
            HRESULT hr = _pAc->SetTrackPosition(i, _aStick[i]._pPerformance->_local_time); //トラックローカル時間
            checkDxException(hr, D3D_OK, "失敗しました。");
        }
    }

    HRESULT hr = _pAc->AdvanceTime(_advance_time_per_draw, NULL );
    checkDxException(hr, D3D_OK, "失敗しました。");
    _advance_time_per_draw = 0; //リセット
    //モデルのワールド変換行列更新
    _pModel->_stackWorldMat.SetWorldMatrix(&(_pPuppet->_matWorld));
    _pModel->_stackWorldMat.UpdateFrame(_pModel->_pFR);
}

GgafDx9Puppeteer::~GgafDx9Puppeteer() {
    DELETEARR_IMPOSSIBLE_NULL(_paPerformances);
}





