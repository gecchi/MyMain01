#include "jp/ggaf/dx/actor/FramedBoardActor.h"

#include "jp/ggaf/dx/actor/supporter/UvFlipper.h"
#include "jp/ggaf/dx/effect/FramedBoardEffect.h"
#include "jp/ggaf/dx/exception/CriticalException.h"
#include "jp/ggaf/dx/manager/TextureConnection.h"
#include "jp/ggaf/dx/model/FramedBoardModel.h"
#include "jp/ggaf/dx/scene/Spacetime.h"
#include "jp/ggaf/dx/util/GeoElem.h"


using namespace GgafDx;

FramedBoardActor::FramedBoardActor(const char* prm_name,
                                   const char* prm_model,
                                   const char* prm_effect_id,
                                   const char* prm_technique) :

                                       FigureActor(prm_name,
                                                   prm_model,
                                                   TYPE_FRAMEDBOARD_MODEL,
                                                   prm_effect_id,
                                                   TYPE_FRAMEDBOARD_EFFECT,
                                                   prm_technique,
                                                   nullptr) ,
                                       IAlignAbleActor(),
_pFramedBoardModel((FramedBoardModel*)_pModel),
_pFramedBoardEffect((FramedBoardEffect*)_pEffect),
_pUvFlipper(NEW UvFlipper(getModel()->_papTextureConnection[0]->peek())),
_pUvFlipper_frame(NEW UvFlipper(getModel()->_papTextureConnection[1]->peek())),
_model_frame_width_px((pixcoord)(_pFramedBoardModel->_model_frame_width_px)),
_model_frame_height_px((pixcoord)(_pFramedBoardModel->_model_frame_height_px)),
_model_center_width_px((pixcoord)(_pFramedBoardModel->_model_width_px)),
_model_center_height_px((pixcoord)(_pFramedBoardModel->_model_height_px)),
_model_total_width_px(_model_frame_width_px * 2 + _model_center_width_px),
_model_total_height_px(_model_frame_height_px * 2 + _model_center_height_px),
_lim_center_sx(R_SC( (_model_frame_width_px * 2.0) / _model_total_width_px )),
_lim_center_sy(R_SC( (_model_frame_height_px * 2.0) / _model_total_height_px )) {

    _obj_class |= Obj_GgafDx_FramedBoardActor | Obj_GgafDx_IAlignAbleActor;
    _class_name = "FramedBoardActor";
    _pUvFlipper->locatePatternNo(_pFramedBoardModel->_col_texture_split,
                            _pFramedBoardModel->_row_texture_split );
    _pUvFlipper->setActivePtn(0);
    _pUvFlipper->exec(NOT_ANIMATED, 1);

    _pUvFlipper_frame->locatePatternNo(_pFramedBoardModel->_col_frame_texture_split,
                                       _pFramedBoardModel->_row_frame_texture_split );
    _pUvFlipper_frame->setActivePtn(0);
    _pUvFlipper_frame->exec(NOT_ANIMATED, 1);

    _align = ALIGN_LEFT;
    _valign = VALIGN_TOP;
    _alpha = 1.0f;

    _is_fix_2D = true;
    _pFunc_calc_rot_mv_world_matrix = nullptr;
    setZEnableDraw(false);
    setZWriteEnable(false);
    setSpecialRenderDepthNear(0); //“Á•Ê‚ÈÅ‘O–ÊƒŒƒ“ƒ_ƒŠƒ“ƒOiˆê”ÔÅŒã‚É•`‰æj
}

void FramedBoardActor::processDraw() {
    if (_sx == 0 || _sy == 0) {
        return;
    }
    FramedBoardEffect* pFramedBoardEffect = _pFramedBoardEffect;
    ID3DXEffect* pID3DXEffect = pFramedBoardEffect->_pID3DXEffect;
    HRESULT hr;
    float u,v;

    //    „¡„Ÿ„¦„Ÿ„¦„Ÿ„¢
    //    „ ‚O„ ‚P„ ‚Q„ 
    //    „¥„Ÿ„©„Ÿ„©„Ÿ„§
    //    „ ‚R„ ‚S„ ‚T„ 
    //    „¥„Ÿ„©„Ÿ„©„Ÿ„§
    //    „ ‚U„ ‚V„ ‚W„ 
    //    „¤„Ÿ„¨„Ÿ„¨„Ÿ„£

    float frame_sx, center_sx;
    float total_width_px;
    int sgn_sx = SGN(_sx);
    if (ABS(_sx)  > _lim_center_sx) {
        //‰¡•‚É—]—T‚ ‚èA1,4,7 ‚Ì‰¡•‚ğLk‚³‚¹‚éB

        //  f = _model_frame_width_px
        //  c = _model_center_width_px
        //          1.0
        //    <------------>
        //     f    c    f
        //   „¡„Ÿ„¦„Ÿ„Ÿ„¦„Ÿ„¢
        //   „ ‚O„  ‚P „ ‚Q„ 
        //   „¥„Ÿ„©„Ÿ„Ÿ„©„Ÿ„§
        //   „ ‚R„  ‚S „ ‚T„ 
        //   „¥„Ÿ„©„Ÿ„Ÿ„©„Ÿ„§
        //   „ ‚U„  ‚V „ ‚W„ 
        //   „¤„Ÿ„¨„Ÿ„Ÿ„¨„Ÿ„£
        //
        //  1.0 ¨ r
        //
        //           r
        //    <------------->
        //     f     x     f
        //   „¡„Ÿ„¦„Ÿ„Ÿ„Ÿ„¦„Ÿ„¢
        //   „ ‚O„   ‚P  „ ‚Q„ 
        //   „¥„Ÿ„©„Ÿ„Ÿ„Ÿ„©„Ÿ„§
        //   „ ‚R„   ‚S  „ ‚T„ 
        //   „¥„Ÿ„©„Ÿ„Ÿ„Ÿ„©„Ÿ„§
        //   „ ‚U„   ‚V  „ ‚W„ 
        //   „¤„Ÿ„¨„Ÿ„Ÿ„Ÿ„¨„Ÿ„£
        //
        //  2f+c : 1.0 =  2f+x : r
        //
        //  2f+x = r(2f+c)
        //  x = r(2f+c)-2f
        frame_sx = 1.0f * sgn_sx;
        pixcoord fw = 2*_model_frame_width_px;
        center_sx = ( SC_R(_sx)*(fw + _model_center_width_px) - fw ) / _model_center_width_px;
        total_width_px = fw + _model_center_width_px * center_sx;

    } else {
        //‰¡•‚É—]—T–³‚µA1,4,7 ‚Ì‰¡•‚Í0
        //0,3,6 ‚Æ 2,5,8 ‚Ì‰¡•‚ğ –³—‚â‚è‚ä‚ª‚ß‚Ä•‚ğ’²®
        //  l = _lim_center_sx
        //  f = _model_frame_width_px
        //          l
        //    <---------->
        //     f       f
        //   „¡„Ÿ„Ÿ„¦„Ÿ„Ÿ„¢
        //   „  ‚O „  ‚Q „ 
        //   „¥„Ÿ„Ÿ„©„Ÿ„Ÿ„§
        //   „  ‚R „  ‚T „ 
        //   „¥„Ÿ„Ÿ„©„Ÿ„Ÿ„§
        //   „  ‚U „  ‚W „ 
        //   „¤„Ÿ„Ÿ„¨„Ÿ„Ÿ„£
        //
        //  l ¨ r
        //
        //       r
        //    <------>
        //     x   x
        //   „¡„Ÿ„¦„Ÿ„¢
        //   „ ‚O„ ‚Q„ 
        //   „¥„Ÿ„©„Ÿ„§
        //   „ ‚R„ ‚T„ 
        //   „¥„Ÿ„©„Ÿ„§
        //   „ ‚U„ ‚W„ 
        //   „¤„Ÿ„¨„Ÿ„£
        //
        //  2f : l =  2x : r
        //
        //  l2x = r2f
        //  x = 2rf / 2l = rf / l
        frame_sx = 1.0f * _sx / _lim_center_sx;
        center_sx = 0.0f;
        total_width_px =  (_model_frame_width_px * frame_sx) + (_model_frame_width_px * frame_sx);
    }
    hr = pID3DXEffect->SetFloat(pFramedBoardEffect->_h_frame_sx, frame_sx);
    checkDxException(hr, D3D_OK, "SetFloat(_h_left_edge_size_rate) ‚É¸”s‚µ‚Ü‚µ‚½B");
    hr = pID3DXEffect->SetFloat(pFramedBoardEffect->_h_center_sx, center_sx);
    checkDxException(hr, D3D_OK, "SetFloat(_h_left_edge_size_rate) ‚É¸”s‚µ‚Ü‚µ‚½B");

    if (_align == ALIGN_RIGHT) {
        //2f+x = r(2f+c)
        hr = pID3DXEffect->SetFloat(pFramedBoardEffect->_h_local_offset_x, -total_width_px);
    } else if (_align == ALIGN_CENTER) {
        hr = pID3DXEffect->SetFloat(pFramedBoardEffect->_h_local_offset_x, -(total_width_px*0.5));
    } else { //ALIGN_LEFT ‚Í‚»‚Ì‚Ü‚Ü
        hr = pID3DXEffect->SetFloat(pFramedBoardEffect->_h_local_offset_x, 0.0f);
    }
    checkDxException(hr, D3D_OK, "SetFloat(_h_local_offset_x) ‚É¸”s‚µ‚Ü‚µ‚½B");

    float frame_sy, center_sy;
    float total_height_px;
    int sgn_sy = SGN(_sy);
    if (ABS(_sy) > _lim_center_sy) {
        //c•‚É—]—T‚ ‚èA3,4,5 ‚Ìc•‚ğLk‚³‚¹‚éB
        frame_sy = 1.0f * sgn_sy;
        pixcoord fh = 2*_model_frame_height_px;
        center_sy =  ( SC_R(_sy)*(fh + _model_center_height_px) - fh ) / _model_center_height_px;
        total_height_px = fh + _model_center_height_px * center_sy;
    } else {
        //c•‚É—]—T–³‚µA3,4,5 ‚Ìc•‚Í0
        //0,1,2 ‚Æ 6,7,8 ‚Ìc•‚ğ –³—‚â‚è‚ä‚ª‚ß‚Ä•‚ğ’²®
        frame_sy = 1.0f * _sy / _lim_center_sy;
        center_sy = 0.0f;
        total_height_px = (_model_frame_height_px * frame_sy ) + (_model_frame_height_px * frame_sy );
    }

    hr = pID3DXEffect->SetFloat(pFramedBoardEffect->_h_frame_sy, frame_sy);
    checkDxException(hr, D3D_OK, "SetFloat(_h_top_edge_size_rate) ‚É¸”s‚µ‚Ü‚µ‚½B");
    hr = pID3DXEffect->SetFloat(pFramedBoardEffect->_h_center_sy, center_sy);
    checkDxException(hr, D3D_OK, "SetFloat(_h_left_edge_size_rate) ‚É¸”s‚µ‚Ü‚µ‚½B");

    if (_valign == VALIGN_BOTTOM) {
        hr = pID3DXEffect->SetFloat(pFramedBoardEffect->_h_local_offset_y, -total_height_px);
    } else if (_valign == VALIGN_MIDDLE) {
        hr = pID3DXEffect->SetFloat(pFramedBoardEffect->_h_local_offset_y, -total_height_px*0.5f);
    } else { //VALIGN_TOP ‚Í‚»‚Ì‚Ü‚Ü
        hr = pID3DXEffect->SetFloat(pFramedBoardEffect->_h_local_offset_y, 0.0f);
    }
    checkDxException(hr, D3D_OK, "SetFloat(_h_local_offset_y) ‚É¸”s‚µ‚Ü‚µ‚½B");

    hr = pID3DXEffect->SetFloat(pFramedBoardEffect->_h_x, C_PX(_x));
    checkDxException(hr, D3D_OK, "SetFloat(_h_x) ‚É¸”s‚µ‚Ü‚µ‚½B");
    hr = pID3DXEffect->SetFloat(pFramedBoardEffect->_h_y, C_PX(_y));
    checkDxException(hr, D3D_OK, "SetFloat(_h_y) ‚É¸”s‚µ‚Ü‚µ‚½B");
    hr = pID3DXEffect->SetFloat(pFramedBoardEffect->_h_z, C_PX(_z));
    checkDxException(hr, D3D_OK, "SetFloat(_h_z) ‚É¸”s‚µ‚Ü‚µ‚½B");
    hr = pID3DXEffect->SetFloat(pFramedBoardEffect->_h_alpha, _alpha);
    checkDxException(hr, D3D_OK, "SetFloat(_h_alpha) ‚É¸”s‚µ‚Ü‚µ‚½B");

    int active_frame_ptn_no = _pUvFlipper_frame->getActivePtn();
    for (int i = 0; i < 9; i++) {
        if (i == 4) {
            _pUvFlipper->getUV(u, v);
            hr = pID3DXEffect->SetFloat(pFramedBoardEffect->_ah_offset_u[4], u);
            checkDxException(hr, D3D_OK, "SetFloat(_h_offset_u) ‚É¸”s‚µ‚Ü‚µ‚½B");
            hr = pID3DXEffect->SetFloat(pFramedBoardEffect->_ah_offset_v[4], v);
            checkDxException(hr, D3D_OK, "SetFloat(_h_offset_v) ‚É¸”s‚µ‚Ü‚µ‚½B");
        } else {
            _pUvFlipper_frame->getUV(active_frame_ptn_no, u, v);
            hr = pID3DXEffect->SetFloat(pFramedBoardEffect->_ah_offset_u[i], u);
            checkDxException(hr, D3D_OK, "SetFloat(_h_offset_u) ‚É¸”s‚µ‚Ü‚µ‚½B");
            hr = pID3DXEffect->SetFloat(pFramedBoardEffect->_ah_offset_v[i], v);
            checkDxException(hr, D3D_OK, "SetFloat(_h_offset_v) ‚É¸”s‚µ‚Ü‚µ‚½B");
            active_frame_ptn_no++;
        }
    }

    _pFramedBoardModel->FramedBoardModel::draw(this);
}

void FramedBoardActor::setPositionAt(const GeometricActor* prm_pActor) {
    _x = prm_pActor->_x;
    _y = prm_pActor->_y;
}

void FramedBoardActor::setPositionAt(const GeoElem* prm_pGeoElem) {
    _x = prm_pGeoElem->x;
    _y = prm_pGeoElem->y;
}

//void FramedBoardActor::setAlign(Align prm_align, Valign prm_valign) {
//    _align = prm_align;
//    _valign = prm_valign;
//}
//
//void FramedBoardActor::setAlign(Align prm_align) {
//    _align = prm_align;
//}
//
//void FramedBoardActor::setValign(Valign prm_valign) {
//    _valign = prm_valign;
//}

void FramedBoardActor::setScale(scale s) {
    _sx = s;
    _sy = s;
}

void FramedBoardActor::setScale(scale sx, scale sy) {
    _sx = sx;
    _sy = sy;
}

void FramedBoardActor::setScale(scale sx, scale sy, scale sz) {
    _sx = sx;
    _sy = sy;
    _sz = sz; //_sz‚Í2D‚Å‚Íg—p‚³‚ê‚È‚¢‚ªAScaler::behave() “à‚Ì”»’è‚Å–ğ‚É—§‚ÂB
}

void FramedBoardActor::setScaleR(float prm_rate) {
    _sx = R_SC(prm_rate);
    _sy = R_SC(prm_rate);
}

void FramedBoardActor::setScaleR(float prm_x_rate, float prm_y_rate) {
    _sx = R_SC(prm_x_rate);
    _sy = R_SC(prm_y_rate);
}

void FramedBoardActor::setScaleR(float prm_x_rate, float prm_y_rate, float prm_z_rate) {
    _sx = R_SC(prm_x_rate);
    _sy = R_SC(prm_y_rate);
    _sz = R_SC(prm_z_rate); //_sz‚Í2D‚Å‚Íg—p‚³‚ê‚È‚¢‚ªAScaler::behave() “à‚Ì”»’è‚Å–ğ‚É—§‚ÂB
}
void FramedBoardActor::setWidth(coord prm_width) {
    _sx = R_SC(1.0 * C_PX(prm_width) / _model_total_width_px);
}

void FramedBoardActor::setHeight(coord prm_height) {
    _sy = R_SC(1.0 * C_PX(prm_height) / _model_total_height_px);
}

void FramedBoardActor::addWidth(coord prm_width) {
    _sx += (R_SC(1.0 * C_PX(prm_width) / _model_total_width_px));
}

void FramedBoardActor::addHeight(coord prm_height) {
    _sy += (R_SC(1.0 * C_PX(prm_height) / _model_total_height_px));
}

coord FramedBoardActor::getWidth() {
    return PX_C(_model_total_width_px * SC_R(_sx));
}
coord FramedBoardActor::getHeight() {
    return PX_C(_model_total_height_px * SC_R(_sy));
}

void FramedBoardActor::changeModel(int prm_model_index) {
    FigureActor::changeModel(prm_model_index);
    _pFramedBoardModel = (FramedBoardModel*)_pModel;
}

FramedBoardActor::~FramedBoardActor() {
    delete _pUvFlipper;
    delete _pUvFlipper_frame;
}
