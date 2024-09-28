#include "jp/ggaf/dx/actor/MassMeshActor.h"

#include "jp/ggaf/dx/Caretaker.h"
#include "jp/ggaf/dx/exception/CriticalException.h"
#include "jp/ggaf/dx/util/Util.h"
#include "jp/ggaf/dx/effect/MassMeshEffect.h"
#include "jp/ggaf/dx/model/MassMeshModel.h"
#include "jp/ggaf/dx/scene/Spacetime.h"


using namespace GgafDx;

MassMeshActor::MassMeshActor(const char* prm_name,
                             const char* prm_model,
                             const char* prm_effect_id,
                             const char* prm_technique) :

                                 MassActor(prm_name,
                                           prm_model,
                                           TYPE_MASSMESH_MODEL,
                                           prm_effect_id,
                                           TYPE_MASSMESH_EFFECT,
                                           prm_technique),
_pMassMeshModel((MassMeshModel*)_pModel),
_pMassMeshEffect((MassMeshEffect*)_pEffect)
{
    _obj_class |= Obj_GgafDx_MassMeshActor;
    _class_name = "MassMeshActor";
    defineRotMvWorldMatrix(UTIL::setWorldMatrix_RxRzRyMv); //デフォルトの回転×移動の変換行列
}

MassMeshActor::MassMeshActor(const char* prm_name,
                             const char* prm_model,
                             const char prm_model_type,
                             const char* prm_effect_id,
                             const char prm_effect_type,
                             const char* prm_technique) :

                                 MassActor(prm_name,
                                           prm_model,
                                           prm_model_type,
                                           prm_effect_id,
                                           prm_effect_type,
                                           prm_technique),
_pMassMeshModel((MassMeshModel*)_pModel),
_pMassMeshEffect((MassMeshEffect*)_pEffect) {

    _obj_class |= Obj_GgafDx_MassMeshActor;
    _class_name = "MassMeshActor";
    defineRotMvWorldMatrix(UTIL::setWorldMatrix_RxRzRyMv); //デフォルトの回転×移動の変換行列
}

void MassMeshActor::changeModelByIndex(int prm_model_index) {
    MassActor::changeModelByIndex(prm_model_index);
    _pMassMeshModel = (MassMeshModel*)_pModel;
}

MassMeshActor::~MassMeshActor() {
}
