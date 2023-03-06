#include "jp/ggaf/dx/actor/BoardActor.h"

#include "jp/ggaf/dx/exception/CriticalException.h"
#include "jp/ggaf/dx/actor/supporter/UvFlipper.h"
#include "jp/ggaf/dx/model/BoardModel.h"
#include "jp/ggaf/dx/effect/BoardEffect.h"
#include "jp/ggaf/dx/manager/TextureConnection.h"
#include "jp/ggaf/dx/util/Util.h"


using namespace GgafDx;

BoardActor::BoardActor(const char* prm_name,
                       const char* prm_model,
                       const char* prm_effect_id,
                       const char* prm_technique,
                       CollisionChecker* prm_pChecker) :

                           FigureActor(prm_name,
                                       prm_model,
                                       TYPE_BOARD_MODEL,
                                       prm_effect_id,
                                       TYPE_BOARD_EFFECT,
                                       prm_technique,
                                       prm_pChecker) ,
                           IAlignAbleActor(),
_pBoardModel((BoardModel*)_pModel),
_pBoardEffect((BoardEffect*)_pEffect) ,
_pUvFlipper(NEW UvFlipper(getModel()->getDefaultTextureConnection()->peek())) {

    _obj_class |= Obj_GgafDx_BoardActor | Obj_GgafDx_IAlignAbleActor;
    _class_name = "BoardActor";
    _pUvFlipper->locatePatternNo(_pBoardModel->_col_texture_split,
                                 _pBoardModel->_row_texture_split );
    _pUvFlipper->setActivePtn(0);
    _pUvFlipper->exec(NOT_ANIMATED, 1);
    _align = ALIGN_LEFT;
    _valign = VALIGN_TOP;
    _alpha = 1.0f;
    _is_fix_2D = true;
    _pFunc_calc_rot_mv_world_matrix = nullptr;
    setZEnableDraw(false);
    setZWriteEnable(false);
    setSpecialRenderDepthNear(0); //“Á•Ê‚ÈÅ‘O–ÊƒŒƒ“ƒ_ƒŠƒ“ƒOiˆê”ÔÅŒã‚É•`‰æj
}

void BoardActor::processDraw() {
    ID3DXEffect* const pID3DXEffect = _pBoardEffect->_pID3DXEffect;

    HRESULT hr;
    hr = pID3DXEffect->SetFloat(_pBoardEffect->_h_transformed_x, float(C_PX(_x)));
    checkDxException(hr, D3D_OK, "SetFloat(_h_transformed_x) ‚ÉŽ¸”s‚µ‚Ü‚µ‚½B3");
    hr = pID3DXEffect->SetFloat(_pBoardEffect->_h_transformed_y, float(C_PX(_y)));
    checkDxException(hr, D3D_OK, "SetFloat(_h_transformed_y) ‚ÉŽ¸”s‚µ‚Ü‚µ‚½B3");

    if (_align == ALIGN_RIGHT) {
        hr = pID3DXEffect->SetFloat(_pBoardEffect->_h_local_left_top_x, (float)(-_pBoardModel->_model_width_px));
    } else if (_align == ALIGN_CENTER) {
        hr = pID3DXEffect->SetFloat(_pBoardEffect->_h_local_left_top_x, (float)(-_pBoardModel->_model_width_px*0.5));
    } else { //ALIGN_LEFT
        hr = pID3DXEffect->SetFloat(_pBoardEffect->_h_local_left_top_x, 0.0f);
    }
    checkDxException(hr, D3D_OK, "SetFloat(_h_local_left_top_x) ‚ÉŽ¸”s‚µ‚Ü‚µ‚½B");
    if (_valign == VALIGN_BOTTOM) {
        hr = pID3DXEffect->SetFloat(_pBoardEffect->_h_local_left_top_y, (float)(-_pBoardModel->_model_height_px));
    } else if (_valign == VALIGN_MIDDLE) {
        hr = pID3DXEffect->SetFloat(_pBoardEffect->_h_local_left_top_y, (float)(-_pBoardModel->_model_height_px*0.5));
    } else { //VALIGN_TOP
        hr = pID3DXEffect->SetFloat(_pBoardEffect->_h_local_left_top_y, 0.0f);
    }
    checkDxException(hr, D3D_OK, "SetFloat(_h_local_left_top_y) ‚ÉŽ¸”s‚µ‚Ü‚µ‚½B");
    hr = pID3DXEffect->SetFloat(_pBoardEffect->_h_depth_z, float(C_PX(_z)));
    checkDxException(hr, D3D_OK, "SetFloat(_h_depth_z) ‚ÉŽ¸”s‚µ‚Ü‚µ‚½B");
//    hr = pID3DXEffect->SetFloat(_pBoardEffect->_h_alpha, _alpha);
//    checkDxException(hr, D3D_OK, "SetFloat(_h_alpha) ‚ÉŽ¸”s‚µ‚Ü‚µ‚½B");
    hr = pID3DXEffect->SetValue(_pBoardEffect->_h_colMaterialDiffuse, &(_paMaterial[0].Diffuse), sizeof(D3DCOLORVALUE) );
    checkDxException(hr, D3D_OK, "SetValue(_h_colMaterialDiffuse) ‚ÉŽ¸”s‚µ‚Ü‚µ‚½B");

    hr = pID3DXEffect->SetFloat(_pBoardEffect->_h_sx, SC_R(_sx));
    checkDxException(hr, D3D_OK, "SetFloat(_sx) ‚ÉŽ¸”s‚µ‚Ü‚µ‚½B");
    hr = pID3DXEffect->SetFloat(_pBoardEffect->_h_sy, SC_R(_sy));
    checkDxException(hr, D3D_OK, "SetFloat(_sy) ‚ÉŽ¸”s‚µ‚Ü‚µ‚½B");
    hr = pID3DXEffect->SetFloat(_pBoardEffect->_h_rz, ANG_RAD(_rz));
    checkDxException(hr, D3D_OK, "SetFloat(_h_rz) ‚ÉŽ¸”s‚µ‚Ü‚µ‚½B");

    _pBoardModel->BoardModel::draw(this);
}

//void BoardActor::setAlign(Align prm_align, Valign prm_valign) {
//    _align = prm_align;
//    _valign = prm_valign;
//}
//void BoardActor::setAlign(Align prm_align) {
//    _align = prm_align;
//}
//void BoardActor::setValign(Valign prm_valign) {
//    _valign = prm_valign;
//}

void BoardActor::setPositionAt(const GeometricActor* prm_pActor) {
    _x = prm_pActor->_x;
    _y = prm_pActor->_y;
}

void BoardActor::setPositionAt(const GeoElem* prm_pGeoElem) {
    _x = prm_pGeoElem->x;
    _y = prm_pGeoElem->y;
}

void BoardActor::setScale(scale s) {
    _sx = s;
    _sy = s;
}

void BoardActor::setScale(scale sx, scale sy) {
    _sx = sx;
    _sy = sy;
}

void BoardActor::setScale(scale sx, scale sy, scale sz) {
    _sx = sx;
    _sy = sy;
    _sz = sz; //_sz‚Í2D‚Å‚ÍŽg—p‚³‚ê‚È‚¢‚ªAScaler::behave() “à‚Ì”»’è‚Å–ð‚É—§‚ÂB
}

void BoardActor::setScaleR(float prm_rate) {
    _sx = R_SC(prm_rate);
    _sy = R_SC(prm_rate);
}

void BoardActor::setScaleR(float prm_x_rate, float prm_y_rate) {
    _sx = R_SC(prm_x_rate);
    _sy = R_SC(prm_y_rate);
}

void BoardActor::setScaleR(float prm_x_rate, float prm_y_rate, float prm_z_rate) {
    _sx = R_SC(prm_x_rate);
    _sy = R_SC(prm_y_rate);
    _sz = R_SC(prm_z_rate); //_sz‚Í2D‚Å‚ÍŽg—p‚³‚ê‚È‚¢‚ªAScaler::behave() “à‚Ì”»’è‚Å–ð‚É—§‚ÂB
}

//float BoardActor::getModelWidth() {
//    return _pBoardModel->_model_width_px;
//}
//
//float BoardActor::getModelHeight() {
//    return _pBoardModel->_model_height_px;
//}

void BoardActor::changeModel(int prm_model_index) {
    FigureActor::changeModel(prm_model_index);
    _pBoardModel = (BoardModel*)_pModel;
}

BoardActor::~BoardActor() {
    delete _pUvFlipper;
}
