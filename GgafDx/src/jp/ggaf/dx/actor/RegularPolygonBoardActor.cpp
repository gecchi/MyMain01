#include "jp/ggaf/dx/actor/RegularPolygonBoardActor.h"

#include "jp/ggaf/dx/exception/CriticalException.h"
#include "jp/ggaf/dx/actor/supporter/UvFlipper.h"
#include "jp/ggaf/dx/model/RegularPolygonBoardModel.h"
#include "jp/ggaf/dx/effect/RegularPolygonBoardEffect.h"
#include "jp/ggaf/dx/manager/TextureConnection.h"
#include "jp/ggaf/dx/util/Util.h"


using namespace GgafDx;

RegularPolygonBoardActor::RegularPolygonBoardActor(const char* prm_name,
                                                   const char* prm_model,
                                                   const char* prm_effect_id,
                                                   const char* prm_technique) :

                                                       FigureActor(prm_name,
                                                                   prm_model,
                                                                   TYPE_REGULARPOLYGONBOARD_MODEL,
                                                                   prm_effect_id,
                                                                   TYPE_REGULARPOLYGONBOARD_EFFECT,
                                                                   prm_technique),

                                                       IAlignAbleActor(),
_pRegularPolygonBoardModel((RegularPolygonBoardModel*)_pModel),
_pRegularPolygonBoardEffect((RegularPolygonBoardEffect*)_pEffect) ,
_pUvFlipper(NEW UvFlipper()) {

    _obj_class |= Obj_GgafDx_RegularPolygonBoardActor | Obj_GgafDx_IAlignAbleActor;
    _class_name = "RegularPolygonBoardActor";
    _pUvFlipper->locatePatternNo(_pRegularPolygonBoardModel);
    _align = ALIGN_LEFT;
    _valign = VALIGN_TOP;
    _is_fix_2D = true;
    _pFunc_calc_rot_mv_world_matrix = nullptr;
    _draw_fan_num = _pRegularPolygonBoardModel->_angle_num;
    setCullingMode(_pRegularPolygonBoardModel->_drawing_order == 1 ?  D3DCULL_CCW : D3DCULL_CW);
    _circumference_begin_position = 0;
    useZBufferDrawing(false);
    setZBufferWriteEnable(false);
    setSpecialRenderDepthNear(0); //特別な最前面レンダリング（一番最後に描画）
}

void RegularPolygonBoardActor::processDraw() {
    ID3DXEffect* const pID3DXEffect = _pRegularPolygonBoardEffect->_pID3DXEffect;

    HRESULT hr;
    hr = pID3DXEffect->SetFloat(_pRegularPolygonBoardEffect->_h_transformed_x, float(C_PX(_x)));
    checkDxException(hr, D3D_OK, "SetFloat(_h_transformed_x) に失敗しました。3");
    hr = pID3DXEffect->SetFloat(_pRegularPolygonBoardEffect->_h_transformed_y, float(C_PX(_y)));
    checkDxException(hr, D3D_OK, "SetFloat(_h_transformed_y) に失敗しました。3");

    if (_align == ALIGN_RIGHT) {
        hr = pID3DXEffect->SetFloat(_pRegularPolygonBoardEffect->_h_local_left_top_x, (float)(-_pRegularPolygonBoardModel->_model_width_px));
    } else if (_align == ALIGN_CENTER) {
        hr = pID3DXEffect->SetFloat(_pRegularPolygonBoardEffect->_h_local_left_top_x, (float)(-_pRegularPolygonBoardModel->_model_width_px*0.5));
    } else { //ALIGN_LEFT
        hr = pID3DXEffect->SetFloat(_pRegularPolygonBoardEffect->_h_local_left_top_x, 0.0f);
    }
    checkDxException(hr, D3D_OK, "SetFloat(_h_local_left_top_x) に失敗しました。");
    if (_valign == VALIGN_BOTTOM) {
        hr = pID3DXEffect->SetFloat(_pRegularPolygonBoardEffect->_h_local_left_top_y, (float)(-_pRegularPolygonBoardModel->_model_height_px));
    } else if (_valign == VALIGN_MIDDLE) {
        hr = pID3DXEffect->SetFloat(_pRegularPolygonBoardEffect->_h_local_left_top_y, (float)(-_pRegularPolygonBoardModel->_model_height_px*0.5));
    } else { //VALIGN_TOP
        hr = pID3DXEffect->SetFloat(_pRegularPolygonBoardEffect->_h_local_left_top_y, 0.0f);
    }
    checkDxException(hr, D3D_OK, "SetFloat(_h_local_left_top_y) に失敗しました。");
    hr = pID3DXEffect->SetFloat(_pRegularPolygonBoardEffect->_h_depth_z, float(C_PX(_z)));
    checkDxException(hr, D3D_OK, "SetFloat(_h_depth_z) に失敗しました。");
    hr = pID3DXEffect->SetValue(_pRegularPolygonBoardEffect->_h_colMaterialDiffuse, &(_paMaterial[0].Diffuse), sizeof(D3DCOLORVALUE) );
    checkDxException(hr, D3D_OK, "SetValue(_h_colMaterialDiffuse) に失敗しました。");

    hr = pID3DXEffect->SetFloat(_pRegularPolygonBoardEffect->_h_sx, SC_R(_sx));
    checkDxException(hr, D3D_OK, "SetFloat(_sx) に失敗しました。");
    hr = pID3DXEffect->SetFloat(_pRegularPolygonBoardEffect->_h_sy, SC_R(_sy));
    checkDxException(hr, D3D_OK, "SetFloat(_sy) に失敗しました。");
    hr = pID3DXEffect->SetFloat(_pRegularPolygonBoardEffect->_h_rz, ANG_RAD(_rz));
    checkDxException(hr, D3D_OK, "SetFloat(_h_rz) に失敗しました。");

    angle a = UTIL::simplifyAng(_circumference_begin_position);
    float sin_rz = ANG_SIN(a);
    float cos_rz = ANG_COS(a);
    hr = pID3DXEffect->SetFloat(_pRegularPolygonBoardEffect->_h_sin_rz, sin_rz);
    checkDxException(hr, D3D_OK, "SetFloat(_h_sin_rz) に失敗しました。");
    hr = pID3DXEffect->SetFloat(_pRegularPolygonBoardEffect->_h_cos_rz, cos_rz);
    checkDxException(hr, D3D_OK, "SetFloat(_h_cos_rz) に失敗しました。");

    _pRegularPolygonBoardModel->RegularPolygonBoardModel::draw(this);
}

void RegularPolygonBoardActor::setPositionAt(const GeometricActor* prm_pActor) {
    _x = prm_pActor->_x;
    _y = prm_pActor->_y;
}

void RegularPolygonBoardActor::setPositionAt(const GeoElem* prm_pGeoElem) {
    _x = prm_pGeoElem->x;
    _y = prm_pGeoElem->y;
}

void RegularPolygonBoardActor::setScale(scale s) {
    _sx = s;
    _sy = s;
}

void RegularPolygonBoardActor::setScale(scale sx, scale sy) {
    _sx = sx;
    _sy = sy;
}

void RegularPolygonBoardActor::setScale(scale sx, scale sy, scale sz) {
    _sx = sx;
    _sy = sy;
    _sz = sz; //_szは2Dでは使用されないが、Scaler::behave() 内の判定で役に立つ。
}

void RegularPolygonBoardActor::setScaleR(float prm_rate) {
    _sx = R_SC(prm_rate);
    _sy = R_SC(prm_rate);
}

void RegularPolygonBoardActor::setScaleR(float prm_x_rate, float prm_y_rate) {
    _sx = R_SC(prm_x_rate);
    _sy = R_SC(prm_y_rate);
}

void RegularPolygonBoardActor::setScaleR(float prm_x_rate, float prm_y_rate, float prm_z_rate) {
    _sx = R_SC(prm_x_rate);
    _sy = R_SC(prm_y_rate);
    _sz = R_SC(prm_z_rate); //_szは2Dでは使用されないが、Scaler::behave() 内の判定で役に立つ。
}

void RegularPolygonBoardActor::changeModelByIndex(int prm_model_index) {
    FigureActor::changeModelByIndex(prm_model_index);
    _pRegularPolygonBoardModel = (RegularPolygonBoardModel*)_pModel;
}

RegularPolygonBoardActor::~RegularPolygonBoardActor() {
    delete _pUvFlipper;
}
