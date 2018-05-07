#include "jp/ggaf/dxcore/actor/GgafDxMassMorphMeshActor.h"

#include "jp/ggaf/dxcore/GgafDxGod.h"
#include "jp/ggaf/dxcore/effect/GgafDxMassMorphMeshEffect.h"
#include "jp/ggaf/dxcore/exception/GgafDxCriticalException.h"
#include "jp/ggaf/dxcore/model/GgafDxMassMorphMeshModel.h"
#include "jp/ggaf/dxcore/scene/GgafDxSpacetime.h"
#include "jp/ggaf/dxcore/util/GgafDxUtil.h"

using namespace GgafCore;
using namespace GgafDxCore;

GgafDxMassMorphMeshActor::GgafDxMassMorphMeshActor(const char* prm_name,
                                                   const char* prm_model_id,
                                                   const char* prm_effect_id,
                                                   const char* prm_technique,
                                                   GgafStatus* prm_pStat,
                                                   GgafDxChecker* prm_pChecker) :

                                                       GgafDxFigureActor(prm_name,
                                                                         prm_model_id,
                                                                         TYPE_MASSMORPHMESH_MODEL,
                                                                         prm_effect_id,
                                                                         TYPE_MASSMORPHMESH_EFFECT,
                                                                         prm_technique,
                                                                         prm_pStat,
                                                                         prm_pChecker),
_pMorpher(new GgafDxMorpher<GgafDxMassMorphMeshActor>(this)),
_pMassMorphMeshModel((GgafDxMassMorphMeshModel*)_pModel),
_pMassMorphMeshEffect((GgafDxMassMorphMeshEffect*)_pEffect)
{
    _obj_class |= Obj_GgafDxMassMorphMeshActor;
    _class_name = "GgafDxMassMorphMeshActor";
    defineRotMvWorldMatrix(UTIL::setWorldMatrix_RxRzRyMv); //デフォルトの回転×移動の変換行列
    //重み初期化
    for (int i = 0; i <= MAX_MASS_MORPH_TARGET_NUM; i++) {
        _weight[i] = 0.0f;
    }
    _morph_target_num = _pMassMorphMeshModel->_morph_target_num;
    GgafDxMassMorphMeshActor::changeEffectTechnique(prm_technique); //テクニック名末尾にターゲット数を付与
}

GgafDxMassMorphMeshActor::GgafDxMassMorphMeshActor(const char* prm_name,
                                                   const char* prm_model_id,
                                                   const char prm_model_type,
                                                   const char* prm_effect_id,
                                                   const char prm_effect_type,
                                                   const char* prm_technique,
                                                   GgafStatus* prm_pStat,
                                                   GgafDxChecker* prm_pChecker) :

                                                       GgafDxFigureActor(prm_name,
                                                                         prm_model_id,
                                                                         prm_model_type,
                                                                         prm_effect_id,
                                                                         prm_effect_type,
                                                                         prm_technique,
                                                                         prm_pStat,
                                                                         prm_pChecker),
_pMorpher(new GgafDxMorpher<GgafDxMassMorphMeshActor>(this)),
_pMassMorphMeshModel((GgafDxMassMorphMeshModel*)_pModel),
_pMassMorphMeshEffect((GgafDxMassMorphMeshEffect*)_pEffect)
{
    _obj_class |= Obj_GgafDxMassMorphMeshActor;
    _class_name = "GgafDxMassMorphMeshActor";
    defineRotMvWorldMatrix(UTIL::setWorldMatrix_RxRzRyMv); //デフォルトの回転×移動の変換行列
    //重み初期化
    for (int i = 0; i <= MAX_MASS_MORPH_TARGET_NUM; i++) {
        _weight[i] = 0.0f;
    }
    _morph_target_num = _pMassMorphMeshModel->_morph_target_num;
    GgafDxMassMorphMeshActor::changeEffectTechnique(prm_technique); //テクニック名末尾にターゲット数を付与
}
void GgafDxMassMorphMeshActor::setMorphWeight(int prm_target_mesh_no, float prm_weight) {
#ifdef MY_DEBUG
    if (prm_target_mesh_no < 1 || _morph_target_num < prm_target_mesh_no) {
        throwGgafCriticalException("prm_target_mesh_no(="<<prm_target_mesh_no<<") が、範囲外です。(有効範囲は 1～"<<_morph_target_num<<") ");
    }
#endif
     _weight[prm_target_mesh_no] = prm_weight;
}
void GgafDxMassMorphMeshActor::setMorphWeight(float prm_weight) {
    for (int i = 1; i <= _morph_target_num; i++) {
        _weight[i] = prm_weight;
    }
}

float GgafDxMassMorphMeshActor::getMorphWeight(int prm_target_mesh_no) {
#ifdef MY_DEBUG
    if (prm_target_mesh_no < 1 || _morph_target_num < prm_target_mesh_no) {
        throwGgafCriticalException("prm_target_mesh_no(="<<prm_target_mesh_no<<") が、範囲外です。(有効範囲は 1～"<<_morph_target_num<<") ");
    }
#endif
    return _weight[prm_target_mesh_no];
}

void GgafDxMassMorphMeshActor::addMorphWeight(int prm_target_mesh_no, float prm_add_weight) {
#ifdef MY_DEBUG
    if (prm_target_mesh_no < 1 || _morph_target_num < prm_target_mesh_no) {
        throwGgafCriticalException("prm_target_mesh_no(="<<prm_target_mesh_no<<") が、範囲外です。(有効範囲は 1～"<<_morph_target_num<<") ");
    }
#endif
    _weight[prm_target_mesh_no] += prm_add_weight;
}

int GgafDxMassMorphMeshActor::getMorphTergetNum() {
    return _pMassMorphMeshModel->_morph_target_num;
}

void GgafDxMassMorphMeshActor::changeEffectTechnique(const char* prm_technique) {
    std::string technique = std::string(_pEffect->getName()) + "_" + std::string(prm_technique) + XTOS(_morph_target_num);
    std::string technique2 = std::string(prm_technique) + XTOS(_morph_target_num);   //テクニック名末尾にターゲット数を付与
#ifdef MY_DEBUG
    if (technique2.length() > 255) {
        throwGgafCriticalException("テクニック名が長すぎます。prm_technique="<<prm_technique<<" technique2="<<technique);
    }
#endif
    _hash_technique = UTIL::easy_hash(technique.c_str());
    strcpy(_technique, technique2.c_str());
}

GgafDxMassMorphMeshActor::~GgafDxMassMorphMeshActor() {
    delete _pMorpher;
}
