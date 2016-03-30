#include "jp/ggaf/dxcore/actor/GgafDxMassActor.h"

#include "jp/ggaf/dxcore/GgafDxGod.h"
#include "jp/ggaf/dxcore/exception/GgafDxCriticalException.h"
#include "jp/ggaf/dxcore/util/GgafDxUtil.h"
#include "jp/ggaf/dxcore/effect/GgafDxMassEffect.h"
#include "jp/ggaf/dxcore/model/GgafDxMassModel.h"
#include "jp/ggaf/dxcore/scene/GgafDxSpacetime.h"

using namespace GgafCore;
using namespace GgafDxCore;

GgafDxMassActor::GgafDxMassActor(const char* prm_name,
                                 const char* prm_model_id,
                                 const char* prm_effect_id,
                                 const char* prm_technique,
                                 GgafStatus* prm_pStat,
                                 GgafDxChecker* prm_pChecker) :

                                   GgafDxFigureActor(prm_name,
                                                     prm_model_id,
                                                     "t",
                                                     prm_effect_id,
                                                     "t",
                                                     prm_technique,
                                                     prm_pStat,
                                                     prm_pChecker),
_pMassModel((GgafDxMassModel*)_pModel),
_pMassEffect((GgafDxMassEffect*)_pEffect) {
    _obj_class |= Obj_GgafDxMassActor;
    _class_name = "GgafDxMassActor";
    defineRotMvWorldMatrix(UTIL::setWorldMatrix_RxRzRyMv); //デフォルトの回転×移動の変換行列
}

GgafDxMassActor::GgafDxMassActor(const char* prm_name,
                                 const char* prm_model_id,
                                 const char* prm_model_type,
                                 const char* prm_effect_id,
                                 const char* prm_effect_type,
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
_pMassModel((GgafDxMassModel*)_pModel),
_pMassEffect((GgafDxMassEffect*)_pEffect) {

    _obj_class |= Obj_GgafDxMassActor;
    _class_name = "GgafDxMassActor";
    defineRotMvWorldMatrix(UTIL::setWorldMatrix_RxRzRyMv); //デフォルトの回転×移動の変換行列
}


GgafDxMassActor::~GgafDxMassActor() {
}
