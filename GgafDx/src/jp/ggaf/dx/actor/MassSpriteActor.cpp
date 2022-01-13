#include "jp/ggaf/dx/actor/MassSpriteActor.h"

#include "jp/ggaf/dx/exception/CriticalException.h"
#include "jp/ggaf/dx/effect/MassSpriteEffect.h"
#include "jp/ggaf/dx/model/MassSpriteModel.h"
#include "jp/ggaf/dx/manager/TextureConnection.h"
#include "jp/ggaf/dx/actor/supporter/UvFlipper.h"
#include "jp/ggaf/dx/scene/Spacetime.h"
#include "jp/ggaf/dx/util/Util.h"


using namespace GgafDx;

MassSpriteActor::MassSpriteActor(const char* prm_name,
                                 const char* prm_model,
                                 const char* prm_effect_id,
                                 const char* prm_technique,
                                 Checker* prm_pChecker) :

                                       MassActor(prm_name,
                                                 prm_model,
                                                 TYPE_MASSACTOR_MODEL,
                                                 prm_effect_id,
                                                 TYPE_MASSSPRITE_EFFECT,
                                                 prm_technique,
                                                 prm_pChecker) ,
_pMassSpriteModel((MassSpriteModel*)_pModel),
_pMassSpriteEffect((MassSpriteEffect*)_pEffect),
_pUvFlipper(NEW UvFlipper(getModel()->getDefaultTextureConnection()->peek()))
{
    _obj_class |= Obj_GgafDx_MassSpriteActor;
    _class_name = "MassSpriteActor";
    _pUvFlipper->locatePatternNo(_pMassSpriteModel->_col_texture_split,
                             _pMassSpriteModel->_row_texture_split );
    _pUvFlipper->setActivePtn(0);
    _pUvFlipper->exec(NOT_ANIMATED, 1);

    defineRotMvWorldMatrix(UTIL::setWorldMatrix_RxRzRyMv); //デフォルトの回転×移動の変換行列
//    _align = ALIGN_CENTER;
//    _valign = VALIGN_MIDDLE;
}

//void MassSpriteActor::setAlign(Align prm_align, Valign prm_valign) {
//    _align = prm_align;
//    _valign = prm_valign;
//}
//
//void MassSpriteActor::setAlign(Align prm_align) {
//    _align = prm_align;
//}
//
//void MassSpriteActor::setValign(Valign prm_valign) {
//    _valign = prm_valign;
//}

MassSpriteActor::~MassSpriteActor() {
    delete _pUvFlipper;
}
