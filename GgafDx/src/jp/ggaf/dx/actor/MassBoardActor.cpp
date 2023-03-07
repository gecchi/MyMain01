#include "jp/ggaf/dx/actor/MassBoardActor.h"

#include "jp/ggaf/dx/actor/supporter/UvFlipper.h"
#include "jp/ggaf/dx/effect/MassBoardEffect.h"
#include "jp/ggaf/dx/exception/CriticalException.h"
#include "jp/ggaf/dx/manager/TextureConnection.h"
#include "jp/ggaf/dx/model/MassBoardModel.h"
#include "jp/ggaf/dx/scene/Spacetime.h"
#include "jp/ggaf/dx/util/GeoElem.h"


using namespace GgafDx;

MassBoardActor::MassBoardActor(const char* prm_name,
                               const char* prm_model,
                               const char* prm_effect_id,
                               const char* prm_technique,
                               CollisionChecker* prm_pChecker) :

                                   MassActor(prm_name,
                                             prm_model,
                                             TYPE_MASSBOARD_MODEL,
                                             prm_effect_id,
                                             TYPE_MASSBOARD_EFFECT,
                                             prm_technique,
                                             prm_pChecker) ,
                                   IAlignAbleActor(),
_pMassBoardModel((MassBoardModel*)_pModel),
_pMassBoardEffect((MassBoardEffect*)_pEffect),
_pUvFlipper(NEW UvFlipper())
{
    _obj_class |= Obj_GgafDx_MassBoardActor | Obj_GgafDx_IAlignAbleActor;
    _class_name = "MassBoardActor";
    _pUvFlipper->locatePatternNo(_pMassBoardModel);
    _align = ALIGN_LEFT;
    _valign = VALIGN_TOP;
    _alpha = 1.0f;

    _is_fix_2D = true;
    _pFunc_calc_rot_mv_world_matrix = nullptr;
    setZEnableDraw(false);
    setZWriteEnable(false);
    setSpecialRenderDepthNear(0); //特別な最前面レンダリング（一番最後に描画）
}

void MassBoardActor::setPositionAt(const GeometricActor* prm_pActor) {
    _x = prm_pActor->_x;
    _y = prm_pActor->_y;
}

void MassBoardActor::setPositionAt(const GeoElem* prm_pGeoElem) {
    _x = prm_pGeoElem->x;
    _y = prm_pGeoElem->y;
}

//void MassBoardActor::setAlign(Align prm_align, Valign prm_valign) {
//    _align = prm_align;
//    _valign = prm_valign;
//}

//void MassBoardActor::setAlign(Align prm_align) {
//    _align = prm_align;
//}
//
//void MassBoardActor::setValign(Valign prm_valign) {
//    _valign = prm_valign;
//}
//
void MassBoardActor::setScale(scale s) {
    _sx = s;
    _sy = s;
}

void MassBoardActor::setScale(scale sx, scale sy) {
    _sx = sx;
    _sy = sy;
}

void MassBoardActor::setScale(scale sx, scale sy, scale sz) {
    _sx = sx;
    _sy = sy;
    _sz = sz; //_szは2Dでは使用されないが、Scaler::behave() 内の判定で役に立つ。
}

void MassBoardActor::setScaleR(float prm_rate) {
    _sx = R_SC(prm_rate);
    _sy = R_SC(prm_rate);
}

void MassBoardActor::setScaleR(float prm_x_rate, float prm_y_rate) {
    _sx = R_SC(prm_x_rate);
    _sy = R_SC(prm_y_rate);
}

void MassBoardActor::setScaleR(float prm_x_rate, float prm_y_rate, float prm_z_rate) {
    _sx = R_SC(prm_x_rate);
    _sy = R_SC(prm_y_rate);
    _sz = R_SC(prm_z_rate); //_szは2Dでは使用されないが、Scaler::behave() 内の判定で役に立つ。
}

//float MassBoardActor::getModelWidth() {
//    return _pMassBoardModel->_model_width_px;
//}
//
//float MassBoardActor::getModelHeight() {
//    return _pMassBoardModel->_model_height_px;
//}

void MassBoardActor::changeModelByIndex(int prm_model_index) {
    MassActor::changeModelByIndex(prm_model_index);
    _pMassBoardModel = (MassBoardModel*)_pModel;
}

MassBoardActor::~MassBoardActor() {
    delete _pUvFlipper;
}
