#include "stdafx.h"
#include "jp/ggaf/dxcore/actor/GgafDxMorphMeshActor.h"

#include "jp/ggaf/dxcore/exception/GgafDxCriticalException.h"
#include "jp/ggaf/dxcore/util/GgafDxUtil.h"
#include "jp/ggaf/dxcore/effect/GgafDxMorphMeshEffect.h"
#include "jp/ggaf/dxcore/model/GgafDxMorphMeshModel.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxMorpher.h"
#include "jp/ggaf/dxcore/scene/GgafDxUniverse.h"

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
                                                                   prm_pChecker),
_pMorphMeshModel((GgafDxMorphMeshModel*)_pModel),
_pMorphMeshEffect((GgafDxMorphMeshEffect*)_pEffect),
_pMorpher(new GgafDxMorpher(this)) {

    _obj_class |= Obj_GgafDxMorphMeshActor;
    _class_name = "GgafDxMorphMeshActor";
    _pFunc_calcRotMvWorldMatrix = UTIL::setWorldMatrix_RxRzRyMv;
    (*_pFunc_calcRotMvWorldMatrix)(this, _matWorldRotMv);
    //重み初期化
    for (int i = 1; i <= MAX_MORPH_TARGET; i++) {
        _weight[i] = 0.0f;
    }
    _morph_target_num = _pMorphMeshModel->_morph_target_num;
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
                                                                   prm_pChecker),
_pMorphMeshModel((GgafDxMorphMeshModel*)_pModel),
_pMorphMeshEffect((GgafDxMorphMeshEffect*)_pEffect),
_pMorpher(new GgafDxMorpher(this)) {
    _obj_class |= Obj_GgafDxMorphMeshActor;
    _class_name = "GgafDxMorphMeshActor";
    _pFunc_calcRotMvWorldMatrix = UTIL::setWorldMatrix_RxRzRyMv;
    (*_pFunc_calcRotMvWorldMatrix)(this, _matWorldRotMv);
    //重み初期化
    for (int i = 1; i <= MAX_MORPH_TARGET; i++) {
        _weight[i] = 0.0f;
    }
    _morph_target_num = _pMorphMeshModel->_morph_target_num;
}
void GgafDxMorphMeshActor::setWeight(int prm_target_mesh_no, float prm_weight) {
#ifdef MY_DEBUG
    if (prm_target_mesh_no < 1 || _morph_target_num > prm_target_mesh_no) {
        throwGgafCriticalException("GgafDxMorphMeshActor::setWeight() prm_target_mesh_no(="<<prm_target_mesh_no<<") が、範囲外です。(有効範囲は 1～"<<_morph_target_num<<") ");
    }
#endif
     _weight[prm_target_mesh_no] = prm_weight;
}
void GgafDxMorphMeshActor::setWeight(float prm_weight) {
    for (int i = 1; i <= _morph_target_num; i++) {
        _weight[i] = prm_weight;
    }
}

float GgafDxMorphMeshActor::getWeight(int prm_target_mesh_no) {
#ifdef MY_DEBUG
    if (prm_target_mesh_no < 1 || _morph_target_num > prm_target_mesh_no) {
        throwGgafCriticalException("GgafDxMorphMeshActor::setWeight() prm_target_mesh_no(="<<prm_target_mesh_no<<") が、範囲外です。(有効範囲は 1～"<<_morph_target_num<<") ");
    }
#endif
    return _weight[prm_target_mesh_no];
}

void GgafDxMorphMeshActor::addWeight(int prm_target_mesh_no, float prm_add_weight) {
#ifdef MY_DEBUG
    if (prm_target_mesh_no < 1 || _morph_target_num > prm_target_mesh_no) {
        throwGgafCriticalException("GgafDxMorphMeshActor::setWeight() prm_target_mesh_no(="<<prm_target_mesh_no<<") が、範囲外です。(有効範囲は 1～"<<_morph_target_num<<") ");
    }
#endif
    _weight[prm_target_mesh_no] += prm_add_weight;
}
void GgafDxMorphMeshActor::setAlpha(float prm_alpha) {
    _alpha = prm_alpha;
    //GgafDxMorphMeshActorはメッシュαも設定（シェーダーで参照するため）
    for (DWORD i = 0; i < _pMorphMeshModel->_num_materials; i++) {
        _paMaterial[i].Ambient.a = _alpha;
        _paMaterial[i].Diffuse.a = _alpha;
    }
}

void GgafDxMorphMeshActor::addAlpha(float prm_alpha) {
    _alpha += prm_alpha;
    //GgafDxMorphMeshActorはメッシュαも設定（シェーダーで参照するため）
    for (DWORD i = 0; i < _pMorphMeshModel->_num_materials; i++) {
        _paMaterial[i].Ambient.a = _alpha;
        _paMaterial[i].Diffuse.a = _alpha;
    }
}

void GgafDxMorphMeshActor::processDraw() {
    GgafDxMorphMeshEffect* pMorphMeshEffect = _pMorphMeshEffect;
    ID3DXEffect* pID3DXEffect = pMorphMeshEffect->_pID3DXEffect;
    HRESULT hr;
    hr = pID3DXEffect->SetMatrix(pMorphMeshEffect->_h_matView, &P_CAM->_matView );
    checkDxException(hr, D3D_OK, "GgafDxMorphMeshActor::processDraw() SetMatrix(g_matView) に失敗しました。");
    hr = pID3DXEffect->SetInt(pMorphMeshEffect->_h_morph_target_num, _pMorphMeshModel->_morph_target_num);
    checkDxException(hr, D3D_OK, "GgafDxMorphMeshActor::processDraw() SetInt(_h_morph_target_num) に失敗しました。");
    for (int pattern = 1; pattern <= _pMorphMeshModel->_morph_target_num; pattern++) {
        hr = pID3DXEffect->SetFloat(pMorphMeshEffect->_ah_weight[pattern], _weight[pattern]);
        checkDxException(hr, D3D_OK, "GgafDxMorphMeshActor::processDraw() SetFloat(_ah_weight["<<pattern<<"]) に失敗しました。");
    }
    hr = pID3DXEffect->SetMatrix(pMorphMeshEffect->_h_matWorld, &_matWorld );
    checkDxException(hr, D3D_OK, "GgafDxMorphMeshActor::processDraw() SetMatrix(g_matWorld) に失敗しました。");
    _pMorphMeshModel->draw(this);
}

int GgafDxMorphMeshActor::getMorphTergetNum() {
    return _pMorphMeshModel->_morph_target_num;
}

GgafDxMorphMeshActor::~GgafDxMorphMeshActor() {
    delete _pMorpher;
}
