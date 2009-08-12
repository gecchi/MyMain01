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
    _class_name = "GgafDx9DynaD3DXMeshActor";

    _pD3DXMeshModel = (GgafDx9D3DXMeshModel*)_pGgafDx9Model;
    _pMeshEffect = (GgafDx9MeshEffect*)_pGgafDx9EffectCon;

}

void GgafDx9DynaD3DXMeshActor::processDraw() {
    static ID3DXEffect* pID3DXEffect;
    pID3DXEffect = _pMeshEffect->_pID3DXEffect;
    GgafDx9GeometricActor::getWorldMatrix_ScRxRzRyMv(this, _matWorld);
    HRESULT hr;
    hr = pID3DXEffect->SetMatrix( _pMeshEffect->_hMatView, &pCAM->_vMatrixView );
    mightDx9Exception(hr, D3D_OK, "GgafDx9DynaD3DXMeshActor::GgafDx9MeshEffect SetMatrix(g_matView) に失敗しました。");
    hr = pID3DXEffect->SetMatrix(_pMeshEffect->_hMatWorld, &_matWorld );
    mightDx9Exception(hr, D3D_OK, "GgafDx9DynaD3DXMeshActor::processDraw() SetMatrix(g_matWorld) に失敗しました。");

    _pD3DXMeshModel->draw(this);
}

void GgafDx9DynaD3DXMeshActor::setAlpha(float prm_fAlpha) {
    GgafDx9DrawableActor::setAlpha(prm_fAlpha);
    //GgafDx9DynaD3DXMeshActorはメッシュαも設定（シェーダーで参照するため）
    for (DWORD i = 0; i < _pD3DXMeshModel->_dwNumMaterials; i++) {
        _paD3DMaterial9[i].Ambient.a = _fAlpha;
        _paD3DMaterial9[i].Diffuse.a = _fAlpha;
    }
}
GgafDx9DynaD3DXMeshActor::~GgafDx9DynaD3DXMeshActor() {
}
