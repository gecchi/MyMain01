#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;

GgafDx9MeshSetActor::GgafDx9MeshSetActor(const char* prm_name,
                                   const char* prm_model,
                                   const char* prm_effect,
                                   const char* prm_technique,
                                   GgafDx9Checker* prm_pChecker) :
                                       GgafDx9DrawableUntransformedActor(prm_name,
                                                                         prm_model,
                                                                         prm_effect,
                                                                         prm_technique,
                                                                         prm_pChecker) {
    _class_name = "GgafDx9MeshSetActor";
    _pMeshSetModel = (GgafDx9MeshSetModel*)_pGgafDx9Model;
    _pMeshSetEffect = (GgafDx9MeshSetEffect*)_pGgafDx9Effect;
}


void GgafDx9MeshSetActor::setAlpha(float prm_fAlpha) {
    GgafDx9DrawableUntransformedActor::setAlpha(prm_fAlpha);
    //GgafDx9MeshSetActorはメッシュαも設定（シェーダーで参照するため）
    for (DWORD i = 0; i < _pMeshSetModel->_dwNumMaterials; i++) {
        _paD3DMaterial9[i].Ambient.a = _fAlpha;
        _paD3DMaterial9[i].Diffuse.a = _fAlpha;
    }
}


void GgafDx9MeshSetActor::processDrawMain() {
    static ID3DXEffect* pID3DXEffect;
    pID3DXEffect = _pMeshSetEffect->_pID3DXEffect;
    HRESULT hr;
    hr = pID3DXEffect->SetMatrix(_pMeshSetEffect->_hMatView, &GgafDx9Universe::_pCamera->_vMatrixView );
    mightDx9Exception(hr, D3D_OK, "GgafDx9MeshSetActor::GgafDx9MeshSetEffect SetMatrix(g_matView) に失敗しました。");
    static D3DXMATRIX matWorld; //UNIVERSE変換行列
    GgafDx9UntransformedActor::getWorldMatrix_ScRxRzRyMv(this, matWorld);
    hr = pID3DXEffect->SetMatrix(_pMeshSetEffect->_hMatWorld, &matWorld );
    mightDx9Exception(hr, D3D_OK, "GgafDx9MeshSetActor::processDrawMain() SetMatrix(g_matWorld) に失敗しました。");

    _pMeshSetModel->draw(this);
}

GgafDx9MeshSetActor::~GgafDx9MeshSetActor() {
}
