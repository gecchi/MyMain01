#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;

GgafDx9MorphTwoMeshActor::GgafDx9MorphTwoMeshActor(const char* prm_name,
                                   const char* prm_model,
                                   const char* prm_effect,
                                   const char* prm_technique,
                                   GgafDx9GeometryMover* prm_pGeoMover,
                                   GgafDx9GeometryChecker* prm_pGeoChecker) :
    GgafDx9UntransformedActor(prm_name, prm_pGeoMover, prm_pGeoChecker)
{
    _class_name = "GgafDx9MorphTwoMeshActor";
    _technique = NEW char[51];
    strcpy(_technique, prm_technique);
    //モデル取得
    _pModelCon = (GgafDx9ModelConnection*)GgafDx9God::_pModelManager->getConnection(prm_model);
    _pMorphTwoMeshModel = (GgafDx9MorphTwoMeshModel*)_pModelCon->view();
    //エフェクト取得
    _pEffectCon = (GgafDx9EffectConnection*)GgafDx9God::_pEffectManager->getConnection(prm_effect);
    _pMorphTwoMeshEffect = (GgafDx9MorphTwoMeshEffect*)_pEffectCon->view();
    //モデルのオリジナルマテリアルをコピーして保存
    _paD3DMaterial9 = NEW D3DMATERIAL9[_pMorphTwoMeshModel->_dwNumMaterials];
    for (DWORD i = 0; i < _pMorphTwoMeshModel->_dwNumMaterials; i++){
        _paD3DMaterial9[i] = _pMorphTwoMeshModel->_paD3DMaterial9_default[i];
    }
    _weight = 0.0;
}

void GgafDx9MorphTwoMeshActor::setAlpha(float prm_fAlpha) {
    GgafDx9UntransformedActor::setAlpha(prm_fAlpha);
    //α設定
    for (DWORD i = 0; i < _pMorphTwoMeshModel->_dwNumMaterials; i++) {
        _paD3DMaterial9[i].Ambient.a = _fAlpha;
        _paD3DMaterial9[i].Diffuse.a = _fAlpha;
    }
}

void GgafDx9MorphTwoMeshActor::processDrawMain() {
    static ID3DXEffect* pID3DXEffect;
    pID3DXEffect = _pMorphTwoMeshEffect->_pID3DXEffect;
    HRESULT hr;
    //VIEW変換行列
    hr = pID3DXEffect->SetMatrix(_pMorphTwoMeshEffect->_hMatView, &GgafDx9Universe::_pCamera->_vMatrixView );
    potentialDx9Exception(hr, D3D_OK, "GgafDx9MorphTwoMeshActor::GgafDx9MeshEffect SetMatrix(g_matView) に失敗しました。");


    static D3DXMATRIX matWorld; //UNIVERSE変換行列
    GgafDx9UntransformedActor::getWorldMatrix_RxRzRyScMv(this, matWorld);


	hr = pID3DXEffect->SetTechnique(_technique);
    potentialDx9Exception(hr, S_OK, "GgafDx9MorphTwoMeshActor::processDrawMain() SetTechnique("<<_technique<<") に失敗しました。");

    hr = pID3DXEffect->SetFloat(_pMorphTwoMeshEffect->_hWeight, _weight );
    potentialDx9Exception(hr, D3D_OK, "GgafDx9MorphTwoMeshActor::processDrawMain() SetMatrix(_hWeight) に失敗しました。");

    hr = pID3DXEffect->SetMatrix(_pMorphTwoMeshEffect->_hMatWorld, &matWorld );
    potentialDx9Exception(hr, D3D_OK, "GgafDx9MorphTwoMeshActor::processDrawMain() SetMatrix(g_matWorld) に失敗しました。");
    UINT numPass;
    hr = pID3DXEffect->Begin( &numPass, D3DXFX_DONOTSAVESTATE );
    potentialDx9Exception(hr, D3D_OK, "GgafDx9MorphTwoMeshActor::processDrawMain() Begin() に失敗しました。");
    for (UINT pass = 0; pass < numPass; pass++) {
        hr = pID3DXEffect->BeginPass(pass);
        potentialDx9Exception(hr, D3D_OK, "GgafDx9MorphTwoMeshActor::processDrawMain() BeginPass("<<pass<<") に失敗しました。");
        _pMorphTwoMeshModel->draw(this);
        hr = pID3DXEffect->EndPass();
        potentialDx9Exception(hr, D3D_OK, "GgafDx9MorphTwoMeshActor::processDrawMain() EndPass() に失敗しました。");
    }
    hr = pID3DXEffect->End();
    potentialDx9Exception(hr, D3D_OK, "GgafDx9MorphTwoMeshActor::processDrawMain() End() に失敗しました。");

}

GgafDx9MorphTwoMeshActor::~GgafDx9MorphTwoMeshActor() {
    DELETEARR_IMPOSSIBLE_NULL(_technique);
    _pModelCon->close();
    _pEffectCon->close();
    DELETEARR_IMPOSSIBLE_NULL(_paD3DMaterial9);
}
