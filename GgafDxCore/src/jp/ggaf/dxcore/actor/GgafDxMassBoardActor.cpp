#include "jp/ggaf/dxcore/actor/GgafDxMassBoardActor.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxUvFlipper.h"
#include "jp/ggaf/dxcore/effect/GgafDxMassBoardEffect.h"
#include "jp/ggaf/dxcore/exception/GgafDxCriticalException.h"
#include "jp/ggaf/dxcore/manager/GgafDxTextureConnection.h"
#include "jp/ggaf/dxcore/model/GgafDxMassBoardModel.h"
#include "jp/ggaf/dxcore/scene/GgafDxSpacetime.h"
#include "jp/ggaf/dxcore/util/GgafDxGeoElem.h"

using namespace GgafCore;
using namespace GgafDxCore;

GgafDxMassBoardActor::GgafDxMassBoardActor(const char* prm_name,
                                           const char* prm_model_id,
                                           const char* prm_effect_id,
                                           const char* prm_technique) :

                                               GgafDxMassActor(prm_name,
                                                               prm_model_id,
                                                               "w",
                                                               prm_effect_id,
                                                               "w",
                                                               prm_technique,
                                                               nullptr,
                                                               nullptr) ,
_pMassBoardModel((GgafDxMassBoardModel*)_pModel),
_pMassBoardEffect((GgafDxMassBoardEffect*)_pEffect),
_pUvFlipper(NEW GgafDxUvFlipper(getModel()->getDefaultTextureConnection()->peek())) {

    _obj_class |= Obj_GgafDxMassBoardActor;
    _class_name = "GgafDxMassBoardActor";
    _pUvFlipper->setRotation(_pMassBoardModel->_col_texture_split,
                             _pMassBoardModel->_row_texture_split
                            );
    _pUvFlipper->setActivePtn(0);
    _pUvFlipper->exec(NOT_ANIMATED, 1);

    _width_px = (int)(_pMassBoardModel->_model_width_px); //幅(px)
    _height_px = (int)(_pMassBoardModel->_model_height_px); //高さ(px)
    _harf_width_px = _width_px/2;
    _harf_height_px = _height_px/2;
    _align = ALIGN_LEFT;
    _valign = VALIGN_TOP;
    _alpha = 1.0f;

    _is_2D = true;
    _pFunc_calc_rot_mv_world_matrix = nullptr;

    setZEnableDraw(false);
    setZWriteEnable(false);

    _z = 0;
}

void GgafDxMassBoardActor::positionAs(const GgafDxGeometricActor* prm_pActor) {
    _x = prm_pActor->_x;
    _y = prm_pActor->_y;
}

void GgafDxMassBoardActor::positionAs(const GgafDxGeoElem* prm_pGeoElem) {
    _x = prm_pGeoElem->x;
    _y = prm_pGeoElem->y;
}

void GgafDxMassBoardActor::setAlign(GgafDxAlign prm_align, GgafDxValign prm_valign) {
    _align = prm_align;
    _valign = prm_valign;
}

void GgafDxMassBoardActor::setAlign(GgafDxAlign prm_align) {
    _align = prm_align;
}

void GgafDxMassBoardActor::setValign(GgafDxValign prm_valign) {
    _valign = prm_valign;
}

void GgafDxMassBoardActor::setScale(scale s) {
    _sx = s;
    _sy = s;
}

void GgafDxMassBoardActor::setScale(scale sx, scale sy) {
    _sx = sx;
    _sy = sy;
}

void GgafDxMassBoardActor::setScale(scale sx, scale sy, scale sz) {
    _sx = sx;
    _sy = sy;
    _sz = sz; //_szは2Dでは使用されないが、GgafDxScaler::behave() 内の判定で役に立つ。
}

void GgafDxMassBoardActor::setScaleR(float prm_rate) {
    _sx = R_SC(prm_rate);
    _sy = R_SC(prm_rate);
}

void GgafDxMassBoardActor::setScaleR(float prm_x_rate, float prm_y_rate) {
    _sx = R_SC(prm_x_rate);
    _sy = R_SC(prm_y_rate);
}

void GgafDxMassBoardActor::setScaleR(float prm_x_rate, float prm_y_rate, float prm_z_rate) {
    _sx = R_SC(prm_x_rate);
    _sy = R_SC(prm_y_rate);
    _sz = R_SC(prm_z_rate); //_szは2Dでは使用されないが、GgafDxScaler::behave() 内の判定で役に立つ。
}

float GgafDxMassBoardActor::getModelWidth() {
    return _pMassBoardModel->_model_width_px;
}

float GgafDxMassBoardActor::getModelHeight() {
    return _pMassBoardModel->_model_height_px;
}

GgafDxMassBoardActor::~GgafDxMassBoardActor() {
    delete _pUvFlipper;
}
