#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;

DWORD GgafDx9DynaD3DXMeshActor::FVF = (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1);

GgafDx9DynaD3DXMeshActor::GgafDx9DynaD3DXMeshActor(const char* prm_name,
                                                   const char* prm_model,
                                                   const char* prm_effect,
                                                   const char* prm_technique,
                                                   GgafDx9Checker* prm_pChecker) :

                                                       GgafDx9DrawableUntransformedActor(prm_name,
                                                                                         prm_model,
                                                                                         prm_effect,
                                                                                         prm_technique,
                                                                                         prm_pChecker) {
    _class_name = "GgafDx9DynaD3DXMeshActor";

    _pD3DXMeshModel = (GgafDx9D3DXMeshModel*)_pDx9Model;
    _pMeshEffect = (GgafDx9MeshEffect*)_pDx9EffectCon;

}

void GgafDx9DynaD3DXMeshActor::processDrawMain() {
    static ID3DXEffect* pID3DXEffect;
    pID3DXEffect = _pMeshEffect->_pID3DXEffect;
    static D3DXMATRIX matWorld; //Worldïœä∑çsóÒ
    GgafDx9UntransformedActor::getWorldMatrix_ScRxRzRyMv(this, matWorld);
    HRESULT hr;
    hr = pID3DXEffect->SetMatrix( _pMeshEffect->_hMatView, &GgafDx9Universe::_pCamera->_vMatrixView );
    mightDx9Exception(hr, D3D_OK, "GgafDx9DynaD3DXMeshActor::GgafDx9MeshEffect SetMatrix(g_matView) Ç…é∏îsÇµÇ‹ÇµÇΩÅB");
    hr = pID3DXEffect->SetMatrix(_pMeshEffect->_hMatWorld, &matWorld );
    mightDx9Exception(hr, D3D_OK, "GgafDx9DynaD3DXMeshActor::processDrawMain() SetMatrix(g_matWorld) Ç…é∏îsÇµÇ‹ÇµÇΩÅB");

    _pD3DXMeshModel->draw(this);
}

void GgafDx9DynaD3DXMeshActor::setAlpha(float prm_fAlpha) {
    GgafDx9DrawableUntransformedActor::setAlpha(prm_fAlpha);
    //Éøê›íË
    for (DWORD i = 0; i < _pD3DXMeshModel->_dwNumMaterials; i++) {
        _paD3DMaterial9[i].Ambient.a = _fAlpha;
        _paD3DMaterial9[i].Diffuse.a = _fAlpha;
    }
}
GgafDx9DynaD3DXMeshActor::~GgafDx9DynaD3DXMeshActor() {
}
