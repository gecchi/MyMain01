#include "jp/ggaf/dx/actor/MassActor.h"

#include "jp/ggaf/dx/God.h"
#include "jp/ggaf/dx/exception/CriticalException.h"
#include "jp/ggaf/dx/util/Util.h"
#include "jp/ggaf/dx/effect/MassEffect.h"
#include "jp/ggaf/dx/model/MassModel.h"
#include "jp/ggaf/dx/scene/Spacetime.h"


using namespace GgafDx;

MassActor::MassActor(const char* prm_name,
                     const char* prm_model,
                     const char prm_model_type,
                     const char* prm_effect_id,
                     const char prm_effect_type,
                     const char* prm_technique,
                     Checker* prm_pChecker) :

                       FigureActor(prm_name,
                                   prm_model,
                                   prm_model_type,
                                   prm_effect_id,
                                   prm_effect_type,
                                   prm_technique,
                                   prm_pChecker),
_pMassModel((MassModel*)_pModel),
_pMassEffect((MassEffect*)_pEffect) {

    _obj_class |= Obj_GgafDx_MassActor;
    _class_name = "MassActor";
    defineRotMvWorldMatrix(UTIL::setWorldMatrix_RxRzRyMv); //�f�t�H���g�̉�]�~�ړ��̕ϊ��s��
}


MassActor::~MassActor() {
}
