#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;

DWORD GgafDx9D3DXAniMeshActor::FVF = (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1);
GgafDx9D3DXAniMeshActor::GgafDx9D3DXAniMeshActor(const char* prm_name,
                                                 const char* prm_model_id,
                                                 const char* prm_effect_id,
                                                 const char* prm_technique,
                                                 GgafDx9Checker* prm_pChecker) :

                                           GgafDx9DrawableActor(prm_name,
                                                                prm_model_id,
                                                                "A",
                                                                prm_effect_id,
                                                                "A",
                                                                prm_technique,
                                                                prm_pChecker) {
    _obj_class |= Obj_GgafDx9D3DXAniMeshActor;
    _class_name = "GgafDx9D3DXAniMeshActor";
    _pD3DXAniMeshModel = (GgafDx9D3DXAniMeshModel*)_pGgafDx9Model;
    _pD3DXAniMeshEffect = (GgafDx9D3DXAniMeshEffect*)_pGgafDx9Effect;
    _pFunc_calcRotMvWorldMatrix = GgafDx9Util::setWorldMatrix_RxRzRyMv;
    _pPuppeteer = NEW GgafDx9Puppeteer(this);
//
//    LPD3DXANIMATIONSET pAnimationSet0;
//    hr = _pAc->GetAnimationSet(0, &pAnimationSet0); //ID0番のアニメーションセット取得
//    checkDxException(hr, D3D_OK, "失敗しました。");
//    LPD3DXANIMATIONSET pAnimationSet1;
//    hr = _pAc->GetAnimationSet(2, &pAnimationSet1); //ID1番のアニメーションセット取得
//    checkDxException(hr, D3D_OK, "失敗しました。");
//    LPD3DXANIMATIONSET pAnimationSet2;
//    hr = _pAc->GetAnimationSet(2, &pAnimationSet2); //ID2番のアニメーションセット取得
//    checkDxException(hr, D3D_OK, "失敗しました。");
//    LPD3DXANIMATIONSET pAnimationSet4;
//    hr = _pAc->GetAnimationSet(2, &pAnimationSet4); //ID2番のアニメーションセット取得
//    checkDxException(hr, D3D_OK, "失敗しました。");
//
//    hr = _pAc->SetTrackAnimationSet(0, pAnimationSet0);//ID0番のアニメーションセットをトラック0番にセット（デフォルトでこうなるはず）
//    checkDxException(hr, D3D_OK, "失敗しました。");
//    hr = _pAc->SetTrackAnimationSet(1, pAnimationSet0);//ID1番のアニメーションセットをトラック1番にセット（デフォルトでこうなるはず）
//    checkDxException(hr, D3D_OK, "失敗しました。");
////    hr = _pAc->SetTrackAnimationSet(2, pAnimationSet2);//ID2番のアニメーションセットをトラック2番にセット（デフォルトでこうなるはず）
////    checkDxException(hr, D3D_OK, "失敗しました。");
//
//    hr = _pAc->ResetTime();//グローバル時間を0にする
//    checkDxException(hr, D3D_OK, "失敗しました。");
//
//    hr = _pAc->SetTrackPosition(0,0);//トラック0(=ID0番)のローカル時間を0にする
//    checkDxException(hr, D3D_OK, "失敗しました。");
//    hr = _pAc->SetTrackPosition(1,0);//トラック1(=ID1番)のローカル時間を0にする
//    checkDxException(hr, D3D_OK, "失敗しました。");
////    hr = _pAc->SetTrackPosition(2,0);//トラック2(=ID2番)のローカル時間を0にする
////    checkDxException(hr, D3D_OK, "失敗しました。");
//
//    hr = _pAc->SetTrackEnable(0,TRUE );//トラック0(=ID0番)を有効
//    checkDxException(hr, D3D_OK, "失敗しました。");
//    hr = _pAc->SetTrackEnable(1,TRUE );//トラック1(=ID1番)を有効
//    checkDxException(hr, D3D_OK, "失敗しました。");
////    hr = _pAc->SetTrackEnable(2,TRUE );//トラック2(=ID2番)を有効
////    checkDxException(hr, D3D_OK, "失敗しました。");
//
//    hr = _pAc->SetTrackWeight(0, 1.00);
//    checkDxException(hr, D3D_OK, "失敗しました。");
//    hr = _pAc->SetTrackWeight(1, 1.00);
//    checkDxException(hr, D3D_OK, "失敗しました。");
////    hr = _pAc->SetTrackWeight(2, 1.00);
////    checkDxException(hr, D3D_OK, "失敗しました。");
//
//    hr = _pAc->AdvanceTime(0,NULL);//0秒進める（それを反映させる）。
//    checkDxException(hr, D3D_OK, "失敗しました。");
//
//    //ID0番(=トラック0)のアニメーションセットの開始～終了までの時間(秒)
////    _advance_time_per_frame =  pAnimationSet0->GetPeriod()/60.0;
////    double time_period0 = pAnimationSet0->GetPeriod();
////    _TRACE_("time_period0="<<time_period0);
////    double time_set0 = time_period0 / (60.0 / _pD3DXAniMeshModel->_anim_ticks_per_second); //そのアニメーションにかかる秒数
//    //ID0番(=トラック0)の SetTrackSpeed が 1.0 固定ならば advanceTimePerFrame は time_period0 / (time_set0 * 60.0)
////    _advance_time_per_frame0 = time_set0 / time_set0*60.0 ; //トラック0番のアニメーションを60分割時間を求める、つまり１ループ1秒にするための時間
//    hr = _pAc->SetTrackSpeed(0, 1.0f);  //トラック0(=ID0番)のスピードを設定。
//    checkDxException(hr, D3D_OK, "失敗しました。");
//    hr = _pAc->SetTrackSpeed(1, 1.0f);
//    checkDxException(hr, D3D_OK, "失敗しました。");
////    hr = _pAc->SetTrackSpeed(2, 1.0f);
////    checkDxException(hr, D3D_OK, "失敗しました。");










    // _pAc->GetMaxNumAnimationSets()

//    if (SUCCEEDED(pAnimController->GetAnimationSetByName(szAnimSetName, &pAnimSet))) {
//        if (SUCCEEDED(pAnimSet->QueryInterface(IID_ID3DXKeyframedAnimationSet, (LPVOID*)&pKeyFramedAnimSet))) {
//            UINT dwNumAnimations = pKeyFramedAnimSet->GetNumAnimations();
//            for (UINT i = 0; i < dwNumAnimations; i++)
//                HRESULT hr = pKeyFramedAnimSet->UnregisterAnimation(i);
//        }
//        pAnimSet->Release();
//    }



}

void GgafDx9D3DXAniMeshActor::setAlpha(float prm_fAlpha) {
    _fAlpha = prm_fAlpha;
    //GgafDx9D3DXAniMeshActorはメッシュαも設定（シェーダーで参照するため）
//    for (DWORD i = 0; i < _pD3DXAniMeshModel->_dwNumMaterials; i++) {
//        _paD3DMaterial9[i].Ambient.a = _fAlpha;
//        _paD3DMaterial9[i].Diffuse.a = _fAlpha;
//    }
}

void GgafDx9D3DXAniMeshActor::addAlpha(float prm_fAlpha) {
    _fAlpha += prm_fAlpha;
    //GgafDx9D3DXAniMeshActorはメッシュαも設定（シェーダーで参照するため）
//    for (DWORD i = 0; i < _pD3DXAniMeshModel->_dwNumMaterials; i++) {
//        _paD3DMaterial9[i].Ambient.a = _fAlpha;
//        _paD3DMaterial9[i].Diffuse.a = _fAlpha;
//    }
}

void GgafDx9D3DXAniMeshActor::processDraw() {
    ID3DXEffect* pID3DXEffect = _pD3DXAniMeshEffect->_pID3DXEffect;
    HRESULT hr;
    //ビュー変換行列
//    hr = pID3DXEffect->SetMatrix(_pD3DXAniMeshEffect->_h_matView, &P_CAM->_vMatrixView );
//    checkDxException(hr, D3D_OK, "GgafDx9D3DXAniMeshActor::processDraw() SetMatrix(g_matView) に失敗しました。");
    //(*_pFunc_calcRotMvWorldMatrix)(this, _matWorld);

    //hr = pID3DXEffect->SetMatrix(_pD3DXAniMeshEffect->_h_matWorld, &_matWorld );
    //checkDxException(hr, D3D_OK, "GgafDx9D3DXAniMeshActor::processDraw() SetMatrix(g_matWorld) に失敗しました。");
    //SetMatrixはモデルでせざるをえない

    // Zバッファを有効に
    //GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE);
    // Zバッファ書き込み可
    //GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

//    HRESULT hr = _pAc->SetTrackPosition(0,_track0time);//トラック0(=ID0番)のローカル時間を0にする
//    checkDxException(hr, D3D_OK, "失敗しました。");

    _pD3DXAniMeshModel->draw(this);

    // Zバッファを無効に
    //GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_ZENABLE, D3DZB_FALSE);
    // Zバッファ書き込み不可
    //GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_ZWRITEENABLE, FALSE );

}

GgafDx9D3DXAniMeshActor::~GgafDx9D3DXAniMeshActor() {
    DELETE_IMPOSSIBLE_NULL(_pPuppeteer);
}
