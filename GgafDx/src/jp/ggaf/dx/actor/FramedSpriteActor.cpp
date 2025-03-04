#include "jp/ggaf/dx/actor/FramedSpriteActor.h"

#include "jp/ggaf/dx/exception/CriticalException.h"
#include "jp/ggaf/dx/Caretaker.h"
#include "jp/ggaf/dx/util/Util.h"
#include "jp/ggaf/dx/effect/FramedSpriteEffect.h"
#include "jp/ggaf/dx/model/FramedSpriteModel.h"
#include "jp/ggaf/dx/manager/TextureConnection.h"
#include "jp/ggaf/dx/actor/supporter/UvFlipper.h"

using namespace GgafDx;

FramedSpriteActor::FramedSpriteActor(const char* prm_name,
                         const char* prm_model,
                         const char* prm_effect_id,
                         const char* prm_technique) :

                             FigureActor(prm_name,
                                         prm_model,
                                         TYPE_FRAMEDSPRITE_MODEL,
                                         prm_effect_id,
                                         TYPE_FRAMEDSPRITE_EFFECT,
                                         prm_technique),
                            IAlignAbleActor(),
_pFramedSpriteModel( (FramedSpriteModel*)_pModel),
_pFramedSpriteEffect( (FramedSpriteEffect*)_pEffect),
_pUvFlipper(NEW UvFlipper()),
_pUvFlipper_frame(NEW UvFlipper()),
_model_frame_width_px((pixcoord)(_pFramedSpriteModel->_model_frame_width_px)),
_model_frame_height_px((pixcoord)(_pFramedSpriteModel->_model_frame_height_px)),
_model_center_width_px((pixcoord)(_pFramedSpriteModel->_model_width_px)),
_model_center_height_px((pixcoord)(_pFramedSpriteModel->_model_height_px)),
_model_total_width_px(_model_frame_width_px * 2 + _model_center_width_px),
_model_total_height_px(_model_frame_height_px * 2 + _model_center_height_px),
_lim_center_sx(R_SC( (_model_frame_width_px * 2.0) / _model_total_width_px )),
_lim_center_sy(R_SC( (_model_frame_height_px * 2.0) / _model_total_height_px )) {

    _obj_class |= Obj_GgafDx_FramedSpriteActor | Obj_GgafDx_IAlignAbleActor;
    _class_name = "FramedSpriteActor";
    _pUvFlipper->locatePatternNo(_pFramedSpriteModel->_col_texture_split,
                                 _pFramedSpriteModel->_row_texture_split );
    _pUvFlipper_frame->locatePatternNo(_pFramedSpriteModel->_col_frame_texture_split,
                                       _pFramedSpriteModel->_row_frame_texture_split );
    defineRotMvWorldMatrix(UTIL::setWorldMatrix_RxRzRyMv); //デフォルトの回転×移動の変換行列

    _align = ALIGN_CENTER;
    _valign = VALIGN_MIDDLE;
}

void FramedSpriteActor::processDraw() {
    if (_sx == 0 || _sy == 0) {
        return;
    }
    ID3DXEffect* const pID3DXEffect = _pFramedSpriteEffect->_pID3DXEffect;
    FramedSpriteEffect* pFramedSpriteEffect = _pFramedSpriteEffect;
    HRESULT hr;
    float u,v;

    //    ┌─┬─┬─┐
    //    │０│１│２│
    //    ├─┼─┼─┤
    //    │３│４│５│
    //    ├─┼─┼─┤
    //    │６│７│８│
    //    └─┴─┴─┘

    float frame_sx, center_sx;
    float total_width_px;
    int sgn_sx = SGN(_sx);
    if (ABS(_sx)  > _lim_center_sx) {
        //横幅に余裕あり、1,4,7 の横幅を伸縮させる。

        //  f = _model_frame_width_px
        //  c = _model_center_width_px
        //          1.0
        //    <------------>
        //     f    c    f
        //   ┌─┬──┬─┐
        //   │０│ １ │２│
        //   ├─┼──┼─┤
        //   │３│ ４ │５│
        //   ├─┼──┼─┤
        //   │６│ ７ │８│
        //   └─┴──┴─┘
        //
        //  1.0 → r
        //
        //           r
        //    <------------->
        //     f     x     f
        //   ┌─┬───┬─┐
        //   │０│  １  │２│
        //   ├─┼───┼─┤
        //   │３│  ４  │５│
        //   ├─┼───┼─┤
        //   │６│  ７  │８│
        //   └─┴───┴─┘
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
        //横幅に余裕無し、1,4,7 の横幅は0
        //0,3,6 と 2,5,8 の横幅を 無理やりゆがめて幅を調整
        //  l = _lim_center_sx
        //  f = _model_frame_width_px
        //          l
        //    <---------->
        //     f       f
        //   ┌──┬──┐
        //   │ ０ │ ２ │
        //   ├──┼──┤
        //   │ ３ │ ５ │
        //   ├──┼──┤
        //   │ ６ │ ８ │
        //   └──┴──┘
        //
        //  l → r
        //
        //       r
        //    <------>
        //     x   x
        //   ┌─┬─┐
        //   │０│２│
        //   ├─┼─┤
        //   │３│５│
        //   ├─┼─┤
        //   │６│８│
        //   └─┴─┘
        //
        //  2f : l =  2x : r
        //
        //  l2x = r2f
        //  x = 2rf / 2l = rf / l
        frame_sx = 1.0f * _sx / _lim_center_sx;
        center_sx = 0.0f;
        total_width_px =  (_model_frame_width_px * frame_sx) + (_model_frame_width_px * frame_sx);
    }
    hr = pID3DXEffect->SetFloat(pFramedSpriteEffect->_h_frame_sx, frame_sx);
    checkDxException(hr, D3D_OK, "SetFloat(_h_frame_sx) に失敗しました。");
    hr = pID3DXEffect->SetFloat(pFramedSpriteEffect->_h_center_sx, center_sx);
    checkDxException(hr, D3D_OK, "SetFloat(_h_center_sx) に失敗しました。");


    //            if (_align == ALIGN_CENTER) {
    //                //do nothing
    //            } else if (_align == ALIGN_LEFT) {
    //                pSpriteSetActor->_matWorld._41 += PX_DX(_pSpriteSetModel->_model_width_px/2);
    //            } else {
    //                //ALIGN_RIGHT
    //                pSpriteSetActor->_matWorld._41 -= PX_DX(_pSpriteSetModel->_model_width_px/2);
    //            }


    if (_align == ALIGN_CENTER) {
        hr = pID3DXEffect->SetFloat(pFramedSpriteEffect->_h_local_offset_x, 0.0f);
    } else if (_align == ALIGN_LEFT) {
        hr = pID3DXEffect->SetFloat(pFramedSpriteEffect->_h_local_offset_x, PX_DX(total_width_px*0.5) );
    } else { //ALIGN_RIGHT
        hr = pID3DXEffect->SetFloat(pFramedSpriteEffect->_h_local_offset_x, -PX_DX(total_width_px*0.5));
    }
//    if (_align == ALIGN_RIGHT) {
//        //2f+x = r(2f+c)
//        hr = pID3DXEffect->SetFloat(pFramedSpriteEffect->_h_local_offset_x, -total_width_px);
//    } else if (_align == ALIGN_CENTER) {
//        hr = pID3DXEffect->SetFloat(pFramedSpriteEffect->_h_local_offset_x, -(total_width_px*0.5));
//    } else { //ALIGN_LEFT はそのまま
//        hr = pID3DXEffect->SetFloat(pFramedSpriteEffect->_h_local_offset_x, 0.0f);
//    }
    checkDxException(hr, D3D_OK, "SetFloat(_h_local_offset_x) に失敗しました。");

    float frame_sy, center_sy;
    float total_height_px;
    int sgn_sy = SGN(_sy);
    if (ABS(_sy) > _lim_center_sy) {
        //縦幅に余裕あり、3,4,5 の縦幅を伸縮させる。
        frame_sy = 1.0f * sgn_sy;
        pixcoord fh = 2*_model_frame_height_px;
        center_sy =  ( SC_R(_sy)*(fh + _model_center_height_px) - fh ) / _model_center_height_px;
        total_height_px = fh + _model_center_height_px * center_sy;
    } else {
        //縦幅に余裕無し、3,4,5 の縦幅は0
        //0,1,2 と 6,7,8 の縦幅を 無理やりゆがめて幅を調整
        frame_sy = 1.0f * _sy / _lim_center_sy;
        center_sy = 0.0f;
        total_height_px = (_model_frame_height_px * frame_sy ) + (_model_frame_height_px * frame_sy );
    }

    hr = pID3DXEffect->SetFloat(pFramedSpriteEffect->_h_frame_sy, frame_sy);
    checkDxException(hr, D3D_OK, "SetFloat(_h_top_edge_size_rate) に失敗しました。");
    hr = pID3DXEffect->SetFloat(pFramedSpriteEffect->_h_center_sy, center_sy);
    checkDxException(hr, D3D_OK, "SetFloat(_h_left_edge_size_rate) に失敗しました。");
    //            if (_valign == VALIGN_MIDDLE) {
    //                //do nothing
    //            } else if (_valign == VALIGN_TOP) {
    //                pSpriteSetActor->_matWorld._42 -= PX_DX(_pSpriteSetModel->_model_height_px/2);
    //            } else {
    //                //VALIGN_BOTTOM
    //                pSpriteSetActor->_matWorld._42 += PX_DX(_pSpriteSetModel->_model_height_px/2);
    //            }
    if (_valign == VALIGN_MIDDLE) {
        hr = pID3DXEffect->SetFloat(pFramedSpriteEffect->_h_local_offset_y, 0.0f);
    } else if (_valign == VALIGN_TOP) {
        hr = pID3DXEffect->SetFloat(pFramedSpriteEffect->_h_local_offset_y, -PX_DX(total_height_px*0.5));
    } else { //VALIGN_BOTTOM
        hr = pID3DXEffect->SetFloat(pFramedSpriteEffect->_h_local_offset_y, PX_DX(total_height_px*0.5));
    }

//    if (_valign == VALIGN_BOTTOM) {
//        hr = pID3DXEffect->SetFloat(pFramedSpriteEffect->_h_local_offset_y, -total_height_px);
//    } else if (_valign == VALIGN_MIDDLE) {
//        hr = pID3DXEffect->SetFloat(pFramedSpriteEffect->_h_local_offset_y, -total_height_px*0.5f);
//    } else { //VALIGN_TOP はそのまま
//        hr = pID3DXEffect->SetFloat(pFramedSpriteEffect->_h_local_offset_y, 0.0f);
//    }

    checkDxException(hr, D3D_OK, "SetFloat(_h_local_offset_y) に失敗しました。");

    hr = pID3DXEffect->SetFloat(pFramedSpriteEffect->_h_alpha, getAlpha());
    checkDxException(hr, D3D_OK, "SetFloat(_h_alpha) に失敗しました。");

    int active_frame_ptn_no = _pUvFlipper_frame->getActivePtn();
    for (int i = 0; i < 9; i++) {
        if (i == 4) {
            _pUvFlipper->getUV(u, v);
            hr = pID3DXEffect->SetFloat(pFramedSpriteEffect->_ah_offset_u[4], u);
            checkDxException(hr, D3D_OK, "SetFloat(_h_offset_u) に失敗しました。");
            hr = pID3DXEffect->SetFloat(pFramedSpriteEffect->_ah_offset_v[4], v);
            checkDxException(hr, D3D_OK, "SetFloat(_h_offset_v) に失敗しました。");
        } else {
            _pUvFlipper_frame->getUV(active_frame_ptn_no, u, v);
            hr = pID3DXEffect->SetFloat(pFramedSpriteEffect->_ah_offset_u[i], u);
            checkDxException(hr, D3D_OK, "SetFloat(_h_offset_u) に失敗しました。");
            hr = pID3DXEffect->SetFloat(pFramedSpriteEffect->_ah_offset_v[i], v);
            checkDxException(hr, D3D_OK, "SetFloat(_h_offset_v) に失敗しました。");
            active_frame_ptn_no++;
        }
    }
    hr = pID3DXEffect->SetMatrix(_pFramedSpriteEffect->_h_matWorldRotMv, &_matWorldRotMv );
    checkDxException(hr, D3D_OK, "SetMatrix(_h_matWorld) に失敗しました。");
    hr = pID3DXEffect->SetValue(_pFramedSpriteEffect->_h_colMaterialDiffuse, &(_paMaterial[0].Diffuse), sizeof(D3DCOLORVALUE) );
    checkDxException(hr, D3D_OK, "SetValue(_h_colMaterialDiffuse) に失敗しました。");
    _pFramedSpriteModel->FramedSpriteModel::draw(this);
}
//void FramedSpriteActor::setAlign(Align prm_align, Valign prm_valign) {
//    _align = prm_align;
//    _valign = prm_valign;
//}
//
//void FramedSpriteActor::setAlign(Align prm_align) {
//    _align = prm_align;
//}
//
//void FramedSpriteActor::setValign(Valign prm_valign) {
//    _valign = prm_valign;
//}

void FramedSpriteActor::setWidth(coord prm_width) {
    _sx = R_SC(1.0 * C_PX(prm_width) / _model_total_width_px);
}

void FramedSpriteActor::setHeight(coord prm_height) {
    _sy = R_SC(1.0 * C_PX(prm_height) / _model_total_height_px);
}

void FramedSpriteActor::addWidth(coord prm_width) {
    _sx += (R_SC(1.0 * C_PX(prm_width) / _model_total_width_px));
}

void FramedSpriteActor::addHeight(coord prm_height) {
    _sy += (R_SC(1.0 * C_PX(prm_height) / _model_total_height_px));
}

coord FramedSpriteActor::getWidth() {
    return PX_C(_model_total_width_px * SC_R(_sx));
}
coord FramedSpriteActor::getHeight() {
    return PX_C(_model_total_height_px * SC_R(_sy));
}

void FramedSpriteActor::changeModelByIndex(int prm_model_index) {
    FigureActor::changeModelByIndex(prm_model_index);
    _pFramedSpriteModel = (FramedSpriteModel*)_pModel;
}

FramedSpriteActor::~FramedSpriteActor() {
    delete _pUvFlipper;
    delete _pUvFlipper_frame;
}
