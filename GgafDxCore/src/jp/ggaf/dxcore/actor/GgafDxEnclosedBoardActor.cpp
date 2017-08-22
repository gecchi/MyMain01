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

    _unit_width_px = (int)(_pEnclosedBoardModel->_model_width_px); //幅(px)
    _unit_height_px = (int)(_pEnclosedBoardModel->_model_height_px); //高さ(px)
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

    //    ┌─┬─┬─┐
    //    │０│１│２│
    //    ├─┼─┼─┤
    //    │３│４│５│
    //    ├─┼─┼─┤
    //    │６│７│８│
    //    └─┴─┴─┘

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
        checkDxException(hr, D3D_OK, "SetFloat(_h_left_edge_size_rate) に失敗しました。");
        hr = pID3DXEffect->SetFloat(pEnclosedBoardEffect->_h_center_height_rate, 1.0 * center_width_px / _unit_width_px);
        checkDxException(hr, D3D_OK, "SetFloat(_h_left_edge_size_rate) に失敗しました。");
        hr = pID3DXEffect->SetFloat(pEnclosedBoardEffect->_h_right_edge_size_rate, 1.0f);
        checkDxException(hr, D3D_OK, "SetFloat(_h_right_edge_size_rate) に失敗しました。");
        //横幅に余裕あり、1,4,7 の横幅を伸縮させる。
        if (_align == ALIGN_RIGHT) {
            hr = pID3DXEffect->SetFloat(pEnclosedBoardEffect->_ah_offset_x[0], -_width_px);
        } else if (_align == ALIGN_CENTER) {
            hr = pID3DXEffect->SetFloat(pEnclosedBoardEffect->_ah_offset_x[1], -(_width_px/2.0));
        } else { //ALIGN_LEFT はそのまま
            hr = pID3DXEffect->SetFloat(pEnclosedBoardEffect->_h_local_offset_x, 0.0f);
        }
        checkDxException(hr, D3D_OK, "SetFloat(_h_local_offset_x) に失敗しました。");
    } else {
        //横幅に余裕無し、1,4,7 の横幅は0
        //0,3,6 と 2,5,8 の横幅を 無理やりゆがめて幅を調整
    }


    if (_height_px > _lim_height_px) {
        //縦幅に余裕あり、3,4,5 の縦幅を伸縮させる。
        pixcoord center_height_px = _height_px - _lim_height_px;
        hr = pID3DXEffect->SetFloat(pEnclosedBoardEffect->_h_top_edge_size_rate, 1.0f);
        checkDxException(hr, D3D_OK, "SetFloat(_h_top_edge_size_rate) に失敗しました。");
        hr = pID3DXEffect->SetFloat(pEnclosedBoardEffect->_h_center_width_rate, 1.0f * center_height_px / _unit_height_px);
        checkDxException(hr, D3D_OK, "SetFloat(_h_left_edge_size_rate) に失敗しました。");
        hr = pID3DXEffect->SetFloat(pEnclosedBoardEffect->_h_bottom_edge_size_rate, 1.0f);
        checkDxException(hr, D3D_OK, "SetFloat(_h_bottom_edge_size_rate) に失敗しました。");
        if (_valign == VALIGN_BOTTOM) {
            hr = pID3DXEffect->SetFloat(pEnclosedBoardEffect->_h_local_offset_y, -_height_px);
        } else if (_valign == VALIGN_MIDDLE) {
            hr = pID3DXEffect->SetFloat(pEnclosedBoardEffect->_h_local_offset_y, -_height_px/2.0f);
        } else { //VALIGN_TOP はそのまま
            hr = pID3DXEffect->SetFloat(pEnclosedBoardEffect->_h_local_offset_y, 0.0f);
        }
        checkDxException(hr, D3D_OK, "SetFloat(_h_local_offset_y) に失敗しました。");
    } else {
        //縦幅に余裕無し、3,4,5 の縦幅は0
        //0,1,2 と 6,7,8 の縦幅を 無理やりゆがめて幅を調整
    }
    hr = pID3DXEffect->SetFloat(pEnclosedBoardEffect->_h_x, C_PX(_x));
    checkDxException(hr, D3D_OK, "SetFloat(_h_x) に失敗しました。");
    hr = pID3DXEffect->SetFloat(pEnclosedBoardEffect->_h_x, C_PX(_y));
    checkDxException(hr, D3D_OK, "SetFloat(_h_y) に失敗しました。");
    hr = pID3DXEffect->SetFloat(pEnclosedBoardEffect->_h_z, C_PX(_z));
    checkDxException(hr, D3D_OK, "SetFloat(_h_z) に失敗しました。");
    hr = pID3DXEffect->SetFloat(pEnclosedBoardEffect->_h_alpha, _alpha);
    checkDxException(hr, D3D_OK, "SetFloat(_h_alpha) に失敗しました。");
    _pUvFlipper->getUV(u,v);
    hr = pID3DXEffect->SetFloat(pEnclosedBoardEffect->_ah_offset_u[0], u);
    checkDxException(hr, D3D_OK, "SetFloat(_h_offset_u) に失敗しました。");
    hr = pID3DXEffect->SetFloat(pEnclosedBoardEffect->_ah_offset_v[0], v);
    checkDxException(hr, D3D_OK, "SetFloat(_h_offset_v) に失敗しました。");


    GgafDxSpacetime::_pActor_draw_active = pEnclosedBoardActor; //描画セットの最後アクターをセット
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
