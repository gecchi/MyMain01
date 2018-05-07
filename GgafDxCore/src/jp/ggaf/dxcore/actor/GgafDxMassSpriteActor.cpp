#include "jp/ggaf/dxcore/actor/GgafDxMassSpriteActor.h"

#include "jp/ggaf/dxcore/exception/GgafDxCriticalException.h"
#include "jp/ggaf/dxcore/effect/GgafDxMassSpriteEffect.h"
#include "jp/ggaf/dxcore/model/GgafDxMassSpriteModel.h"
#include "jp/ggaf/dxcore/manager/GgafDxTextureConnection.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxUvFlipper.h"
#include "jp/ggaf/dxcore/scene/GgafDxSpacetime.h"
#include "jp/ggaf/dxcore/util/GgafDxUtil.h"

using namespace GgafCore;
using namespace GgafDxCore;

GgafDxMassSpriteActor::GgafDxMassSpriteActor(const char* prm_name,
                                             const char* prm_model_id,
                                             const char* prm_effect_id,
                                             const char* prm_technique,
                                             GgafStatus* prm_pStat,
                                             GgafDxChecker* prm_pChecker) :

                                                   GgafDxMassActor(prm_name,
                                                                   prm_model_id,
                                                                   TYPE_MESHSPRITE_MODEL,
                                                                   prm_effect_id,
                                                                   TYPE_MASSSPRITE_EFFECT,
                                                                   prm_technique,
                                                                   prm_pStat,
                                                                   prm_pChecker) ,
_pMassSpriteModel((GgafDxMassSpriteModel*)_pModel),
_pMassSpriteEffect((GgafDxMassSpriteEffect*)_pEffect),
_pUvFlipper(NEW GgafDxUvFlipper(getModel()->getDefaultTextureConnection()->peek()))
{
    _obj_class |= Obj_GgafDxMassSpriteActor;
    _class_name = "GgafDxMassSpriteActor";
    _pUvFlipper->setRotation(_pMassSpriteModel->_col_texture_split,
                             _pMassSpriteModel->_row_texture_split );
    _pUvFlipper->setActivePtn(0);
    _pUvFlipper->exec(NOT_ANIMATED, 1);

    defineRotMvWorldMatrix(UTIL::setWorldMatrix_RxRzRyMv); //デフォルトの回転×移動の変換行列
    _align = ALIGN_CENTER;
    _valign = VALIGN_MIDDLE;
}

void GgafDxMassSpriteActor::setAlign(GgafDxAlign prm_align, GgafDxValign prm_valign) {
    _align = prm_align;
    _valign = prm_valign;
}

void GgafDxMassSpriteActor::setAlign(GgafDxAlign prm_align) {
    _align = prm_align;
}

void GgafDxMassSpriteActor::setValign(GgafDxValign prm_valign) {
    _valign = prm_valign;
}

GgafDxMassSpriteActor::~GgafDxMassSpriteActor() {
    delete _pUvFlipper;
}
