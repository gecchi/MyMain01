#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;

DWORD GgafDx9DynaD3DXMeshActor::FVF = (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1);

GgafDx9DynaD3DXMeshActor::GgafDx9DynaD3DXMeshActor(const char* prm_name,
                                                   const char* prm_model_id,
                                                   const char* prm_effect_id,
                                                   const char* prm_technique,
                                                   GgafDx9Checker* prm_pChecker) :

                                                       GgafDx9DrawableActor(prm_name,
                                                                            prm_model_id,
                                                                            "d",
                                                                            prm_effect_id,
                                                                            "X",
                                                                            prm_technique,
                                                                            prm_pChecker) {
    _actor_class |= Obj_GgafDx9DynaD3DXMeshActor;
    _class_name = "GgafDx9DynaD3DXMeshActor";

    _pD3DXMeshModel = (GgafDx9D3DXMeshModel*)_pGgafDx9Model;
    _pMeshEffect = (GgafDx9MeshEffect*)_pGgafDx9Effect;
    _pFunc_calcRotMvWorldMatrix = GgafDx9Util::setWorldMatrix_RxRzRyMv;
}

void GgafDx9DynaD3DXMeshActor::processDraw() {
    static ID3DXEffect* pID3DXEffect;
    pID3DXEffect = _pMeshEffect->_pID3DXEffect;
    //(*_pFunc_calcRotMvWorldMatrix)(this, _matWorld);
    HRESULT hr;
    hr = pID3DXEffect->SetMatrix( _pMeshEffect->_h_matView, &pCAM->_vMatrixView );
    checkDxException(hr, D3D_OK, "GgafDx9DynaD3DXMeshActor::GgafDx9MeshEffect SetMatrix(g_matView) に失敗しました。");
    hr = pID3DXEffect->SetMatrix(_pMeshEffect->_h_matWorld, &_matWorld );
    checkDxException(hr, D3D_OK, "GgafDx9DynaD3DXMeshActor::processDraw() SetMatrix(g_matWorld) に失敗しました。");

    // Zバッファを有効に
    //GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE);
    // Zバッファ書き込み可
    //GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

    _pD3DXMeshModel->draw(this);

    // Zバッファを無効に
    //GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_ZENABLE, D3DZB_FALSE);
    // Zバッファ書き込み不可
    //GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_ZWRITEENABLE, FALSE );
}

void GgafDx9DynaD3DXMeshActor::setAlpha(float prm_fAlpha) {
    _fAlpha = prm_fAlpha;
    //GgafDx9DynaD3DXMeshActorはメッシュαも設定（シェーダーで参照するため）
    for (DWORD i = 0; i < _pD3DXMeshModel->_dwNumMaterials; i++) {
        _paD3DMaterial9[i].Ambient.a = _fAlpha;
        _paD3DMaterial9[i].Diffuse.a = _fAlpha;
    }
}

void GgafDx9DynaD3DXMeshActor::addAlpha(float prm_fAlpha) {
    _fAlpha += prm_fAlpha;
    //GgafDx9DynaD3DXMeshActorはメッシュαも設定（シェーダーで参照するため）
    for (DWORD i = 0; i < _pD3DXMeshModel->_dwNumMaterials; i++) {
        _paD3DMaterial9[i].Ambient.a = _fAlpha;
        _paD3DMaterial9[i].Diffuse.a = _fAlpha;
    }
}

GgafDx9DynaD3DXMeshActor::~GgafDx9DynaD3DXMeshActor() {
}
