#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;

GgafDx9MorphMeshActor::GgafDx9MorphMeshActor(const char* prm_name,
                                             const char* prm_model,
                                             const char* prm_effect,
                                             const char* prm_technique,
                                             GgafDx9Morpher* prm_pMorpher,
                                             GgafDx9GeometryMover*   prm_pGeoMover,
                                             GgafDx9GeometryChecker* prm_pGeoChecker) :
    GgafDx9UntransformedActor(prm_name, prm_pGeoMover, prm_pGeoChecker)
{
    _class_name = "GgafDx9MorphMeshActor";
    _technique = NEW char[51];
    strcpy(_technique, prm_technique);
   //モデル取得
    _pModelCon = (GgafDx9ModelConnection*)GgafDx9God::_pModelManager->getConnection(prm_model);
    _pMorphMeshModel = (GgafDx9MorphMeshModel*)_pModelCon->view();
    //エフェクト取得
    _pEffectCon = (GgafDx9EffectConnection*)GgafDx9God::_pEffectManager->getConnection(prm_effect);
    _pMorphMeshEffect = (GgafDx9MorphMeshEffect*)_pEffectCon->view();
    //モデルのオリジナルマテリアルをコピーして保存
    _paD3DMaterial9 = NEW D3DMATERIAL9[_pMorphMeshModel->_dwNumMaterials];
    for (DWORD i = 0; i < _pMorphMeshModel->_dwNumMaterials; i++){
        _paD3DMaterial9[i] = _pMorphMeshModel->_paD3DMaterial9_default[i];
    }
    //重み初期化
    for (int i = 1; i < 10; i++) {
        _weight[i] = 0.0;
    }
    _pMorpher = prm_pMorpher;
}



void GgafDx9MorphMeshActor::setAlpha(float prm_fAlpha) {
    GgafDx9UntransformedActor::setAlpha(prm_fAlpha);
    //α設定
    for (DWORD i = 0; i < _pMorphMeshModel->_dwNumMaterials; i++) {
        _paD3DMaterial9[i].Ambient.a = _fAlpha;
        _paD3DMaterial9[i].Diffuse.a = _fAlpha;
    }
}

void GgafDx9MorphMeshActor::processDrawMain() {
    static ID3DXEffect* pID3DXEffect;
    pID3DXEffect = _pMorphMeshEffect->_pID3DXEffect;
    HRESULT hr;
    //VIEW変換行列
    hr = pID3DXEffect->SetMatrix(_pMorphMeshEffect->_hMatView, &GgafDx9Universe::_pCamera->_vMatrixView );
    mightDx9Exception(hr, D3D_OK, "GgafDx9MorphMeshActor::GgafDx9MeshEffect SetMatrix(g_matView) に失敗しました。");


    static D3DXMATRIX matWorld; //UNIVERSE変換行列
    GgafDx9UntransformedActor::getWorldMatrix_RxRzRyScMv(this, matWorld);

//	hr = pID3DXEffect->SetTechnique(_technique);
//    mightDx9Exception(hr, S_OK, "GgafDx9MorphMeshActor::processDrawMain() SetTechnique("<<_technique<<") に失敗しました。");

    hr = pID3DXEffect->SetInt(_pMorphMeshEffect->_hMorphTargetnum, _pMorphMeshModel->_morph_target_num);
    mightDx9Exception(hr, D3D_OK, "GgafDx9MorphMeshActor::processDrawMain() SetInt(_hMorphTargetnum) に失敗しました。");
    for (int pattern = 1; pattern <= _pMorphMeshModel->_morph_target_num; pattern++) {
        hr = pID3DXEffect->SetFloat(_pMorphMeshEffect->_hWeight[pattern], _weight[pattern]);
        mightDx9Exception(hr, D3D_OK, "GgafDx9MorphMeshActor::processDrawMain() SetFloat(_hWeight["<<pattern<<"]) に失敗しました。");
    }

    hr = pID3DXEffect->SetMatrix(_pMorphMeshEffect->_hMatWorld, &matWorld );
    mightDx9Exception(hr, D3D_OK, "GgafDx9MorphMeshActor::processDrawMain() SetMatrix(g_matWorld) に失敗しました。");
//    UINT numPass;
//    hr = pID3DXEffect->Begin( &numPass, D3DXFX_DONOTSAVESTATE );
//    mightDx9Exception(hr, D3D_OK, "GgafDx9MorphMeshActor::processDrawMain() Begin() に失敗しました。");
//
//    //モーフターゲットの数により pass を切り替えている
//    //プリマリメッシュのみ                             = pass0
//    //プライマリメッシュ＋モーフターゲットメッシュ１つ = pass1
//    //プライマリメッシュ＋モーフターゲットメッシュ２つ = pass2
//    //以下最大９まで
//    hr = pID3DXEffect->BeginPass(_pMorphMeshModel->_morph_target_num);
//    mightDx9Exception(hr, D3D_OK, "GgafDx9MorphMeshActor::processDrawMain() BeginPass("<<_pMorphMeshModel->_morph_target_num<<") に失敗しました。");
    _pMorphMeshModel->draw(this);
//    hr = pID3DXEffect->EndPass();
//    mightDx9Exception(hr, D3D_OK, "GgafDx9MorphMeshActor::processDrawMain() EndPass() に失敗しました。");
//    hr = pID3DXEffect->End();
//    mightDx9Exception(hr, D3D_OK, "GgafDx9MorphMeshActor::processDrawMain() End() に失敗しました。");

}

int GgafDx9MorphMeshActor::getMorphTergetNum() {
    return _pMorphMeshModel->_morph_target_num;
}

GgafDx9MorphMeshActor::~GgafDx9MorphMeshActor() {
    DELETE_POSSIBLE_NULL(_pMorpher);
    DELETEARR_IMPOSSIBLE_NULL(_technique);
    _pModelCon->close();
    _pEffectCon->close();
    DELETEARR_IMPOSSIBLE_NULL(_paD3DMaterial9);
}
