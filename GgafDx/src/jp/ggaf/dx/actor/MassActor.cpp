#include "jp/ggaf/dx/actor/MassActor.h"

#include "jp/ggaf/dx/Caretaker.h"
#include "jp/ggaf/dx/exception/CriticalException.h"
#include "jp/ggaf/dx/util/Util.h"
#include "jp/ggaf/dx/model/MassModel.h"
#include "jp/ggaf/dx/scene/Spacetime.h"


using namespace GgafDx;

MassActor::MassActor(const char* prm_name,
                     const char* prm_model,
                     const char prm_model_type,
                     const char* prm_effect_id,
                     const char prm_effect_type,
                     const char* prm_technique) :

                       FigureActor(prm_name,
                                   prm_model,
                                   prm_model_type,
                                   prm_effect_id,
                                   prm_effect_type,
                                   prm_technique),
_pMassModel((MassModel*)_pModel) {

    _obj_class |= Obj_GgafDx_MassActor;
    _class_name = "MassActor";
    defineRotMvWorldMatrix(UTIL::setWorldMatrix_RxRzRyMv); //デフォルトの回転×移動の変換行列
}


MassActor::~MassActor() {
}
