#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;

GgafDxMorphMeshActor::GgafDxMorphMeshActor(const char* prm_name,
                                           const char* prm_model_id,
                                           const char* prm_effect_id,
                                           const char* prm_technique,
                                           GgafStatus* prm_pStat,
                                           GgafDxChecker* prm_pChecker) :

                                               GgafDxDrawableActor(prm_name,
                                                                   prm_model_id,
                                                                   "M",
                                                                   prm_effect_id,
                                                                   "M",
                                                                   prm_technique,
                                                                   prm_pStat,
                                                                   prm_pChecker) {
    _obj_class |= Obj_GgafDxMorphMeshActor;
    _class_name = "GgafDxMorphMeshActor";
    _pMorphMeshModel = (GgafDxMorphMeshModel*)_pModel;
    _pMorphMeshEffect = (GgafDxMorphMeshEffect*)_pEffect;
    _pFunc_calcRotMvWorldMatrix = GgafDxUtil::setWorldMatrix_RxRzRyMv;
    //重み初期化
    for (int i = 1; i <= MAX_MORPH_TARGET; i++) {
        _weight[i] = 0.0f;
    }
}


GgafDxMorphMeshActor::GgafDxMorphMeshActor(const char* prm_name,
                                           const char* prm_model_id,
                                           const char* prm_model_type,
                                           const char* prm_effect_id,
                                           const char* prm_effect_type,
                                           const char* prm_technique,
                                           GgafStatus* prm_pStat,
                                           GgafDxChecker* prm_pChecker) :

                                               GgafDxDrawableActor(prm_name,
                                                                   prm_model_id,
                                                                   prm_model_type,
                                                                   prm_effect_id,
                                                                   prm_effect_type,
                                                                   prm_technique,
                                                                   prm_pStat,
                                                                   prm_pChecker) {
    _obj_class |= Obj_GgafDxMorphMeshActor;
    _class_name = "GgafDxMorphMeshActor";
    _pMorphMeshModel = (GgafDxMorphMeshModel*)_pModel;
    _pMorphMeshEffect = (GgafDxMorphMeshEffect*)_pEffect;
    _pFunc_calcRotMvWorldMatrix = GgafDxUtil::setWorldMatrix_RxRzRyMv;
    //重み初期化
    for (int i = 1; i <= MAX_MORPH_TARGET; i++) {
        _weight[i] = 0.0f;
    }
}

void GgafDxMorphMeshActor::setAlpha(float prm_fAlpha) {
    _fAlpha = prm_fAlpha;
    //GgafDxMorphMeshActorはメッシュαも設定（シェーダーで参照するため）
    for (DWORD i = 0; i < _pMorphMeshModel->_dwNumMaterials; i++) {
        _paMaterial[i].Ambient.a = _fAlpha;
        _paMaterial[i].Diffuse.a = _fAlpha;
    }
}

void GgafDxMorphMeshActor::addAlpha(float prm_fAlpha) {
    _fAlpha += prm_fAlpha;
    //GgafDxMorphMeshActorはメッシュαも設定（シェーダーで参照するため）
    for (DWORD i = 0; i < _pMorphMeshModel->_dwNumMaterials; i++) {
        _paMaterial[i].Ambient.a = _fAlpha;
        _paMaterial[i].Diffuse.a = _fAlpha;
    }
}

void GgafDxMorphMeshActor::processDraw() {
    ID3DXEffect* pID3DXEffect = _pMorphMeshEffect->_pID3DXEffect;
    HRESULT hr;
    hr = pID3DXEffect->SetMatrix(_pMorphMeshEffect->_h_matView, &P_CAM->_matView );
    checkDxException(hr, D3D_OK, "GgafDxMorphMeshActor::processDraw() SetMatrix(g_matView) に失敗しました。");
    hr = pID3DXEffect->SetInt(_pMorphMeshEffect->_h_morph_target_num, _pMorphMeshModel->_morph_target_num);
    checkDxException(hr, D3D_OK, "GgafDxMorphMeshActor::processDraw() SetInt(_h_morph_target_num) に失敗しました。");
    for (int pattern = 1; pattern <= _pMorphMeshModel->_morph_target_num; pattern++) {
        hr = pID3DXEffect->SetFloat(_pMorphMeshEffect->_ah_weight[pattern], _weight[pattern]);
        checkDxException(hr, D3D_OK, "GgafDxMorphMeshActor::processDraw() SetFloat(_ah_weight["<<pattern<<"]) に失敗しました。");
    }
    hr = pID3DXEffect->SetMatrix(_pMorphMeshEffect->_h_matWorld, &_matWorld );
    checkDxException(hr, D3D_OK, "GgafDxMorphMeshActor::processDraw() SetMatrix(g_matWorld) に失敗しました。");
    _pMorphMeshModel->draw(this);
}

int GgafDxMorphMeshActor::getMorphTergetNum() {
    return _pMorphMeshModel->_morph_target_num;
}

GgafDxMorphMeshActor::~GgafDxMorphMeshActor() {
}
