#include "stdafx.h"
#include "jp/ggaf/dxcore/actor/GgafDxBoardActor.h"

#include "jp/ggaf/dxcore/util/GgafDxUtil.h"
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
                                                           nullptr) ,
_pBoardModel((GgafDxBoardModel*)_pModel),
_pBoardEffect((GgafDxBoardEffect*)_pEffect) ,
_pUvFlipper(NEW GgafDxUvFlipper(_pBoardModel->_papTextureConnection[0]->peek())) {

    _obj_class |= Obj_GgafDxBoardActor;
    _class_name = "GgafDxBoardActor";
    _pUvFlipper->setRotation(_pBoardModel->_col_texture_split,
                             _pBoardModel->_row_texture_split );
    _pUvFlipper->setActivePtn(0);
    _pUvFlipper->exec(NOT_ANIMATED, 1);
    _align = ALIGN_LEFT;
    _valign = VALIGN_TOP;
    _alpha = 1.0f;
    _is_2D = true;
    _pFunc_calcRotMvWorldMatrix = nullptr;
    _z = 0;
    setZEnable(false);
    setZWriteEnable(false);
}

void GgafDxBoardActor::processDraw() {
    ID3DXEffect* pID3DXEffect = _pBoardEffect->_pID3DXEffect;

    HRESULT hr;
    hr = pID3DXEffect->SetFloat(_pBoardEffect->_hTransformedX, float(C_PX(_x)));
    checkDxException(hr, D3D_OK, "GgafDxBoardActor::draw SetFloat(_hTransformedX) に失敗しました。3");
    hr = pID3DXEffect->SetFloat(_pBoardEffect->_hTransformedY, float(C_PX(_y)));
    checkDxException(hr, D3D_OK, "GgafDxBoardActor::draw SetFloat(_hTransformedY) に失敗しました。3");

    if (_align == ALIGN_RIGHT) {
        hr = pID3DXEffect->SetFloat(_pBoardEffect->_h_local_left_top_x, (float)(-_pBoardModel->_fSize_BoardModelWidthPx));
    } else if (_align == ALIGN_CENTER) {
        hr = pID3DXEffect->SetFloat(_pBoardEffect->_h_local_left_top_x, (float)(-_pBoardModel->_fSize_BoardModelWidthPx*0.5));
    } else { //ALIGN_LEFT
        hr = pID3DXEffect->SetFloat(_pBoardEffect->_h_local_left_top_x, 0.0f);
    }
    checkDxException(hr, D3D_OK, "GgafDxBoardActor::draw SetFloat(_h_local_left_top_x) に失敗しました。");
    if (_valign == VALIGN_BOTTOM) {
        hr = pID3DXEffect->SetFloat(_pBoardEffect->_h_local_left_top_y, (float)(-_pBoardModel->_fSize_BoardModelHeightPx));
    } else if (_valign == VALIGN_MIDDLE) {
        hr = pID3DXEffect->SetFloat(_pBoardEffect->_h_local_left_top_y, (float)(-_pBoardModel->_fSize_BoardModelHeightPx*0.5));
    } else { //VALIGN_TOP
        hr = pID3DXEffect->SetFloat(_pBoardEffect->_h_local_left_top_y, 0.0f);
    }
    checkDxException(hr, D3D_OK, "GgafDxBoardActor::draw SetFloat(_h_local_left_top_y) に失敗しました。");
    hr = pID3DXEffect->SetFloat(_pBoardEffect->_hDepthZ, float(C_PX(_z)));
    checkDxException(hr, D3D_OK, "GgafDxBoardActor::draw SetFloat(_hDepthZ) に失敗しました。");
//    hr = pID3DXEffect->SetFloat(_pBoardEffect->_h_alpha, _alpha);
//    checkDxException(hr, D3D_OK, "GgafDxBoardActor::draw SetFloat(_h_alpha) に失敗しました。");
    hr = pID3DXEffect->SetValue(_pBoardEffect->_h_colMaterialDiffuse, &(_paMaterial[0].Diffuse), sizeof(D3DCOLORVALUE) );
    checkDxException(hr, D3D_OK, "GgafDxBoardActor::draw() SetValue(_h_colMaterialDiffuse) に失敗しました。");

    hr = pID3DXEffect->SetFloat(_pBoardEffect->_hSx, SC_R(_sx));
    checkDxException(hr, D3D_OK, "GgafDxBoardActor::draw SetFloat(_sx) に失敗しました。");
    hr = pID3DXEffect->SetFloat(_pBoardEffect->_hSy, SC_R(_sy));
    checkDxException(hr, D3D_OK, "GgafDxBoardActor::draw SetFloat(_sy) に失敗しました。");
    hr = pID3DXEffect->SetFloat(_pBoardEffect->_h_Rz, ANG_RAD(_rz));
    checkDxException(hr, D3D_OK, "GgafDxBoardActor::draw SetFloat(_h_Rz) に失敗しました。");

    _pBoardModel->GgafDxBoardModel::draw(this);
}

void GgafDxBoardActor::setAlign(GgafDxAlign prm_align, GgafDxValign prm_valign) {
    _align = prm_align;
    _valign = prm_valign;
}
void GgafDxBoardActor::setAlign(GgafDxAlign prm_align) {
    _align = prm_align;
}
void GgafDxBoardActor::setValign(GgafDxValign prm_valign) {
    _valign = prm_valign;
}

void GgafDxBoardActor::positionAs(GgafDxGeometricActor* prm_pActor) {
    _x = prm_pActor->_x;
    _y = prm_pActor->_y;
}

void GgafDxBoardActor::positionAs(GgafDxGeoElem* prm_pGeoElem) {
    _x = prm_pGeoElem->x;
    _y = prm_pGeoElem->y;
}

void GgafDxBoardActor::setScale(scale s) {
    _sx = s;
    _sy = s;
}

void GgafDxBoardActor::setScale(scale sx, scale sy) {
    _sx = sx;
    _sy = sy;
}

void GgafDxBoardActor::setScale(scale sx, scale sy, scale sz) {
    _sx = sx;
    _sy = sy;
    _sz = sz; //_szは2Dでは使用されないが、GgafDxScaler::behave() 内の判定で役に立つ。
}

void GgafDxBoardActor::setScaleR(float prm_rate) {
    _sx = R_SC(prm_rate);
    _sy = R_SC(prm_rate);
}

void GgafDxBoardActor::setScaleR(float prm_x_rate, float prm_y_rate) {
    _sx = R_SC(prm_x_rate);
    _sy = R_SC(prm_y_rate);
}

void GgafDxBoardActor::setScaleR(float prm_x_rate, float prm_y_rate, float prm_z_rate) {
    _sx = R_SC(prm_x_rate);
    _sy = R_SC(prm_y_rate);
    _sz = R_SC(prm_z_rate); //_szは2Dでは使用されないが、GgafDxScaler::behave() 内の判定で役に立つ。
}
void GgafDxBoardActor::setAlpha(float prm_alpha) {
    _alpha = prm_alpha;
    //α設定、現在マテリアルはDiffuse以外関係ない
    _paMaterial[0].Ambient.a = _alpha;
    _paMaterial[0].Diffuse.a = _alpha;
}

void GgafDxBoardActor::addAlpha(float prm_alpha) {
    _alpha += prm_alpha;
    //α設定、現在マテリアルはDiffuse以外関係ない
    _paMaterial[0].Ambient.a = _alpha;
    _paMaterial[0].Diffuse.a = _alpha;
}

float GgafDxBoardActor::getModelWidth() {
    return _pBoardModel->_fSize_BoardModelWidthPx;
}

float GgafDxBoardActor::getModelHeight() {
    return _pBoardModel->_fSize_BoardModelHeightPx;
}

GgafDxBoardActor::~GgafDxBoardActor() {
    delete _pUvFlipper;
}
