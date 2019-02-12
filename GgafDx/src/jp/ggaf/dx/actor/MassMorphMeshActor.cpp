#include "jp/ggaf/dx/actor/MassMorphMeshActor.h"

#include "jp/ggaf/dx/God.h"
#include "jp/ggaf/dx/effect/MassMorphMeshEffect.h"
#include "jp/ggaf/dx/exception/CriticalException.h"
#include "jp/ggaf/dx/model/MassMorphMeshModel.h"
#include "jp/ggaf/dx/scene/Spacetime.h"
#include "jp/ggaf/dx/util/Util.h"


using namespace GgafDx;

MassMorphMeshActor::MassMorphMeshActor(const char* prm_name,
                                                   const char* prm_model_id,
                                                   const char* prm_effect_id,
                                                   const char* prm_technique,
                                                   GgafCore::Status* prm_pStat,
                                                   Checker* prm_pChecker) :

                                                       FigureActor(prm_name,
                                                                         prm_model_id,
                                                                         TYPE_MASSMORPHMESH_MODEL,
                                                                         prm_effect_id,
                                                                         TYPE_MASSMORPHMESH_EFFECT,
                                                                         prm_technique,
                                                                         prm_pStat,
                                                                         prm_pChecker),
_pMorpher(new Morpher<MassMorphMeshActor>(this)),
_pMassMorphMeshModel((MassMorphMeshModel*)_pModel),
_pMassMorphMeshEffect((MassMorphMeshEffect*)_pEffect)
{
    _obj_class |= Obj_GgafDx_MassMorphMeshActor;
    _class_name = "MassMorphMeshActor";
    defineRotMvWorldMatrix(UTIL::setWorldMatrix_RxRzRyMv); //�f�t�H���g�̉�]�~�ړ��̕ϊ��s��
    //�d�ݏ�����
    for (int i = 0; i <= MAX_MASS_MORPH_TARGET_NUM; i++) {
        _weight[i] = 0.0f;
    }
    _morph_target_num = _pMassMorphMeshModel->_morph_target_num;
    MassMorphMeshActor::changeEffectTechnique(prm_technique); //�e�N�j�b�N�������Ƀ^�[�Q�b�g����t�^
}

MassMorphMeshActor::MassMorphMeshActor(const char* prm_name,
                                                   const char* prm_model_id,
                                                   const char prm_model_type,
                                                   const char* prm_effect_id,
                                                   const char prm_effect_type,
                                                   const char* prm_technique,
                                                   GgafCore::Status* prm_pStat,
                                                   Checker* prm_pChecker) :

                                                       FigureActor(prm_name,
                                                                         prm_model_id,
                                                                         prm_model_type,
                                                                         prm_effect_id,
                                                                         prm_effect_type,
                                                                         prm_technique,
                                                                         prm_pStat,
                                                                         prm_pChecker),
_pMorpher(new Morpher<MassMorphMeshActor>(this)),
_pMassMorphMeshModel((MassMorphMeshModel*)_pModel),
_pMassMorphMeshEffect((MassMorphMeshEffect*)_pEffect)
{
    _obj_class |= Obj_GgafDx_MassMorphMeshActor;
    _class_name = "MassMorphMeshActor";
    defineRotMvWorldMatrix(UTIL::setWorldMatrix_RxRzRyMv); //�f�t�H���g�̉�]�~�ړ��̕ϊ��s��
    //�d�ݏ�����
    for (int i = 0; i <= MAX_MASS_MORPH_TARGET_NUM; i++) {
        _weight[i] = 0.0f;
    }
    _morph_target_num = _pMassMorphMeshModel->_morph_target_num;
    MassMorphMeshActor::changeEffectTechnique(prm_technique); //�e�N�j�b�N�������Ƀ^�[�Q�b�g����t�^
}
void MassMorphMeshActor::setMorphWeight(int prm_target_mesh_no, float prm_weight) {
#ifdef MY_DEBUG
    if (prm_target_mesh_no < 1 || _morph_target_num < prm_target_mesh_no) {
        throwCriticalException("prm_target_mesh_no(="<<prm_target_mesh_no<<") ���A�͈͊O�ł��B(�L���͈͂� 1�`"<<_morph_target_num<<") ");
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
        throwCriticalException("prm_target_mesh_no(="<<prm_target_mesh_no<<") ���A�͈͊O�ł��B(�L���͈͂� 1�`"<<_morph_target_num<<") ");
    }
#endif
    return _weight[prm_target_mesh_no];
}

void MassMorphMeshActor::addMorphWeight(int prm_target_mesh_no, float prm_add_weight) {
#ifdef MY_DEBUG
    if (prm_target_mesh_no < 1 || _morph_target_num < prm_target_mesh_no) {
        throwCriticalException("prm_target_mesh_no(="<<prm_target_mesh_no<<") ���A�͈͊O�ł��B(�L���͈͂� 1�`"<<_morph_target_num<<") ");
    }
#endif
    _weight[prm_target_mesh_no] += prm_add_weight;
}

int MassMorphMeshActor::getMorphTergetNum() {
    return _pMassMorphMeshModel->_morph_target_num;
}

void MassMorphMeshActor::changeEffectTechnique(const char* prm_technique) {
    std::string technique = std::string(_pEffect->getName()) + "_" + std::string(prm_technique) + XTOS(_morph_target_num);
    std::string technique2 = std::string(prm_technique) + XTOS(_morph_target_num);   //�e�N�j�b�N�������Ƀ^�[�Q�b�g����t�^
#ifdef MY_DEBUG
    if (technique2.length() > 255) {
        throwCriticalException("�e�N�j�b�N�����������܂��Bprm_technique="<<prm_technique<<" technique2="<<technique);
    }
#endif
    _hash_technique = UTIL::easy_hash(technique.c_str());
    strcpy(_technique, technique2.c_str());
}

MassMorphMeshActor::~MassMorphMeshActor() {
    delete _pMorpher;
}
