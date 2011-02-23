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
    _num_animation_set = _pAc->GetMaxNumAnimationSets();
    _num_tracks = _pAc->GetMaxNumTracks();
    _TRACE_("_pAc->GetMaxNumTracks()="<<_pAc->GetMaxNumTracks());
    _TRACE_("_pAc->GetMaxNumAnimationSets()="<<_pAc->GetMaxNumAnimationSets());

//    _advance_time_per_frame = 1.0 / 60.0; //60分の1秒
    _advance_time_per_draw = 0.0;


    _papAnimationSet = NEW LPD3DXANIMATIONSET[_num_animation_set];
    _pa_as_anime_time = NEW double[_num_animation_set];
    _pa_as_anime_speed = NEW float[_num_animation_set];
    _pa_as_weight = NEW float[_num_animation_set];
    for (UINT i = 0; i < _num_animation_set; i++) {
        hr = _pAc->GetAnimationSet(i, &(_papAnimationSet[i])); //アニメーションセット保持
        checkDxException(hr, D3D_OK, "失敗しました。");
        _pa_as_anime_time[i] = 0.0;
        _pa_as_anime_speed[i] = 1.0;
        _pa_as_weight[i] = 1.0;
    }

    hr = _pAc->ResetTime();//グローバル時間を0にする
    checkDxException(hr, D3D_OK, "失敗しました。");
    //初期は静止
    for (UINT i = 0; i < _num_tracks; i++) {
        hr = _pAc->SetTrackEnable(i, TRUE);
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

    for (DWORD i = 0; i < (DWORD)_pAc->GetMaxNumTracks(); i++) {
        hr = _pAc->SetTrackEnable(i, FALSE);
        checkDxException(hr, D3D_OK, "失敗しました。");
    }

    _hand = 0;

}
void GgafDx9Puppeteer::play(UINT anim_set_id) {
    HRESULT hr = _pAc->SetTrackAnimationSet(_hand, _papAnimationSet[anim_set_id]);//anim_set_id番のアニメーションセットをトラック0番にセット
    checkDxException(hr, D3D_OK, "失敗しました。");
    hr = _pAc->SetTrackEnable(_hand, TRUE);
    checkDxException(hr, D3D_OK, "失敗しました。");
}
void GgafDx9Puppeteer::play() {
    HRESULT hr = _pAc->SetTrackEnable(_hand, TRUE);
    checkDxException(hr, D3D_OK, "失敗しました。");
}
void GgafDx9Puppeteer::stop() {
    HRESULT hr = _pAc->SetTrackEnable(_hand, FALSE);
    checkDxException(hr, D3D_OK, "失敗しました。");
}

void GgafDx9Puppeteer::behave() {
    _advance_time_per_draw += (1.0/60.0);
}
void GgafDx9Puppeteer::work() {
    //アニメーションを進める。
    HRESULT hr = _pAc->AdvanceTime(_advance_time_per_draw, NULL );
    checkDxException(hr, D3D_OK, "失敗しました。");
    _advance_time_per_draw = 0; //リセット
    //モデルのワールド変換行列更新
    _pModel->_stackWorldMat.SetWorldMatrix(&(_pPuppet->_matWorld));
    _pModel->_stackWorldMat.UpdateFrame(_pModel->_pFR);
}

GgafDx9Puppeteer::~GgafDx9Puppeteer() {
}





