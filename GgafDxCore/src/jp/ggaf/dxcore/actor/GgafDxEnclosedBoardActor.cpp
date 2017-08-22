#include "jp/ggaf/dxcore/actor/GgafDxEnclosedBoardActor.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxUvFlipper.h"
#include "jp/ggaf/dxcore/effect/GgafDxEnclosedBoardEffect.h"
#include "jp/ggaf/dxcore/exception/GgafDxCriticalException.h"
#include "jp/ggaf/dxcore/manager/GgafDxTextureConnection.h"
#include "jp/ggaf/dxcore/model/GgafDxEnclosedBoardModel.h"
#include "jp/ggaf/dxcore/scene/GgafDxSpacetime.h"
#include "jp/ggaf/dxcore/util/GgafDxGeoElem.h"

using namespace GgafCore;
using namespace GgafDxCore;

GgafDxEnclosedBoardActor::GgafDxEnclosedBoardActor(const char* prm_name,
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
_pEnclosedBoardModel((GgafDxEnclosedBoardModel*)_pModel),
_pEnclosedBoardEffect((GgafDxEnclosedBoardEffect*)_pEffect),
_pUvFlipper(NEW GgafDxUvFlipper(getModel()->getDefaultTextureConnection()->peek())) {

    _obj_class |= Obj_GgafDxEnclosedBoardActor;
    _class_name = "GgafDxEnclosedBoardActor";
    _pUvFlipper->setRotation(_pEnclosedBoardModel->_col_texture_split,
                             _pEnclosedBoardModel->_row_texture_split
                            );
    _pUvFlipper->setActivePtn(0);
    _pUvFlipper->exec(NOT_ANIMATED, 1);

    _unit_width_px = (int)(_pEnclosedBoardModel->_model_width_px); //•(px)
    _unit_height_px = (int)(_pEnclosedBoardModel->_model_height_px); //‚‚³(px)
//    _unit_harf_width_px = _unit_width_px/2;
//    _unit_harf_height_px = _unit_height_px/2;
    _width_px = _unit_width_px * 3;
    _height_px = _unit_height_px * 3;

    _lim_width_px  = _unit_width_px + _unit_width_px;
    _lim_height_px = _unit_height_px + _unit_height_px;

    _align = ALIGN_LEFT;
    _valign = VALIGN_TOP;
    _alpha = 1.0f;

    _is_2D = true;
    _pFunc_calc_rot_mv_world_matrix = nullptr;

    setZEnableDraw(false);
    setZWriteEnable(false);

    _z = 0;


}

void GgafDxEnclosedBoardActor::processDraw() {
    GgafDxEnclosedBoardEffect* pEnclosedBoardEffect = _pEnclosedBoardEffect;
    ID3DXEffect* pID3DXEffect = pEnclosedBoardEffect->_pID3DXEffect;
    HRESULT hr;
    GgafDxEnclosedBoardActor* pEnclosedBoardActor = nullptr;
    float u,v;

    //    „¡„Ÿ„¦„Ÿ„¦„Ÿ„¢
    //    „ ‚O„ ‚P„ ‚Q„ 
    //    „¥„Ÿ„©„Ÿ„©„Ÿ„§
    //    „ ‚R„ ‚S„ ‚T„ 
    //    „¥„Ÿ„©„Ÿ„©„Ÿ„§
    //    „ ‚U„ ‚V„ ‚W„ 
    //    „¤„Ÿ„¨„Ÿ„¨„Ÿ„£

//    D3DXHANDLE _h_top_edge_size_rate;
//    D3DXHANDLE _h_center_width_rate;
//    D3DXHANDLE _h_bottom_edge_size_rate;
//
//    D3DXHANDLE _h_left_edge_size_rate;
//    D3DXHANDLE _h_center_width_rate;
//    D3DXHANDLE _h_right_edge_size_rate;
    if (_width_px > _lim_width_px) {
        pixcoord center_width_px = _width_px - _lim_width_px;
        hr = pID3DXEffect->SetFloat(pEnclosedBoardEffect->_h_left_edge_size_rate, 1.0f);
        checkDxException(hr, D3D_OK, "SetFloat(_h_left_edge_size_rate) ‚ÉŽ¸”s‚µ‚Ü‚µ‚½B");
        hr = pID3DXEffect->SetFloat(pEnclosedBoardEffect->_h_center_height_rate, 1.0 * center_width_px / _unit_width_px);
        checkDxException(hr, D3D_OK, "SetFloat(_h_left_edge_size_rate) ‚ÉŽ¸”s‚µ‚Ü‚µ‚½B");
        hr = pID3DXEffect->SetFloat(pEnclosedBoardEffect->_h_right_edge_size_rate, 1.0f);
        checkDxException(hr, D3D_OK, "SetFloat(_h_right_edge_size_rate) ‚ÉŽ¸”s‚µ‚Ü‚µ‚½B");
        //‰¡•‚É—]—T‚ ‚èA1,4,7 ‚Ì‰¡•‚ðLk‚³‚¹‚éB
        if (_align == ALIGN_RIGHT) {
            hr = pID3DXEffect->SetFloat(pEnclosedBoardEffect->_ah_offset_x[0], -_width_px);
        } else if (_align == ALIGN_CENTER) {
            hr = pID3DXEffect->SetFloat(pEnclosedBoardEffect->_ah_offset_x[1], -(_width_px/2.0));
        } else { //ALIGN_LEFT ‚Í‚»‚Ì‚Ü‚Ü
            hr = pID3DXEffect->SetFloat(pEnclosedBoardEffect->_h_local_offset_x, 0.0f);
        }
        checkDxException(hr, D3D_OK, "SetFloat(_h_local_offset_x) ‚ÉŽ¸”s‚µ‚Ü‚µ‚½B");
    } else {
        //‰¡•‚É—]—T–³‚µA1,4,7 ‚Ì‰¡•‚Í0
        //0,3,6 ‚Æ 2,5,8 ‚Ì‰¡•‚ð –³—‚â‚è‚ä‚ª‚ß‚Ä•‚ð’²®
    }


    if (_height_px > _lim_height_px) {
        //c•‚É—]—T‚ ‚èA3,4,5 ‚Ìc•‚ðLk‚³‚¹‚éB
        pixcoord center_height_px = _height_px - _lim_height_px;
        hr = pID3DXEffect->SetFloat(pEnclosedBoardEffect->_h_top_edge_size_rate, 1.0f);
        checkDxException(hr, D3D_OK, "SetFloat(_h_top_edge_size_rate) ‚ÉŽ¸”s‚µ‚Ü‚µ‚½B");
        hr = pID3DXEffect->SetFloat(pEnclosedBoardEffect->_h_center_width_rate, 1.0f * center_height_px / _unit_height_px);
        checkDxException(hr, D3D_OK, "SetFloat(_h_left_edge_size_rate) ‚ÉŽ¸”s‚µ‚Ü‚µ‚½B");
        hr = pID3DXEffect->SetFloat(pEnclosedBoardEffect->_h_bottom_edge_size_rate, 1.0f);
        checkDxException(hr, D3D_OK, "SetFloat(_h_bottom_edge_size_rate) ‚ÉŽ¸”s‚µ‚Ü‚µ‚½B");
        if (_valign == VALIGN_BOTTOM) {
            hr = pID3DXEffect->SetFloat(pEnclosedBoardEffect->_h_local_offset_y, -_height_px);
        } else if (_valign == VALIGN_MIDDLE) {
            hr = pID3DXEffect->SetFloat(pEnclosedBoardEffect->_h_local_offset_y, -_height_px/2.0f);
        } else { //VALIGN_TOP ‚Í‚»‚Ì‚Ü‚Ü
            hr = pID3DXEffect->SetFloat(pEnclosedBoardEffect->_h_local_offset_y, 0.0f);
        }
        checkDxException(hr, D3D_OK, "SetFloat(_h_local_offset_y) ‚ÉŽ¸”s‚µ‚Ü‚µ‚½B");
    } else {
        //c•‚É—]—T–³‚µA3,4,5 ‚Ìc•‚Í0
        //0,1,2 ‚Æ 6,7,8 ‚Ìc•‚ð –³—‚â‚è‚ä‚ª‚ß‚Ä•‚ð’²®
    }
    hr = pID3DXEffect->SetFloat(pEnclosedBoardEffect->_h_x, C_PX(_x));
    checkDxException(hr, D3D_OK, "SetFloat(_h_x) ‚ÉŽ¸”s‚µ‚Ü‚µ‚½B");
    hr = pID3DXEffect->SetFloat(pEnclosedBoardEffect->_h_x, C_PX(_y));
    checkDxException(hr, D3D_OK, "SetFloat(_h_y) ‚ÉŽ¸”s‚µ‚Ü‚µ‚½B");
    hr = pID3DXEffect->SetFloat(pEnclosedBoardEffect->_h_z, C_PX(_z));
    checkDxException(hr, D3D_OK, "SetFloat(_h_z) ‚ÉŽ¸”s‚µ‚Ü‚µ‚½B");
    hr = pID3DXEffect->SetFloat(pEnclosedBoardEffect->_h_alpha, _alpha);
    checkDxException(hr, D3D_OK, "SetFloat(_h_alpha) ‚ÉŽ¸”s‚µ‚Ü‚µ‚½B");
    _pUvFlipper->getUV(u,v);
    hr = pID3DXEffect->SetFloat(pEnclosedBoardEffect->_ah_offset_u[0], u);
    checkDxException(hr, D3D_OK, "SetFloat(_h_offset_u) ‚ÉŽ¸”s‚µ‚Ü‚µ‚½B");
    hr = pID3DXEffect->SetFloat(pEnclosedBoardEffect->_ah_offset_v[0], v);
    checkDxException(hr, D3D_OK, "SetFloat(_h_offset_v) ‚ÉŽ¸”s‚µ‚Ü‚µ‚½B");


    GgafDxSpacetime::_pActor_draw_active = pEnclosedBoardActor; //•`‰æƒZƒbƒg‚ÌÅŒãƒAƒNƒ^[‚ðƒZƒbƒg
    _pEnclosedBoardModel->GgafDxEnclosedBoardModel::draw(this);
}

void GgafDxEnclosedBoardActor::setPositionAt(const GgafDxGeometricActor* prm_pActor) {
    _x = prm_pActor->_x;
    _y = prm_pActor->_y;
}

void GgafDxEnclosedBoardActor::setPositionAt(const GgafDxGeoElem* prm_pGeoElem) {
    _x = prm_pGeoElem->x;
    _y = prm_pGeoElem->y;
}

void GgafDxEnclosedBoardActor::setAlign(GgafDxAlign prm_align, GgafDxValign prm_valign) {
    _align = prm_align;
    _valign = prm_valign;
}

void GgafDxEnclosedBoardActor::setAlign(GgafDxAlign prm_align) {
    _align = prm_align;
}

void GgafDxEnclosedBoardActor::setValign(GgafDxValign prm_valign) {
    _valign = prm_valign;
}

float GgafDxEnclosedBoardActor::getModelWidth() {
    return _pEnclosedBoardModel->_model_width_px;
}

float GgafDxEnclosedBoardActor::getModelHeight() {
    return _pEnclosedBoardModel->_model_height_px;
}

GgafDxEnclosedBoardActor::~GgafDxEnclosedBoardActor() {
    delete _pUvFlipper;
}
