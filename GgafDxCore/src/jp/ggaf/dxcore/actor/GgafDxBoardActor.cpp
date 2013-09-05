#include "stdafx.h"
#include "jp/ggaf/dxcore/actor/GgafDxBoardActor.h"

#include "jp/ggaf/dxcore/exception/GgafDxCriticalException.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxUvFlipper.h"
#include "jp/ggaf/dxcore/model/GgafDxBoardModel.h"
#include "jp/ggaf/dxcore/effect/GgafDxBoardEffect.h"
#include "jp/ggaf/dxcore/manager/GgafDxTextureConnection.h"

using namespace GgafCore;
using namespace GgafDxCore;

GgafDxBoardActor::GgafDxBoardActor(const char* prm_name,
                                   const char* prm_model_id,
                                   const char* prm_effect_id,
                                   const char* prm_technique) :
                                       GgafDxDrawableActor(prm_name,
                                                           prm_model_id,
                                                           "B",
                                                           prm_effect_id,
                                                           "B",
                                                           prm_technique,
                                                           nullptr,
                                                           nullptr) {
    _obj_class |= Obj_GgafDxBoardActor;
    _class_name = "GgafDxBoardActor";

    _pBoardModel = (GgafDxBoardModel*)_pModel;
    _pBoardEffect = (GgafDxBoardEffect*)_pEffect;
    _pUvFlipper = NEW GgafDxUvFlipper(_pBoardModel->_papTextureConnection[0]->peek());
    _pUvFlipper->setRotation(_pBoardModel->_col_texture_split,
                             _pBoardModel->_row_texture_split
                            );
    _pUvFlipper->setActivePtn(0);
    _pUvFlipper->exec(NOT_ANIMATED, 1);
    _width_px = (int)(_pBoardModel->_fSize_BoardModelWidthPx); //��(px)�AsetScale()���ɂ��ω�����I
    _height_px = (int)(_pBoardModel->_fSize_BoardModelHeightPx); //����(px)�AsetScale()���ɂ��ω�����I
    _harf_width_px = _width_px/2;
    _harf_height_px = _height_px/2;
    _align = ALIGN_LEFT;
    _valign = VALIGN_TOP;
    _alpha = 1.0f;
    _is_2D = true;
    _pFunc_calcRotMvWorldMatrix = nullptr;
    _Z = 0;
    setZEnable(false);
    setZWriteEnable(false);
}

void GgafDxBoardActor::processDraw() {
    ID3DXEffect* pID3DXEffect = _pBoardEffect->_pID3DXEffect;

    HRESULT hr;
    hr = pID3DXEffect->SetFloat(_pBoardEffect->_hTransformedX, float(C_PX(_X)));
    checkDxException(hr, D3D_OK, "GgafDxBoardModel::draw SetFloat(_hTransformedX) �Ɏ��s���܂����B3");
    hr = pID3DXEffect->SetFloat(_pBoardEffect->_hTransformedY, float(C_PX(_Y)));
    checkDxException(hr, D3D_OK, "GgafDxBoardModel::draw SetFloat(_hTransformedY) �Ɏ��s���܂����B3");

    if (_align == ALIGN_RIGHT) {
        hr = pID3DXEffect->SetFloat(_pBoardEffect->_h_local_left_top_X, (float)(-_width_px));
    } else if (_align == ALIGN_CENTER) {
        hr = pID3DXEffect->SetFloat(_pBoardEffect->_h_local_left_top_X, (float)(-_harf_width_px));
    } else { //ALIGN_LEFT
        hr = pID3DXEffect->SetFloat(_pBoardEffect->_h_local_left_top_X, 0.0f);
    }
    checkDxException(hr, D3D_OK, "GgafDxBoardModel::draw SetFloat(_h_local_left_top_X) �Ɏ��s���܂����B");
    if (_valign == VALIGN_BOTTOM) {
        hr = pID3DXEffect->SetFloat(_pBoardEffect->_h_local_left_top_Y, (float)(-_height_px));
    } else if (_valign == VALIGN_MIDDLE) {
        hr = pID3DXEffect->SetFloat(_pBoardEffect->_h_local_left_top_Y, (float)(-_harf_height_px));
    } else { //VALIGN_TOP
        hr = pID3DXEffect->SetFloat(_pBoardEffect->_h_local_left_top_Y, 0.0f);
    }
    checkDxException(hr, D3D_OK, "GgafDxBoardModel::draw SetFloat(_h_local_left_top_Y) �Ɏ��s���܂����B");

    hr = pID3DXEffect->SetFloat(_pBoardEffect->_hDepthZ, float(C_PX(_Z)));
    checkDxException(hr, D3D_OK, "GgafDxBoardModel::draw SetFloat(_hDepthZ) �Ɏ��s���܂����B");
    hr = pID3DXEffect->SetFloat(_pBoardEffect->_h_alpha, _alpha);
    checkDxException(hr, D3D_OK, "GgafDxBoardModel::draw SetFloat(_h_alpha) �Ɏ��s���܂����B");
    hr = pID3DXEffect->SetFloat(_pBoardEffect->_hSx, SC_R(_SX));
    checkDxException(hr, D3D_OK, "GgafDxBoardModel::draw SetFloat(_sx) �Ɏ��s���܂����B");
    hr = pID3DXEffect->SetFloat(_pBoardEffect->_hSy, SC_R(_SY));
    checkDxException(hr, D3D_OK, "GgafDxBoardModel::draw SetFloat(_sy) �Ɏ��s���܂����B");
    hr = pID3DXEffect->SetFloat(_pBoardEffect->_h_Rz, ANG_RAD(_RZ));
    checkDxException(hr, D3D_OK, "GgafDxBoardModel::draw SetFloat(_h_Rz) �Ɏ��s���܂����B");

    _pBoardModel->GgafDxBoardModel::draw(this);
}

void GgafDxBoardActor::setAlign(GgafDxAlign prm_align, GgafDxValign prm_valign) {
    _align = prm_align;
    _valign = prm_valign;
}
void GgafDxBoardActor::positionAs(GgafDxGeometricActor* prm_pActor) {
    _X = prm_pActor->_X;
    _Y = prm_pActor->_Y;
}

void GgafDxBoardActor::positionAs(GgafDxGeoElem* prm_pGeoElem) {
    _X = prm_pGeoElem->_X;
    _Y = prm_pGeoElem->_Y;
}

void GgafDxBoardActor::setScale(scale S) {
    _SX = S;
    _SY = S;
    _width_px = _pBoardModel->_fSize_BoardModelWidthPx * SC_R(S);
    _height_px = _pBoardModel->_fSize_BoardModelHeightPx * SC_R(S);
    _harf_width_px = _width_px/2;
    _harf_height_px = _height_px/2;
}

void GgafDxBoardActor::setScale(scale SX, scale SY) {
    _SX = SX;
    _SY = SY;
    _width_px = _pBoardModel->_fSize_BoardModelWidthPx * SC_R(SX);
    _height_px = _pBoardModel->_fSize_BoardModelHeightPx * SC_R(SY);
    _harf_width_px = _width_px/2;
    _harf_height_px = _height_px/2;
}

void GgafDxBoardActor::setScale(scale SX, scale SY, scale SZ) {
    _SX = SX;
    _SY = SY;
    _SZ = SZ; //_SZ��2D�ł͎g�p����Ȃ����AGgafDxScaler::behave() ���̔���Ŗ��ɗ��B
    _width_px = _pBoardModel->_fSize_BoardModelWidthPx * SC_R(SX);
    _height_px = _pBoardModel->_fSize_BoardModelHeightPx * SC_R(SY);
    _harf_width_px = _width_px/2;
    _harf_height_px = _height_px/2;
}

void GgafDxBoardActor::setScaleR(float prm_rate) {
    _SX = R_SC(prm_rate);
    _SY = R_SC(prm_rate);
    _width_px = _pBoardModel->_fSize_BoardModelWidthPx * prm_rate;
    _height_px = _pBoardModel->_fSize_BoardModelHeightPx * prm_rate;
    _harf_width_px = _width_px/2;
    _harf_height_px = _height_px/2;
}

void GgafDxBoardActor::setScaleR(float prm_x_rate, float prm_y_rate) {
    _SX = R_SC(prm_x_rate);
    _SY = R_SC(prm_y_rate);
    _width_px = _pBoardModel->_fSize_BoardModelWidthPx * prm_x_rate;
    _height_px = _pBoardModel->_fSize_BoardModelHeightPx * prm_y_rate;
    _harf_width_px = _width_px/2;
    _harf_height_px = _height_px/2;
}

void GgafDxBoardActor::setScaleR(float prm_x_rate, float prm_y_rate, float prm_z_rate) {
    _SX = R_SC(prm_x_rate);
    _SY = R_SC(prm_y_rate);
    _SZ = R_SC(prm_z_rate); //_SZ��2D�ł͎g�p����Ȃ����AGgafDxScaler::behave() ���̔���Ŗ��ɗ��B
    _width_px = _pBoardModel->_fSize_BoardModelWidthPx * prm_x_rate;
    _height_px = _pBoardModel->_fSize_BoardModelHeightPx * prm_y_rate;
    _harf_width_px = _width_px/2;
    _harf_height_px = _height_px/2;
}

GgafDxBoardActor::~GgafDxBoardActor() {
    GGAF_DELETE(_pUvFlipper);
}
