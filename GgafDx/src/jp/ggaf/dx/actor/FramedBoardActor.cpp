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
                                         const char* prm_model_id,
                                         const char* prm_effect_id,
                                         const char* prm_technique) :

                                             FigureActor(prm_name,
                                                               prm_model_id,
                                                               TYPE_FRAMEDBOARD_MODEL,
                                                               prm_effect_id,
                                                               TYPE_FRAMEDBOARD_EFFECT,
                                                               prm_technique,
                                                               nullptr) ,
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

    _obj_class |= Obj_GgafDx_FramedBoardActor;
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

    _is_2D = true;
    _pFunc_calc_rot_mv_world_matrix = nullptr;

    setZEnableDraw(false);
    setZWriteEnable(false);

    _z = 0;
}

void FramedBoardActor::processDraw() {
    if (_sx == 0 || _sy == 0) {
        return;
    }
    FramedBoardEffect* pFramedBoardEffect = _pFramedBoardEffect;
    ID3DXEffect* pID3DXEffect = pFramedBoardEffect->_pID3DXEffect;
    HRESULT hr;
    float u,v;

    //    ��������������
    //    ���O���P���Q��
    //    ��������������
    //    ���R���S���T��
    //    ��������������
    //    ���U���V���W��
    //    ��������������

    float frame_width_rate, center_width_rate;
    float total_width_px;
    int sgn_sx = SGN(_sx);
    if (ABS(_sx)  > _lim_center_sx) {
        //�����ɗ]�T����A1,4,7 �̉�����L�k������B

        //  f = _model_frame_width_px
        //  c = _model_center_width_px
        //          1.0
        //    <------------>
        //     f    c    f
        //   ����������������
        //   ���O�� �P ���Q��
        //   ����������������
        //   ���R�� �S ���T��
        //   ����������������
        //   ���U�� �V ���W��
        //   ����������������
        //
        //  1.0 �� r
        //
        //           r
        //    <------------->
        //     f     x     f
        //   ������������������
        //   ���O��  �P  ���Q��
        //   ������������������
        //   ���R��  �S  ���T��
        //   ������������������
        //   ���U��  �V  ���W��
        //   ������������������
        //
        //  2f+c : 1.0 =  2f+x : r
        //
        //  2f+x = r(2f+c)
        //  x = r(2f+c)-2f
        frame_width_rate = 1.0f * sgn_sx;
        pixcoord fw = 2*_model_frame_width_px;
        center_width_rate = ( SC_R(_sx)*(fw + _model_center_width_px) - fw ) / _model_center_width_px;
        total_width_px = fw + _model_center_width_px * center_width_rate;

    } else {
        //�����ɗ]�T�����A1,4,7 �̉�����0
        //0,3,6 �� 2,5,8 �̉����� �������䂪�߂ĕ��𒲐�
        //  l = _lim_center_sx
        //  f = _model_frame_width_px
        //          l
        //    <---------->
        //     f       f
        //   ��������������
        //   �� �O �� �Q ��
        //   ��������������
        //   �� �R �� �T ��
        //   ��������������
        //   �� �U �� �W ��
        //   ��������������
        //
        //  l �� r
        //
        //       r
        //    <------>
        //     x   x
        //   ����������
        //   ���O���Q��
        //   ����������
        //   ���R���T��
        //   ����������
        //   ���U���W��
        //   ����������
        //
        //  2f : l =  2x : r
        //
        //  l2x = r2f
        //  x = 2rf / 2l = rf / l
        frame_width_rate = 1.0f * _sx / _lim_center_sx;
        center_width_rate = 0.0f;
        total_width_px =  (_model_frame_width_px * frame_width_rate) + (_model_frame_width_px * frame_width_rate);
    }
    hr = pID3DXEffect->SetFloat(pFramedBoardEffect->_h_frame_width_rate, frame_width_rate);
    checkDxException(hr, D3D_OK, "SetFloat(_h_left_edge_size_rate) �Ɏ��s���܂����B");
    hr = pID3DXEffect->SetFloat(pFramedBoardEffect->_h_center_width_rate, center_width_rate);
    checkDxException(hr, D3D_OK, "SetFloat(_h_left_edge_size_rate) �Ɏ��s���܂����B");

    if (_align == ALIGN_RIGHT) {
        //2f+x = r(2f+c)
        hr = pID3DXEffect->SetFloat(pFramedBoardEffect->_h_local_offset_x, -total_width_px);
    } else if (_align == ALIGN_CENTER) {
        hr = pID3DXEffect->SetFloat(pFramedBoardEffect->_h_local_offset_x, -(total_width_px*0.5));
    } else { //ALIGN_LEFT �͂��̂܂�
        hr = pID3DXEffect->SetFloat(pFramedBoardEffect->_h_local_offset_x, 0.0f);
    }
    checkDxException(hr, D3D_OK, "SetFloat(_h_local_offset_x) �Ɏ��s���܂����B");

    float frame_height_rate, center_height_rate;
    float total_height_px;
    int sgn_sy = SGN(_sy);
    if (ABS(_sy) > _lim_center_sy) {
        //�c���ɗ]�T����A3,4,5 �̏c����L�k������B
        frame_height_rate = 1.0f * sgn_sy;
        pixcoord fh = 2*_model_frame_height_px;
        center_height_rate =  ( SC_R(_sy)*(fh + _model_center_height_px) - fh ) / _model_center_height_px;
        total_height_px = fh + _model_center_height_px * center_height_rate;
    } else {
        //�c���ɗ]�T�����A3,4,5 �̏c����0
        //0,1,2 �� 6,7,8 �̏c���� �������䂪�߂ĕ��𒲐�
        frame_height_rate = 1.0f * _sy / _lim_center_sy;
        center_height_rate = 0.0f;
        total_height_px = (_model_frame_height_px * frame_height_rate ) + (_model_frame_height_px * frame_height_rate );
    }

    hr = pID3DXEffect->SetFloat(pFramedBoardEffect->_h_frame_height_rate, frame_height_rate);
    checkDxException(hr, D3D_OK, "SetFloat(_h_top_edge_size_rate) �Ɏ��s���܂����B");
    hr = pID3DXEffect->SetFloat(pFramedBoardEffect->_h_center_height_rate, center_height_rate);
    checkDxException(hr, D3D_OK, "SetFloat(_h_left_edge_size_rate) �Ɏ��s���܂����B");

    if (_valign == VALIGN_BOTTOM) {
        hr = pID3DXEffect->SetFloat(pFramedBoardEffect->_h_local_offset_y, -total_height_px);
    } else if (_valign == VALIGN_MIDDLE) {
        hr = pID3DXEffect->SetFloat(pFramedBoardEffect->_h_local_offset_y, -total_height_px*0.5f);
    } else { //VALIGN_TOP �͂��̂܂�
        hr = pID3DXEffect->SetFloat(pFramedBoardEffect->_h_local_offset_y, 0.0f);
    }
    checkDxException(hr, D3D_OK, "SetFloat(_h_local_offset_y) �Ɏ��s���܂����B");

    hr = pID3DXEffect->SetFloat(pFramedBoardEffect->_h_x, C_PX(_x));
    checkDxException(hr, D3D_OK, "SetFloat(_h_x) �Ɏ��s���܂����B");
    hr = pID3DXEffect->SetFloat(pFramedBoardEffect->_h_y, C_PX(_y));
    checkDxException(hr, D3D_OK, "SetFloat(_h_y) �Ɏ��s���܂����B");
    hr = pID3DXEffect->SetFloat(pFramedBoardEffect->_h_z, C_PX(_z));
    checkDxException(hr, D3D_OK, "SetFloat(_h_z) �Ɏ��s���܂����B");
    hr = pID3DXEffect->SetFloat(pFramedBoardEffect->_h_alpha, _alpha);
    checkDxException(hr, D3D_OK, "SetFloat(_h_alpha) �Ɏ��s���܂����B");

    int active_frame_ptn_no = _pUvFlipper_frame->getActivePtn();
    for (int i = 0; i < 9; i++) {
        if (i == 4) {
            _pUvFlipper->getUV(u, v);
            hr = pID3DXEffect->SetFloat(pFramedBoardEffect->_ah_offset_u[4], u);
            checkDxException(hr, D3D_OK, "SetFloat(_h_offset_u) �Ɏ��s���܂����B");
            hr = pID3DXEffect->SetFloat(pFramedBoardEffect->_ah_offset_v[4], v);
            checkDxException(hr, D3D_OK, "SetFloat(_h_offset_v) �Ɏ��s���܂����B");
        } else {
            _pUvFlipper_frame->getUV(active_frame_ptn_no, u, v);
            hr = pID3DXEffect->SetFloat(pFramedBoardEffect->_ah_offset_u[i], u);
            checkDxException(hr, D3D_OK, "SetFloat(_h_offset_u) �Ɏ��s���܂����B");
            hr = pID3DXEffect->SetFloat(pFramedBoardEffect->_ah_offset_v[i], v);
            checkDxException(hr, D3D_OK, "SetFloat(_h_offset_v) �Ɏ��s���܂����B");
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

void FramedBoardActor::setAlign(Align prm_align, Valign prm_valign) {
    _align = prm_align;
    _valign = prm_valign;
}

void FramedBoardActor::setAlign(Align prm_align) {
    _align = prm_align;
}

void FramedBoardActor::setValign(Valign prm_valign) {
    _valign = prm_valign;
}

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
    _sz = sz; //_sz��2D�ł͎g�p����Ȃ����AScaler::behave() ���̔���Ŗ��ɗ��B
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
    _sz = R_SC(prm_z_rate); //_sz��2D�ł͎g�p����Ȃ����AScaler::behave() ���̔���Ŗ��ɗ��B
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
FramedBoardActor::~FramedBoardActor() {
    delete _pUvFlipper;
    delete _pUvFlipper_frame;
}
