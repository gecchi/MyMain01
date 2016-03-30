#include "jp/ggaf/dxcore/actor/GgafDxMassMeshActor.h"

#include "jp/ggaf/dxcore/GgafDxGod.h"
#include "jp/ggaf/dxcore/exception/GgafDxCriticalException.h"
#include "jp/ggaf/dxcore/util/GgafDxUtil.h"
#include "jp/ggaf/dxcore/effect/GgafDxMassMeshEffect.h"
#include "jp/ggaf/dxcore/model/GgafDxMassMeshModel.h"
#include "jp/ggaf/dxcore/scene/GgafDxSpacetime.h"

using namespace GgafCore;
using namespace GgafDxCore;

GgafDxMassMeshActor::GgafDxMassMeshActor(const char* prm_name,
                                         const char* prm_model_id,
                                         const char* prm_effect_id,
                                         const char* prm_technique,
                                         GgafStatus* prm_pStat,
                                         GgafDxChecker* prm_pChecker) :

                                             GgafDxMassActor(prm_name,
                                                             prm_model_id,
                                                             "t",
                                                             prm_effect_id,
                                                             "t",
                                                             prm_technique,
                                                             prm_pStat,
                                                             prm_pChecker),
_pMassMeshModel((GgafDxMassMeshModel*)_pModel),
_pMassMeshEffect((GgafDxMassMeshEffect*)_pEffect) {
    _obj_class |= Obj_GgafDxMassMeshActor;
    _class_name = "GgafDxMassMeshActor";
    defineRotMvWorldMatrix(UTIL::setWorldMatrix_RxRzRyMv); //デフォルトの回転×移動の変換行列
}

GgafDxMassMeshActor::GgafDxMassMeshActor(const char* prm_name,
                                         const char* prm_model_id,
                                         const char* prm_model_type,
                                         const char* prm_effect_id,
                                         const char* prm_effect_type,
                                         const char* prm_technique,
                                         GgafStatus* prm_pStat,
                                         GgafDxChecker* prm_pChecker) :

                                             GgafDxMassActor(prm_name,
                                                             prm_model_id,
                                                             prm_model_type,
                                                             prm_effect_id,
                                                             prm_effect_type,
                                                             prm_technique,
                                                             prm_pStat,
                                                             prm_pChecker),
_pMassMeshModel((GgafDxMassMeshModel*)_pModel),
_pMassMeshEffect((GgafDxMassMeshEffect*)_pEffect) {

    _obj_class |= Obj_GgafDxMassMeshActor;
    _class_name = "GgafDxMassMeshActor";
    defineRotMvWorldMatrix(UTIL::setWorldMatrix_RxRzRyMv); //デフォルトの回転×移動の変換行列
}

GgafDxMassMeshActor::~GgafDxMassMeshActor() {
}
