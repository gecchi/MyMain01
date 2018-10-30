#include "jp/ggaf/dxcore/actor/GgafDxRegularPolygonBoardActor.h"

#include "jp/ggaf/dxcore/exception/GgafDxCriticalException.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxUvFlipper.h"
#include "jp/ggaf/dxcore/model/GgafDxRegularPolygonBoardModel.h"
#include "jp/ggaf/dxcore/effect/GgafDxRegularPolygonBoardEffect.h"
#include "jp/ggaf/dxcore/manager/GgafDxTextureConnection.h"
#include "jp/ggaf/dxcore/util/GgafDxUtil.h"

using namespace GgafCore;
using namespace GgafDxCore;

GgafDxRegularPolygonBoardActor::GgafDxRegularPolygonBoardActor(const char* prm_name,
                                   const char* prm_model_id,
                                   const char* prm_effect_id,
                                   const char* prm_technique) :

                                       GgafDxFigureActor(prm_name,
                                                         prm_model_id,
                                                         TYPE_REGULARPOLYGONBOARD_MODEL,
                                                         prm_effect_id,
                                                         TYPE_REGULARPOLYGONBOARD_EFFECT,
                                                         prm_technique,
                                                         nullptr,
                                                         nullptr) ,
_pRegularPolygonBoardModel((GgafDxRegularPolygonBoardModel*)_pModel),
_pRegularPolygonBoardEffect((GgafDxRegularPolygonBoardEffect*)_pEffect) ,
_pUvFlipper(NEW GgafDxUvFlipper(getModel()->getDefaultTextureConnection()->peek())) {

    _obj_class |= Obj_GgafDxRegularPolygonBoardActor;
    _class_name = "GgafDxRegularPolygonBoardActor";
    _pUvFlipper->setRotation(_pRegularPolygonBoardModel->_col_texture_split,
                             _pRegularPolygonBoardModel->_row_texture_split );
    _pUvFlipper->setActivePtn(0);
    _pUvFlipper->exec(NOT_ANIMATED, 1);
    _align = ALIGN_LEFT;
    _valign = VALIGN_TOP;
    _alpha = 1.0f;
    _is_2D = true;
    _pFunc_calc_rot_mv_world_matrix = nullptr;
    _z = 0;
    _draw_fan_num = _pRegularPolygonBoardModel->_angle_num;
    _cull_mode = _pRegularPolygonBoardModel->_drawing_order == 1 ?  D3DCULL_CCW : D3DCULL_CW;
    _circumference_begin_position = 0;
    setZEnableDraw(false);
    setZWriteEnable(false);
}

void GgafDxRegularPolygonBoardActor::processDraw() {
    ID3DXEffect* const pID3DXEffect = _pRegularPolygonBoardEffect->_pID3DXEffect;

    HRESULT hr;
    hr = pID3DXEffect->SetFloat(_pRegularPolygonBoardEffect->_h_transformed_x, float(C_PX(_x)));
    checkDxException(hr, D3D_OK, "SetFloat(_h_transformed_x) ‚ÉŽ¸”s‚µ‚Ü‚µ‚½B3");
    hr = pID3DXEffect->SetFloat(_pRegularPolygonBoardEffect->_h_transformed_y, float(C_PX(_y)));
    checkDxException(hr, D3D_OK, "SetFloat(_h_transformed_y) ‚ÉŽ¸”s‚µ‚Ü‚µ‚½B3");

    if (_align == ALIGN_RIGHT) {
        hr = pID3DXEffect->SetFloat(_pRegularPolygonBoardEffect->_h_local_left_top_x, (float)(-_pRegularPolygonBoardModel->_model_width_px));
    } else if (_align == ALIGN_CENTER) {
        hr = pID3DXEffect->SetFloat(_pRegularPolygonBoardEffect->_h_local_left_top_x, (float)(-_pRegularPolygonBoardModel->_model_width_px*0.5));
    } else { //ALIGN_LEFT
        hr = pID3DXEffect->SetFloat(_pRegularPolygonBoardEffect->_h_local_left_top_x, 0.0f);
    }
    checkDxException(hr, D3D_OK, "SetFloat(_h_local_left_top_x) ‚ÉŽ¸”s‚µ‚Ü‚µ‚½B");
    if (_valign == VALIGN_BOTTOM) {
        hr = pID3DXEffect->SetFloat(_pRegularPolygonBoardEffect->_h_local_left_top_y, (float)(-_pRegularPolygonBoardModel->_model_height_px));
    } else if (_valign == VALIGN_MIDDLE) {
        hr = pID3DXEffect->SetFloat(_pRegularPolygonBoardEffect->_h_local_left_top_y, (float)(-_pRegularPolygonBoardModel->_model_height_px*0.5));
    } else { //VALIGN_TOP
        hr = pID3DXEffect->SetFloat(_pRegularPolygonBoardEffect->_h_local_left_top_y, 0.0f);
    }
    checkDxException(hr, D3D_OK, "SetFloat(_h_local_left_top_y) ‚ÉŽ¸”s‚µ‚Ü‚µ‚½B");
    hr = pID3DXEffect->SetFloat(_pRegularPolygonBoardEffect->_h_depth_z, float(C_PX(_z)));
    checkDxException(hr, D3D_OK, "SetFloat(_h_depth_z) ‚ÉŽ¸”s‚µ‚Ü‚µ‚½B");
//    hr = pID3DXEffect->SetFloat(_pRegularPolygonBoardEffect->_h_alpha, _alpha);
//    checkDxException(hr, D3D_OK, "SetFloat(_h_alpha) ‚ÉŽ¸”s‚µ‚Ü‚µ‚½B");
    hr = pID3DXEffect->SetValue(_pRegularPolygonBoardEffect->_h_colMaterialDiffuse, &(_paMaterial[0].Diffuse), sizeof(D3DCOLORVALUE) );
    checkDxException(hr, D3D_OK, "SetValue(_h_colMaterialDiffuse) ‚ÉŽ¸”s‚µ‚Ü‚µ‚½B");

    hr = pID3DXEffect->SetFloat(_pRegularPolygonBoardEffect->_h_sx, SC_R(_sx));
    checkDxException(hr, D3D_OK, "SetFloat(_sx) ‚ÉŽ¸”s‚µ‚Ü‚µ‚½B");
    hr = pID3DXEffect->SetFloat(_pRegularPolygonBoardEffect->_h_sy, SC_R(_sy));
    checkDxException(hr, D3D_OK, "SetFloat(_sy) ‚ÉŽ¸”s‚µ‚Ü‚µ‚½B");
    hr = pID3DXEffect->SetFloat(_pRegularPolygonBoardEffect->_h_rz, ANG_RAD(_rz));
    checkDxException(hr, D3D_OK, "SetFloat(_h_rz) ‚ÉŽ¸”s‚µ‚Ü‚µ‚½B");

    angle a = UTIL::simplifyAng(_circumference_begin_position);
    float sin_rz = ANG_SIN(a);
    float cos_rz = ANG_COS(a);
    checkDxException(hr, D3D_OK, "SetFloat(_h_far_rate) ‚ÉŽ¸”s‚µ‚Ü‚µ‚½B");
    hr = pID3DXEffect->SetFloat(_pRegularPolygonBoardEffect->_h_sin_rz, sin_rz);
    checkDxException(hr, D3D_OK, "SetFloat(_h_sin_rz) ‚ÉŽ¸”s‚µ‚Ü‚µ‚½B");
    hr = pID3DXEffect->SetFloat(_pRegularPolygonBoardEffect->_h_cos_rz, cos_rz);
    checkDxException(hr, D3D_OK, "SetFloat(_h_cos_rz) ‚ÉŽ¸”s‚µ‚Ü‚µ‚½B");

    _pRegularPolygonBoardModel->GgafDxRegularPolygonBoardModel::draw(this);
}

void GgafDxRegularPolygonBoardActor::setAlign(GgafDxAlign prm_align, GgafDxValign prm_valign) {
    _align = prm_align;
    _valign = prm_valign;
}
void GgafDxRegularPolygonBoardActor::setAlign(GgafDxAlign prm_align) {
    _align = prm_align;
}
void GgafDxRegularPolygonBoardActor::setValign(GgafDxValign prm_valign) {
    _valign = prm_valign;
}

void GgafDxRegularPolygonBoardActor::setPositionAt(const GgafDxGeometricActor* prm_pActor) {
    _x = prm_pActor->_x;
    _y = prm_pActor->_y;
}

void GgafDxRegularPolygonBoardActor::setPositionAt(const GgafDxGeoElem* prm_pGeoElem) {
    _x = prm_pGeoElem->x;
    _y = prm_pGeoElem->y;
}

void GgafDxRegularPolygonBoardActor::setScale(scale s) {
    _sx = s;
    _sy = s;
}

void GgafDxRegularPolygonBoardActor::setScale(scale sx, scale sy) {
    _sx = sx;
    _sy = sy;
}

void GgafDxRegularPolygonBoardActor::setScale(scale sx, scale sy, scale sz) {
    _sx = sx;
    _sy = sy;
    _sz = sz; //_sz‚Í2D‚Å‚ÍŽg—p‚³‚ê‚È‚¢‚ªAGgafDxScaler::behave() “à‚Ì”»’è‚Å–ð‚É—§‚ÂB
}

void GgafDxRegularPolygonBoardActor::setScaleR(float prm_rate) {
    _sx = R_SC(prm_rate);
    _sy = R_SC(prm_rate);
}

void GgafDxRegularPolygonBoardActor::setScaleR(float prm_x_rate, float prm_y_rate) {
    _sx = R_SC(prm_x_rate);
    _sy = R_SC(prm_y_rate);
}

void GgafDxRegularPolygonBoardActor::setScaleR(float prm_x_rate, float prm_y_rate, float prm_z_rate) {
    _sx = R_SC(prm_x_rate);
    _sy = R_SC(prm_y_rate);
    _sz = R_SC(prm_z_rate); //_sz‚Í2D‚Å‚ÍŽg—p‚³‚ê‚È‚¢‚ªAGgafDxScaler::behave() “à‚Ì”»’è‚Å–ð‚É—§‚ÂB
}

float GgafDxRegularPolygonBoardActor::getModelWidth() {
    return _pRegularPolygonBoardModel->_model_width_px;
}

float GgafDxRegularPolygonBoardActor::getModelHeight() {
    return _pRegularPolygonBoardModel->_model_height_px;
}

GgafDxRegularPolygonBoardActor::~GgafDxRegularPolygonBoardActor() {
    delete _pUvFlipper;
}
