#include "jp/ggaf/dx/actor/FramedSpriteActor.h"

#include "jp/ggaf/dx/exception/CriticalException.h"
#include "jp/ggaf/dx/God.h"
#include "jp/ggaf/dx/util/Util.h"
#include "jp/ggaf/dx/effect/FramedSpriteEffect.h"
#include "jp/ggaf/dx/model/FramedSpriteModel.h"
#include "jp/ggaf/dx/manager/TextureConnection.h"
#include "jp/ggaf/dx/actor/supporter/UvFlipper.h"

using namespace GgafDx;

FramedSpriteActor::FramedSpriteActor(const char* prm_name,
                         const char* prm_model,
                         const char* prm_effect_id,
                         const char* prm_technique,
                         Checker* prm_pChecker) :

                             FigureActor(prm_name,
                                         prm_model,
                                         TYPE_FRAMEDSPRITE_MODEL,
                                         prm_effect_id,
                                         TYPE_FRAMEDSPRITE_EFFECT,
                                         prm_technique,
                                         prm_pChecker),
_pFramedSpriteModel( (FramedSpriteModel*)_pModel),
_pFramedSpriteEffect( (FramedSpriteEffect*)_pEffect),
_pUvFlipper(NEW UvFlipper(getModel()->_papTextureConnection[0]->peek())),
_pUvFlipper_frame(NEW UvFlipper(getModel()->_papTextureConnection[1]->peek())),
_model_frame_width_px((pixcoord)(_pFramedSpriteModel->_model_frame_width_px)),
_model_frame_height_px((pixcoord)(_pFramedSpriteModel->_model_frame_height_px)),
_model_center_width_px((pixcoord)(_pFramedSpriteModel->_model_width_px)),
_model_center_height_px((pixcoord)(_pFramedSpriteModel->_model_height_px)),
_model_total_width_px(_model_frame_width_px * 2 + _model_center_width_px),
_model_total_height_px(_model_frame_height_px * 2 + _model_center_height_px),
_lim_center_sx(R_SC( (_model_frame_width_px * 2.0) / _model_total_width_px )),
_lim_center_sy(R_SC( (_model_frame_height_px * 2.0) / _model_total_height_px )) {

    _obj_class |= Obj_GgafDx_FramedSpriteActor;
    _class_name = "FramedSpriteActor";
    _pUvFlipper->locatePatternNo(_pFramedSpriteModel->_col_texture_split,
                                 _pFramedSpriteModel->_row_texture_split );
    _pUvFlipper->setActivePtn(0);
    _pUvFlipper->exec(NOT_ANIMATED, 1);

    _pUvFlipper_frame->locatePatternNo(_pFramedSpriteModel->_col_frame_texture_split,
                                       _pFramedSpriteModel->_row_frame_texture_split );
    _pUvFlipper_frame->setActivePtn(0);
    _pUvFlipper_frame->exec(NOT_ANIMATED, 1);

    defineRotMvWorldMatrix(UTIL::setWorldMatrix_RxRzRyMv); //�f�t�H���g�̉�]�~�ړ��̕ϊ��s��
    _far_rate = -1.0f;

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
    hr = pID3DXEffect->SetFloat(pFramedSpriteEffect->_h_frame_width_rate, frame_width_rate);
    checkDxException(hr, D3D_OK, "SetFloat(_h_left_edge_size_rate) �Ɏ��s���܂����B");
    hr = pID3DXEffect->SetFloat(pFramedSpriteEffect->_h_center_width_rate, center_width_rate);
    checkDxException(hr, D3D_OK, "SetFloat(_h_left_edge_size_rate) �Ɏ��s���܂����B");


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
//    } else { //ALIGN_LEFT �͂��̂܂�
//        hr = pID3DXEffect->SetFloat(pFramedSpriteEffect->_h_local_offset_x, 0.0f);
//    }
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

    hr = pID3DXEffect->SetFloat(pFramedSpriteEffect->_h_frame_height_rate, frame_height_rate);
    checkDxException(hr, D3D_OK, "SetFloat(_h_top_edge_size_rate) �Ɏ��s���܂����B");
    hr = pID3DXEffect->SetFloat(pFramedSpriteEffect->_h_center_height_rate, center_height_rate);
    checkDxException(hr, D3D_OK, "SetFloat(_h_left_edge_size_rate) �Ɏ��s���܂����B");
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
//    } else { //VALIGN_TOP �͂��̂܂�
//        hr = pID3DXEffect->SetFloat(pFramedSpriteEffect->_h_local_offset_y, 0.0f);
//    }

    checkDxException(hr, D3D_OK, "SetFloat(_h_local_offset_y) �Ɏ��s���܂����B");

    hr = pID3DXEffect->SetFloat(pFramedSpriteEffect->_h_x, C_PX(_x));
    checkDxException(hr, D3D_OK, "SetFloat(_h_x) �Ɏ��s���܂����B");
    hr = pID3DXEffect->SetFloat(pFramedSpriteEffect->_h_y, C_PX(_y));
    checkDxException(hr, D3D_OK, "SetFloat(_h_y) �Ɏ��s���܂����B");
    hr = pID3DXEffect->SetFloat(pFramedSpriteEffect->_h_z, C_PX(_z));
    checkDxException(hr, D3D_OK, "SetFloat(_h_z) �Ɏ��s���܂����B");
    hr = pID3DXEffect->SetFloat(pFramedSpriteEffect->_h_alpha, _alpha);
    checkDxException(hr, D3D_OK, "SetFloat(_h_alpha) �Ɏ��s���܂����B");

    int active_frame_ptn_no = _pUvFlipper_frame->getActivePtn();
    for (int i = 0; i < 9; i++) {
        if (i == 4) {
            _pUvFlipper->getUV(u, v);
            hr = pID3DXEffect->SetFloat(pFramedSpriteEffect->_ah_offset_u[4], u);
            checkDxException(hr, D3D_OK, "SetFloat(_h_offset_u) �Ɏ��s���܂����B");
            hr = pID3DXEffect->SetFloat(pFramedSpriteEffect->_ah_offset_v[4], v);
            checkDxException(hr, D3D_OK, "SetFloat(_h_offset_v) �Ɏ��s���܂����B");
        } else {
            _pUvFlipper_frame->getUV(active_frame_ptn_no, u, v);
            hr = pID3DXEffect->SetFloat(pFramedSpriteEffect->_ah_offset_u[i], u);
            checkDxException(hr, D3D_OK, "SetFloat(_h_offset_u) �Ɏ��s���܂����B");
            hr = pID3DXEffect->SetFloat(pFramedSpriteEffect->_ah_offset_v[i], v);
            checkDxException(hr, D3D_OK, "SetFloat(_h_offset_v) �Ɏ��s���܂����B");
            active_frame_ptn_no++;
        }
    }

    _pFramedSpriteModel->FramedSpriteModel::draw(this);


//    hr = pID3DXEffect->SetMatrix(_pFramedSpriteEffect->_h_matWorld, &_matWorld );
//    checkDxException(hr, D3D_OK, "SetMatrix(_h_matWorld) �Ɏ��s���܂����B");
    hr = pID3DXEffect->SetValue(_pFramedSpriteEffect->_h_colMaterialDiffuse, &(_paMaterial[0].Diffuse), sizeof(D3DCOLORVALUE) );
    checkDxException(hr, D3D_OK, "SetValue(_h_colMaterialDiffuse) �Ɏ��s���܂����B");
    hr = pID3DXEffect->SetFloat(_pFramedSpriteEffect->_h_far_rate, _far_rate );
    checkDxException(hr, D3D_OK, "SetFloat(_h_far_rate) �Ɏ��s���܂����B");
    _pFramedSpriteModel->FramedSpriteModel::draw(this);
}

FramedSpriteActor::~FramedSpriteActor() {
    delete _pUvFlipper;
}
