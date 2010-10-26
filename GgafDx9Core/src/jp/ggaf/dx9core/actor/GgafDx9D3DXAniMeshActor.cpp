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
    static ID3DXEffect* pID3DXEffect;
    pID3DXEffect = _pD3DXAniMeshEffect->_pID3DXEffect;
    HRESULT hr;
    //ビュー変換行列
    hr = pID3DXEffect->SetMatrix(_pD3DXAniMeshEffect->_h_matView, &pCAM->_vMatrixView );
    checkDxException(hr, D3D_OK, "GgafDx9D3DXAniMeshActor::processDraw() SetMatrix(g_matView) に失敗しました。");
    //(*_pFunc_calcRotMvWorldMatrix)(this, _matWorld);

    //hr = pID3DXEffect->SetMatrix(_pD3DXAniMeshEffect->_h_matWorld, &_matWorld );
    //checkDxException(hr, D3D_OK, "GgafDx9D3DXAniMeshActor::processDraw() SetMatrix(g_matWorld) に失敗しました。");
    //SetMatrixはモデルでせざるをえない

    // Zバッファを有効に
    //GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE);
    // Zバッファ書き込み可
    //GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

    _pD3DXAniMeshModel->draw(this);

    // Zバッファを無効に
    //GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_ZENABLE, D3DZB_FALSE);
    // Zバッファ書き込み不可
    //GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_ZWRITEENABLE, FALSE );

}

GgafDx9D3DXAniMeshActor::~GgafDx9D3DXAniMeshActor() {
}
