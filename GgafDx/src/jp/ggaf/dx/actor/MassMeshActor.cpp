#include "jp/ggaf/dx/actor/MassMeshActor.h"

#include "jp/ggaf/dx/God.h"
#include "jp/ggaf/dx/exception/CriticalException.h"
#include "jp/ggaf/dx/util/Util.h"
#include "jp/ggaf/dx/effect/MassMeshEffect.h"
#include "jp/ggaf/dx/model/MassMeshModel.h"
#include "jp/ggaf/dx/scene/Spacetime.h"


using namespace GgafDx;

MassMeshActor::MassMeshActor(const char* prm_name,
                                         const char* prm_model_id,
                                         const char* prm_effect_id,
                                         const char* prm_technique,
                                         GgafCore::Status* prm_pStat,
                                         Checker* prm_pChecker) :

                                             MassActor(prm_name,
                                                             prm_model_id,
                                                             TYPE_MASSMESH_MODEL,
                                                             prm_effect_id,
                                                             TYPE_MASSMESH_EFFECT,
                                                             prm_technique,
                                                             prm_pStat,
                                                             prm_pChecker),
_pMassMeshModel((MassMeshModel*)_pModel),
_pMassMeshEffect((MassMeshEffect*)_pEffect)
{
    _obj_class |= Obj_GgafDx_MassMeshActor;
    _class_name = "MassMeshActor";
    defineRotMvWorldMatrix(UTIL::setWorldMatrix_RxRzRyMv); //�f�t�H���g�̉�]�~�ړ��̕ϊ��s��
}

MassMeshActor::MassMeshActor(const char* prm_name,
                                         const char* prm_model_id,
                                         const char prm_model_type,
                                         const char* prm_effect_id,
                                         const char prm_effect_type,
                                         const char* prm_technique,
                                         GgafCore::Status* prm_pStat,
                                         Checker* prm_pChecker) :

                                             MassActor(prm_name,
                                                             prm_model_id,
                                                             prm_model_type,
                                                             prm_effect_id,
                                                             prm_effect_type,
                                                             prm_technique,
                                                             prm_pStat,
                                                             prm_pChecker),
_pMassMeshModel((MassMeshModel*)_pModel),
_pMassMeshEffect((MassMeshEffect*)_pEffect) {

    _obj_class |= Obj_GgafDx_MassMeshActor;
    _class_name = "MassMeshActor";
    defineRotMvWorldMatrix(UTIL::setWorldMatrix_RxRzRyMv); //�f�t�H���g�̉�]�~�ړ��̕ϊ��s��
}

MassMeshActor::~MassMeshActor() {
}
