#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;

GgafDx9MorphMeshActor::GgafDx9MorphMeshActor(const char* prm_name,
                                             const char* prm_model_id,
                                             const char* prm_effect_id,
                                             const char* prm_technique,
                                             GgafDx9Checker* prm_pChecker) :

                                                 GgafDx9DrawableActor(prm_name,
                                                                       prm_model_id,
                                                                       "M",
                                                                       prm_effect_id,
                                                                       "M",
                                                                       prm_technique,
                                                                       prm_pChecker) {
    _obj_class |= Obj_GgafDx9MorphMeshActor;
    _class_name = "GgafDx9MorphMeshActor";
    _pMorphMeshModel = (GgafDx9MorphMeshModel*)_pGgafDx9Model;
    _pMorphMeshEffect = (GgafDx9MorphMeshEffect*)_pGgafDx9Effect;
    _pFunc_calcRotMvWorldMatrix = GgafDx9Util::setWorldMatrix_RxRzRyMv;
    //重み初期化
    for (int i = 1; i <= MAX_MORPH_TARGET; i++) {
        _weight[i] = 0.0f;
    }
}

void GgafDx9MorphMeshActor::setAlpha(float prm_fAlpha) {
    _fAlpha = prm_fAlpha;
    //GgafDx9MorphMeshActorはメッシュαも設定（シェーダーで参照するため）
    for (DWORD i = 0; i < _pMorphMeshModel->_dwNumMaterials; i++) {
        _paD3DMaterial9[i].Ambient.a = _fAlpha;
        _paD3DMaterial9[i].Diffuse.a = _fAlpha;
    }
}

void GgafDx9MorphMeshActor::addAlpha(float prm_fAlpha) {
    _fAlpha += prm_fAlpha;
    //GgafDx9MorphMeshActorはメッシュαも設定（シェーダーで参照するため）
    for (DWORD i = 0; i < _pMorphMeshModel->_dwNumMaterials; i++) {
        _paD3DMaterial9[i].Ambient.a = _fAlpha;
        _paD3DMaterial9[i].Diffuse.a = _fAlpha;
    }
}

void GgafDx9MorphMeshActor::processDraw() {
    ID3DXEffect* pID3DXEffect = _pMorphMeshEffect->_pID3DXEffect;
    HRESULT hr;
    hr = pID3DXEffect->SetMatrix(_pMorphMeshEffect->_h_matView, &P_CAM->_vMatrixView );
    checkDxException(hr, D3D_OK, "GgafDx9MorphMeshActor::GgafDx9MeshEffect SetMatrix(g_matView) に失敗しました。");
    //(*_pFunc_calcRotMvWorldMatrix)(this, _matWorld);
    hr = pID3DXEffect->SetInt(_pMorphMeshEffect->_h_morph_target_num, _pMorphMeshModel->_morph_target_num);
    checkDxException(hr, D3D_OK, "GgafDx9MorphMeshActor::processDraw() SetInt(_h_morph_target_num) に失敗しました。");
    for (int pattern = 1; pattern <= _pMorphMeshModel->_morph_target_num; pattern++) {
        hr = pID3DXEffect->SetFloat(_pMorphMeshEffect->_ah_weight[pattern], _weight[pattern]);
        checkDxException(hr, D3D_OK, "GgafDx9MorphMeshActor::processDraw() SetFloat(_ah_weight["<<pattern<<"]) に失敗しました。");
    }
    hr = pID3DXEffect->SetMatrix(_pMorphMeshEffect->_h_matWorld, &_matWorld );
    checkDxException(hr, D3D_OK, "GgafDx9MorphMeshActor::processDraw() SetMatrix(g_matWorld) に失敗しました。");

    _pMorphMeshModel->draw(this);
}

int GgafDx9MorphMeshActor::getMorphTergetNum() {
    return _pMorphMeshModel->_morph_target_num;
}

GgafDx9MorphMeshActor::~GgafDx9MorphMeshActor() {
}
