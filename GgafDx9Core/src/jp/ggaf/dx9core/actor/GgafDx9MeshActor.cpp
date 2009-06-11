#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;

GgafDx9MeshActor::GgafDx9MeshActor(const char* prm_name,
                                   const char* prm_model,
                                   const char* prm_effect,
                                   const char* prm_technique,
                                   GgafDx9Checker* prm_pChecker) :
                                       GgafDx9DrawableUntransformedActor(prm_name,
                                                                         prm_model,
                                                                         prm_effect,
                                                                         prm_technique,
                                                                         prm_pChecker) {
    _class_name = "GgafDx9MeshActor";
    _pMeshModel = (GgafDx9MeshModel*)_pDx9Model;
    _pMeshEffect = (GgafDx9MeshEffect*)_pDx9Effect;
}


void GgafDx9MeshActor::setAlpha(float prm_fAlpha) {
    GgafDx9DrawableUntransformedActor::setAlpha(prm_fAlpha);
    //Éøê›íË
    for (DWORD i = 0; i < _pMeshModel->_dwNumMaterials; i++) {
        _paD3DMaterial9[i].Ambient.a = _fAlpha;
        _paD3DMaterial9[i].Diffuse.a = _fAlpha;
    }
}


void GgafDx9MeshActor::processDrawMain() {
    static ID3DXEffect* pID3DXEffect;
    pID3DXEffect = _pMeshEffect->_pID3DXEffect;
    HRESULT hr;
    hr = pID3DXEffect->SetMatrix(_pMeshEffect->_hMatView, &GgafDx9Universe::_pCamera->_vMatrixView );
    mightDx9Exception(hr, D3D_OK, "GgafDx9MeshActor::GgafDx9MeshEffect SetMatrix(g_matView) Ç…é∏îsÇµÇ‹ÇµÇΩÅB");
    static D3DXMATRIX matWorld; //UNIVERSEïœä∑çsóÒ
    GgafDx9UntransformedActor::getWorldMatrix_ScRxRzRyMv(this, matWorld);
    hr = pID3DXEffect->SetMatrix(_pMeshEffect->_hMatWorld, &matWorld );
    mightDx9Exception(hr, D3D_OK, "GgafDx9MeshActor::processDrawMain() SetMatrix(g_matWorld) Ç…é∏îsÇµÇ‹ÇµÇΩÅB");

    _pMeshModel->draw(this);
}

GgafDx9MeshActor::~GgafDx9MeshActor() {
}
