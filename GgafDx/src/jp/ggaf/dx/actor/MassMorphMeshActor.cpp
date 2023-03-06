#include "jp/ggaf/dx/actor/MassMorphMeshActor.h"

#include "jp/ggaf/dx/Caretaker.h"
#include "jp/ggaf/dx/effect/MassMorphMeshEffect.h"
#include "jp/ggaf/dx/exception/CriticalException.h"
#include "jp/ggaf/dx/model/MassMorphMeshModel.h"
#include "jp/ggaf/dx/scene/Spacetime.h"
#include "jp/ggaf/dx/util/Util.h"


using namespace GgafDx;

MassMorphMeshActor::MassMorphMeshActor(const char* prm_name,
                                       const char* prm_model,
                                       const char* prm_effect_id,
                                       const char* prm_technique,
                                       CollisionChecker* prm_pChecker) :

                                           FigureActor(prm_name,
                                                       prm_model,
                                                       TYPE_MASSMORPHMESH_MODEL,
                                                       prm_effect_id,
                                                       TYPE_MASSMORPHMESH_EFFECT,
                                                       prm_technique,
                                                       prm_pChecker),
_pMorpher(new Morpher<MassMorphMeshActor>(this)),
_pMassMorphMeshModel((MassMorphMeshModel*)_pModel),
_pMassMorphMeshEffect((MassMorphMeshEffect*)_pEffect)
{
    _obj_class |= Obj_GgafDx_MassMorphMeshActor;
    _class_name = "MassMorphMeshActor";
    defineRotMvWorldMatrix(UTIL::setWorldMatrix_RxRzRyMv); //デフォルトの回転×移動の変換行列
    //重み初期化
    for (int i = 0; i <= MAX_MASS_MORPH_TARGET_NUM; i++) {
        _weight[i] = 0.0f;
    }
    _morph_target_num = _pMassMorphMeshModel->_morph_target_num;
    MassMorphMeshActor::changeEffectTechnique(prm_technique); //テクニック名末尾にターゲット数を付与
}

MassMorphMeshActor::MassMorphMeshActor(const char* prm_name,
                                       const char* prm_model,
                                       const char prm_model_type,
                                       const char* prm_effect_id,
                                       const char prm_effect_type,
                                       const char* prm_technique,
                                       CollisionChecker* prm_pChecker) :

                                           FigureActor(prm_name,
                                                       prm_model,
                                                       prm_model_type,
                                                       prm_effect_id,
                                                       prm_effect_type,
                                                       prm_technique,
                                                       prm_pChecker),
_pMorpher(new Morpher<MassMorphMeshActor>(this)),
_pMassMorphMeshModel((MassMorphMeshModel*)_pModel),
_pMassMorphMeshEffect((MassMorphMeshEffect*)_pEffect)
{
    _obj_class |= Obj_GgafDx_MassMorphMeshActor;
    _class_name = "MassMorphMeshActor";
    defineRotMvWorldMatrix(UTIL::setWorldMatrix_RxRzRyMv); //デフォルトの回転×移動の変換行列
    //重み初期化
    for (int i = 0; i <= MAX_MASS_MORPH_TARGET_NUM; i++) {
        _weight[i] = 0.0f;
    }
    _morph_target_num = _pMassMorphMeshModel->_morph_target_num;
    MassMorphMeshActor::changeEffectTechnique(prm_technique); //テクニック名末尾にターゲット数を付与
}
void MassMorphMeshActor::setMorphWeight(int prm_target_mesh_no, float prm_weight) {
#ifdef MY_DEBUG
    if (prm_target_mesh_no < 1 || _morph_target_num < prm_target_mesh_no) {
        throwCriticalException("prm_target_mesh_no(="<<prm_target_mesh_no<<") が、範囲外です。(有効範囲は 1～"<<_morph_target_num<<") ");
    }
#endif
     _weight[prm_target_mesh_no] = prm_weight;
}
void MassMorphMeshActor::setMorphWeight(float prm_weight) {
    for (int i = 1; i <= _morph_target_num; i++) {
        _weight[i] = prm_weight;
    }
}

float MassMorphMeshActor::getMorphWeight(int prm_target_mesh_no) {
#ifdef MY_DEBUG
    if (prm_target_mesh_no < 1 || _morph_target_num < prm_target_mesh_no) {
        throwCriticalException("prm_target_mesh_no(="<<prm_target_mesh_no<<") が、範囲外です。(有効範囲は 1～"<<_morph_target_num<<") ");
    }
#endif
    return _weight[prm_target_mesh_no];
}

void MassMorphMeshActor::addMorphWeight(int prm_target_mesh_no, float prm_add_weight) {
#ifdef MY_DEBUG
    if (prm_target_mesh_no < 1 || _morph_target_num < prm_target_mesh_no) {
        throwCriticalException("prm_target_mesh_no(="<<prm_target_mesh_no<<") が、範囲外です。(有効範囲は 1～"<<_morph_target_num<<") ");
    }
#endif
    _weight[prm_target_mesh_no] += prm_add_weight;
}

int MassMorphMeshActor::getMorphTergetNum() {
    return _pMassMorphMeshModel->_morph_target_num;
}

void MassMorphMeshActor::changeEffectTechnique(const char* prm_technique) {
    std::string technique = std::string(_pEffect->getName()) + "_" + std::string(prm_technique) + XTOS(_morph_target_num);
    std::string technique2 = std::string(prm_technique) + XTOS(_morph_target_num);   //テクニック名末尾にターゲット数を付与
#ifdef MY_DEBUG
    if (technique2.length() > 255) {
        throwCriticalException("テクニック名が長すぎます。prm_technique="<<prm_technique<<" technique2="<<technique);
    }
#endif
    _hash_technique = UTIL::easy_hash(technique.c_str());
    strcpy(_technique, technique2.c_str());
}

void MassMorphMeshActor::changeModel(int prm_model_index) {
    FigureActor::changeModel(prm_model_index);
    _pMassMorphMeshModel = (MassMorphMeshModel*)_pModel;
}

MassMorphMeshActor::~MassMorphMeshActor() {
    delete _pMorpher;
}
