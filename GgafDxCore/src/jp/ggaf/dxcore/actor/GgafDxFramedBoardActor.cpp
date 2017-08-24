#include "jp/ggaf/dxcore/actor/GgafDxFramedBoardActor.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxUvFlipper.h"
#include "jp/ggaf/dxcore/effect/GgafDxFramedBoardEffect.h"
#include "jp/ggaf/dxcore/exception/GgafDxCriticalException.h"
#include "jp/ggaf/dxcore/manager/GgafDxTextureConnection.h"
#include "jp/ggaf/dxcore/model/GgafDxFramedBoardModel.h"
#include "jp/ggaf/dxcore/scene/GgafDxSpacetime.h"
#include "jp/ggaf/dxcore/util/GgafDxGeoElem.h"

using namespace GgafCore;
using namespace GgafDxCore;

GgafDxFramedBoardActor::GgafDxFramedBoardActor(const char* prm_name,
                                         const char* prm_model_id,
                                         const char* prm_effect_id,
                                         const char* prm_technique) :

                                             GgafDxFigureActor(prm_name,
                                                               prm_model_id,
                                                               "E",
                                                               prm_effect_id,
                                                               "E",
                                                               prm_technique,
                                                               nullptr,
                                                               nullptr) ,
_pFramedBoardModel((GgafDxFramedBoardModel*)_pModel),
_pFramedBoardEffect((GgafDxFramedBoardEffect*)_pEffect),
_pUvFlipper(NEW GgafDxUvFlipper(getModel()->_papTextureConnection[0]->peek())),
_pUvFlipper_frame(NEW GgafDxUvFlipper(getModel()->_papTextureConnection[1]->peek())),
_model_frame_width_px((pixcoord)(_pFramedBoardModel->_model_frame_width_px)),
_model_frame_height_px((pixcoord)(_pFramedBoardModel->_model_frame_height_px)),
_model_center_width_px((pixcoord)(_pFramedBoardModel->_model_width_px)),
_model_center_height_px((pixcoord)(_pFramedBoardModel->_model_height_px)),
_model_total_width_px(_model_frame_width_px * 2 + _model_center_width_px),
_model_total_height_px(_model_frame_height_px * 2 + _model_center_height_px),
_lim_center_sx(R_SC( (_model_frame_width_px * 2.0) / _model_total_width_px )),
_lim_center_sy(R_SC( (_model_frame_height_px * 2.0) / _model_total_height_px )) {

    _obj_class |= Obj_GgafDxFramedBoardActor;
    _class_name = "GgafDxFramedBoardActor";
    _pUvFlipper->setRotation(_pFramedBoardModel->_col_texture_split,
                            _pFramedBoardModel->_row_texture_split );
    _pUvFlipper->setActivePtn(0);
    _pUvFlipper->exec(NOT_ANIMATED, 1);

    _pUvFlipper_frame->setRotation(_pFramedBoardModel->_col_frame_texture_split,
                                   _pFramedBoardModel->_row_frame_texture_split );
    _pUvFlipper_frame->setActivePtn(0);
    _pUvFlipper_frame->exec(NOT_ANIMATED, 1);

    _align = ALIGN_LEFT;
    _valign = VALIGN_TOP;
    _alpha = 1.0f;

    _is_2D = true;
    _pFunc_calc_rot_mv_world_matrix = nullptr;

    setZEnableDraw(false);
    setZWriteEnable(false);

    _z = 0;
}

void GgafDxFramedBoardActor::processDraw() {
    GgafDxFramedBoardEffect* pFramedBoardEffect = _pFramedBoardEffect;
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

    float frame_width_rate, center_width_rate;
    float total_width_px;
    if (_sx  > _lim_center_sx) {
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
        frame_width_rate = 1.0f;
        pixcoord fw = 2*_model_frame_width_px;
        center_width_rate = ( SC_R(_sx)*(fw + _model_center_width_px) - fw ) / _model_center_width_px;
        total_width_px = fw + _model_center_width_px * center_width_rate;

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
        frame_width_rate = 1.0f * _sx  / _lim_center_sx;
        center_width_rate = 0.0f;
        total_width_px =  (_model_frame_width_px * frame_width_rate) + (_model_frame_width_px * frame_width_rate);
    }
    hr = pID3DXEffect->SetFloat(pFramedBoardEffect->_h_frame_width_rate, frame_width_rate);
    checkDxException(hr, D3D_OK, "SetFloat(_h_left_edge_size_rate) ‚É¸”s‚µ‚Ü‚µ‚½B");
    hr = pID3DXEffect->SetFloat(pFramedBoardEffect->_h_center_width_rate, center_width_rate);
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

    float frame_height_rate, center_height_rate;
    float total_height_px;
    if (_sy > _lim_center_sy) {
        //c•‚É—]—T‚ ‚èA3,4,5 ‚Ìc•‚ğLk‚³‚¹‚éB
        frame_height_rate = 1.0f;
        pixcoord fh = 2*_model_frame_height_px;
        center_height_rate =  ( SC_R(_sy)*(fh + _model_center_height_px) - fh ) / _model_center_height_px;
        total_height_px = fh + _model_center_height_px * center_height_rate;
    } else {
        //c•‚É—]—T–³‚µA3,4,5 ‚Ìc•‚Í0
        //0,1,2 ‚Æ 6,7,8 ‚Ìc•‚ğ –³—‚â‚è‚ä‚ª‚ß‚Ä•‚ğ’²®
        frame_height_rate = 1.0f * _sy / _lim_center_sy;
        center_height_rate = 0.0f;
        total_height_px = (_model_frame_height_px * frame_height_rate ) + (_model_frame_height_px * frame_height_rate );
    }

    hr = pID3DXEffect->SetFloat(pFramedBoardEffect->_h_frame_height_rate, frame_height_rate);
    checkDxException(hr, D3D_OK, "SetFloat(_h_top_edge_size_rate) ‚É¸”s‚µ‚Ü‚µ‚½B");
    hr = pID3DXEffect->SetFloat(pFramedBoardEffect->_h_center_height_rate, center_height_rate);
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

    int active_ptn_no = _pUvFlipper_frame->getActivePtn();
    for (int i = 0; i < 9; i++) {
        if (i == 4) {
            _pUvFlipper->getUV(u, v);
            hr = pID3DXEffect->SetFloat(pFramedBoardEffect->_ah_offset_u[4], u);
            checkDxException(hr, D3D_OK, "SetFloat(_h_offset_u) ‚É¸”s‚µ‚Ü‚µ‚½B");
            hr = pID3DXEffect->SetFloat(pFramedBoardEffect->_ah_offset_v[4], v);
            checkDxException(hr, D3D_OK, "SetFloat(_h_offset_v) ‚É¸”s‚µ‚Ü‚µ‚½B");
        } else {
            _pUvFlipper_frame->getUV(active_ptn_no, u, v);
            hr = pID3DXEffect->SetFloat(pFramedBoardEffect->_ah_offset_u[i], u);
            checkDxException(hr, D3D_OK, "SetFloat(_h_offset_u) ‚É¸”s‚µ‚Ü‚µ‚½B");
            hr = pID3DXEffect->SetFloat(pFramedBoardEffect->_ah_offset_v[i], v);
            checkDxException(hr, D3D_OK, "SetFloat(_h_offset_v) ‚É¸”s‚µ‚Ü‚µ‚½B");
            active_ptn_no++;
        }
    }

    _pFramedBoardModel->GgafDxFramedBoardModel::draw(this);
}

void GgafDxFramedBoardActor::setPositionAt(const GgafDxGeometricActor* prm_pActor) {
    _x = prm_pActor->_x;
    _y = prm_pActor->_y;
}

void GgafDxFramedBoardActor::setPositionAt(const GgafDxGeoElem* prm_pGeoElem) {
    _x = prm_pGeoElem->x;
    _y = prm_pGeoElem->y;
}

void GgafDxFramedBoardActor::setAlign(GgafDxAlign prm_align, GgafDxValign prm_valign) {
    _align = prm_align;
    _valign = prm_valign;
}

void GgafDxFramedBoardActor::setAlign(GgafDxAlign prm_align) {
    _align = prm_align;
}

void GgafDxFramedBoardActor::setValign(GgafDxValign prm_valign) {
    _valign = prm_valign;
}

void GgafDxFramedBoardActor::setScale(scale s) {
    _sx = s;
    _sy = s;
}

void GgafDxFramedBoardActor::setScale(scale sx, scale sy) {
    _sx = sx;
    _sy = sy;
}

void GgafDxFramedBoardActor::setScale(scale sx, scale sy, scale sz) {
    _sx = sx;
    _sy = sy;
    _sz = sz; //_sz‚Í2D‚Å‚Íg—p‚³‚ê‚È‚¢‚ªAGgafDxScaler::behave() “à‚Ì”»’è‚Å–ğ‚É—§‚ÂB
}

void GgafDxFramedBoardActor::setScaleR(float prm_rate) {
    _sx = R_SC(prm_rate);
    _sy = R_SC(prm_rate);
}

void GgafDxFramedBoardActor::setScaleR(float prm_x_rate, float prm_y_rate) {
    _sx = R_SC(prm_x_rate);
    _sy = R_SC(prm_y_rate);
}

void GgafDxFramedBoardActor::setScaleR(float prm_x_rate, float prm_y_rate, float prm_z_rate) {
    _sx = R_SC(prm_x_rate);
    _sy = R_SC(prm_y_rate);
    _sz = R_SC(prm_z_rate); //_sz‚Í2D‚Å‚Íg—p‚³‚ê‚È‚¢‚ªAGgafDxScaler::behave() “à‚Ì”»’è‚Å–ğ‚É—§‚ÂB
}
void GgafDxFramedBoardActor::setWidth(coord prm_width) {
    _sx = R_SC(1.0 * C_PX(prm_width) / _model_total_width_px);
}

void GgafDxFramedBoardActor::setHeight(coord prm_height) {
    _sy = R_SC(1.0 * C_PX(prm_height) / _model_total_height_px);
}

void GgafDxFramedBoardActor::addWidth(coord prm_width) {
    _sx += (R_SC(1.0 * C_PX(prm_width) / _model_total_width_px));
}

void GgafDxFramedBoardActor::addHeight(coord prm_height) {
    _sy += (R_SC(1.0 * C_PX(prm_height) / _model_total_height_px));
}

GgafDxFramedBoardActor::~GgafDxFramedBoardActor() {
    delete _pUvFlipper;
    delete _pUvFlipper_frame;
}
