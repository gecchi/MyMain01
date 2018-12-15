#include "jp/ggaf/dxcore/actor/GgafDxMassPointSpriteActor.h"

#include "jp/ggaf/dxcore/exception/GgafDxCriticalException.h"
#include "jp/ggaf/dxcore/effect/GgafDxMassPointSpriteEffect.h"
#include "jp/ggaf/dxcore/model/GgafDxMassPointSpriteModel.h"
#include "jp/ggaf/dxcore/manager/GgafDxTextureConnection.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxUvFlipper.h"
#include "jp/ggaf/dxcore/scene/GgafDxSpacetime.h"
#include "jp/ggaf/dxcore/util/GgafDxUtil.h"

using namespace GgafCore;
using namespace GgafDxCore;

GgafDxMassPointSpriteActor::GgafDxMassPointSpriteActor(const char* prm_name,
                                                       const char* prm_model_id,
                                                       const char* prm_effect_id,
                                                       const char* prm_technique,
                                                       GgafStatus* prm_pStat,
                                                       GgafDxChecker* prm_pChecker) :

                                                         GgafDxMassActor(prm_name,
                                                                         prm_model_id,
                                                                         TYPE_MASSPOINTSPRITE_MODEL,
                                                                         prm_effect_id,
                                                                         TYPE_MASSPOINTSPRITE_EFFECT,
                                                                         prm_technique,
                                                                         prm_pStat,
                                                                         prm_pChecker),
_pMassPointSpriteModel((GgafDxMassPointSpriteModel*)_pModel),
_pMassPointSpriteEffect((GgafDxMassPointSpriteEffect*)_pEffect),
_pUvFlipper(NEW GgafDxUvFlipper(getModel()->getDefaultTextureConnection()->peek()))
{
    _obj_class |= Obj_GgafDxMassPointSpriteActor;
    _class_name = "GgafDxMassPointSpriteActor";
    defineRotMvWorldMatrix(UTIL::setWorldMatrix_RxRzRyMv); //デフォルトの回転×移動の変換行列
    _pUvFlipper->locatePatternNo(_pMassPointSpriteModel->_texture_split_rowcol,
                             _pMassPointSpriteModel->_texture_split_rowcol );
    _pUvFlipper->setActivePtn(0);
    _pUvFlipper->exec(NOT_ANIMATED, 1);
    setZEnableDraw(false);
    setZWriteEnable(false);
}

GgafDxMassPointSpriteActor::~GgafDxMassPointSpriteActor() {
    delete _pUvFlipper;
}
