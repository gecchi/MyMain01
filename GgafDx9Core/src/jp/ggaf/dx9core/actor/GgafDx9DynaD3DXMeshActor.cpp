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

                                                   GgafDx9UntransformedActor(prm_name,
                                                                             prm_pChecker) {
    _class_name = "GgafDx9DynaD3DXMeshActor";

	_technique = NEW char[51];
    strcpy(_technique, prm_technique);

	_pModelCon = (GgafDx9ModelConnection*)GgafDx9God::_pModelManager->getConnection(prm_model);
    _pD3DXMeshModel = (GgafDx9D3DXMeshModel*)_pModelCon->view();
    //エフェクト取得
    _pEffectCon = (GgafDx9EffectConnection*)GgafDx9God::_pEffectManager->getConnection(prm_effect);
    _pMeshEffect = (GgafDx9MeshEffect*)_pEffectCon->view();

	//マテリアルをコピー
    _paD3DMaterial9 = NEW D3DMATERIAL9[_pD3DXMeshModel->_dwNumMaterials];
	for (DWORD i = 0; i < _pD3DXMeshModel->_dwNumMaterials; i++){
        _paD3DMaterial9[i] = _pD3DXMeshModel->_paD3DMaterial9_default[i];
    }
}

void GgafDx9DynaD3DXMeshActor::processDrawMain() {
    static ID3DXEffect* pID3DXEffect;
    pID3DXEffect = _pMeshEffect->_pID3DXEffect;
    static D3DXMATRIX matWorld; //World変換行列
    GgafDx9UntransformedActor::getWorldMatrix_ScRxRzRyMv(this, matWorld);
    HRESULT hr;
    hr = pID3DXEffect->SetMatrix( _pMeshEffect->_hMatView, &GgafDx9Universe::_pCamera->_vMatrixView );
    mightDx9Exception(hr, D3D_OK, "GgafDx9DynaD3DXMeshActor::GgafDx9MeshEffect SetMatrix(g_matView) に失敗しました。");
    hr = pID3DXEffect->SetMatrix(_pMeshEffect->_hMatWorld, &matWorld );
    mightDx9Exception(hr, D3D_OK, "GgafDx9DynaD3DXMeshActor::processDrawMain() SetMatrix(g_matWorld) に失敗しました。");

    _pD3DXMeshModel->draw(this);
}

void GgafDx9DynaD3DXMeshActor::setAlpha(float prm_fAlpha) {
    GgafDx9UntransformedActor::setAlpha(prm_fAlpha);
    //α設定
    for (DWORD i = 0; i < _pD3DXMeshModel->_dwNumMaterials; i++) {
        _paD3DMaterial9[i].Ambient.a = _fAlpha;
        _paD3DMaterial9[i].Diffuse.a = _fAlpha;
    }
}
GgafDx9DynaD3DXMeshActor::~GgafDx9DynaD3DXMeshActor() {
    DELETEARR_IMPOSSIBLE_NULL(_technique);
    _pModelCon->close();
    _pEffectCon->close();
    DELETEARR_IMPOSSIBLE_NULL(_paD3DMaterial9);
}
