#include "stdafx.h"
#include "jp/ggaf/dxcore/actor/GgafDxBoardSetActor.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxUvFlipper.h"
#include "jp/ggaf/dxcore/effect/GgafDxBoardSetEffect.h"
#include "jp/ggaf/dxcore/exception/GgafDxCriticalException.h"
#include "jp/ggaf/dxcore/manager/GgafDxTextureConnection.h"
#include "jp/ggaf/dxcore/model/GgafDxBoardSetModel.h"
#include "jp/ggaf/dxcore/scene/GgafDxUniverse.h"

using namespace GgafCore;
using namespace GgafDxCore;

GgafDxBoardSetActor::GgafDxBoardSetActor(const char* prm_name,
                                         const char* prm_model_id,
                                         const char* prm_effect_id,
                                         const char* prm_technique) :

                                             GgafDxDrawableActor(prm_name,
                                                                 prm_model_id,
                                                                 "b",
                                                                 prm_effect_id,
                                                                 "b",
                                                                 prm_technique,
                                                                 nullptr,
                                                                 nullptr) ,
_pBoardSetModel((GgafDxBoardSetModel*)_pModel),
_pBoardSetEffect((GgafDxBoardSetEffect*)_pEffect),
_pUvFlipper(NEW GgafDxUvFlipper(_pBoardSetModel->_papTextureConnection[0]->peek())) {

    _obj_class |= Obj_GgafDxBoardSetActor;
    _class_name = "GgafDxBoardSetActor";
    _pUvFlipper->setRotation(_pBoardSetModel->_col_texture_split,
                             _pBoardSetModel->_row_texture_split
                            );
    _pUvFlipper->setActivePtn(0);
    _pUvFlipper->exec(NOT_ANIMATED, 1);

    _width_px = (int)(_pBoardSetModel->_fSize_BoardSetModelWidthPx); //幅(px)
    _height_px = (int)(_pBoardSetModel->_fSize_BoardSetModelHeightPx); //高さ(px)
    _harf_width_px = _width_px/2;
    _harf_height_px = _height_px/2;
    _align = ALIGN_LEFT;
    _valign = VALIGN_TOP;
    _alpha = 1.0f;

    _is_2D = true;
    _pFunc_calcRotMvWorldMatrix = nullptr;

    setZEnable(false);
    setZWriteEnable(false);

    _z = 0;
}

void GgafDxBoardSetActor::processDraw() {
    int draw_set_num = 0; //GgafDxBoardSetActorの同じモデルで同じテクニックが
                       //連続しているカウント数。同一描画深度は一度に描画する。
    GgafDxBoardSetEffect* pBoardSetEffect = _pBoardSetEffect;
    ID3DXEffect* pID3DXEffect = pBoardSetEffect->_pID3DXEffect;
    HRESULT hr;
    GgafDxDrawableActor* pDrawActor = this;
    GgafDxBoardSetActor* pBoardSetActor = nullptr;
    int model_set_num = _pBoardSetModel->_set_num;
    float u,v;
    while (pDrawActor) {
        if (pDrawActor->getModel() == _pBoardSetModel && pDrawActor->_hash_technique == _hash_technique) {
            pBoardSetActor = (GgafDxBoardSetActor*)pDrawActor;

            if (_align == ALIGN_RIGHT) {
                hr = pID3DXEffect->SetFloat(pBoardSetEffect->_ah_transformed_x[draw_set_num], C_PX(pBoardSetActor->_x) - pBoardSetActor->_width_px);
            } else if (_align == ALIGN_CENTER) {
                hr = pID3DXEffect->SetFloat(pBoardSetEffect->_ah_transformed_x[draw_set_num], C_PX(pBoardSetActor->_x) - (pBoardSetActor->_harf_width_px));
            } else {
                //ALIGN_LEFT
                hr = pID3DXEffect->SetFloat(pBoardSetEffect->_ah_transformed_x[draw_set_num], C_PX(pBoardSetActor->_x));
            }
            checkDxException(hr, D3D_OK, "GgafDxBoardSetModel::draw SetFloat(_ah_transformed_x) に失敗しました。");
            if (_valign == VALIGN_BOTTOM) {
                hr = pID3DXEffect->SetFloat(pBoardSetEffect->_ah_transformed_y[draw_set_num], C_PX(pBoardSetActor->_y) - pBoardSetActor->_height_px);
            } else if (_valign == VALIGN_MIDDLE) {
                hr = pID3DXEffect->SetFloat(pBoardSetEffect->_ah_transformed_y[draw_set_num], C_PX(pBoardSetActor->_y) - (pBoardSetActor->_harf_height_px));
            } else {
                //VALIGN_TOP
                hr = pID3DXEffect->SetFloat(pBoardSetEffect->_ah_transformed_y[draw_set_num], C_PX(pBoardSetActor->_y));
            }
            checkDxException(hr, D3D_OK, "GgafDxBoardSetModel::draw SetFloat(_ah_transformed_y) に失敗しました。");
            hr = pID3DXEffect->SetFloat(pBoardSetEffect->_ah_depth_z[draw_set_num], C_PX(pBoardSetActor->_z));
            checkDxException(hr, D3D_OK, "GgafDxBoardSetModel::draw SetFloat(_ah_depth_z) に失敗しました。");
            hr = pID3DXEffect->SetFloat(pBoardSetEffect->_ah_alpha[draw_set_num], pBoardSetActor->_alpha);
            checkDxException(hr, D3D_OK, "GgafDxBoardSetModel::draw SetFloat(_ah_alpha) に失敗しました。");
            pBoardSetActor->_pUvFlipper->getUV(u,v);
            hr = pID3DXEffect->SetFloat(pBoardSetEffect->_ah_offset_u[draw_set_num], u);
            checkDxException(hr, D3D_OK, "GgafDxBoardModel::draw() SetFloat(_h_offset_u) に失敗しました。");
            hr = pID3DXEffect->SetFloat(pBoardSetEffect->_ah_offset_v[draw_set_num], v);
            checkDxException(hr, D3D_OK, "GgafDxBoardModel::draw() SetFloat(_h_offset_v) に失敗しました。");

            draw_set_num++;
            if (draw_set_num >= model_set_num) {
                break;
            }
            pDrawActor = pDrawActor->_pNext_TheSameDrawDepthLevel;
        } else {
            break;
        }
    }
    GgafDxUniverse::_pActor_DrawActive = pBoardSetActor; //描画セットの最後アクターをセット
    _pBoardSetModel->GgafDxBoardSetModel::draw(this, draw_set_num);
}

void GgafDxBoardSetActor::positionAs(GgafDxGeometricActor* prm_pActor) {
    _x = prm_pActor->_x;
    _y = prm_pActor->_y;
}

void GgafDxBoardSetActor::positionAs(GgafDxGeoElem* prm_pGeoElem) {
    _x = prm_pGeoElem->x;
    _y = prm_pGeoElem->y;
}

void GgafDxBoardSetActor::setAlign(GgafDxAlign prm_align, GgafDxValign prm_valign) {
    _align = prm_align;
    _valign = prm_valign;
}

void GgafDxBoardSetActor::setAlign(GgafDxAlign prm_align) {
    _align = prm_align;
}

void GgafDxBoardSetActor::setValign(GgafDxValign prm_valign) {
    _valign = prm_valign;
}

float GgafDxBoardSetActor::getModelWidth() {
    return _pBoardSetModel->_fSize_BoardSetModelWidthPx;
}

float GgafDxBoardSetActor::getModelHeight() {
    return _pBoardSetModel->_fSize_BoardSetModelHeightPx;
}

GgafDxBoardSetActor::~GgafDxBoardSetActor() {
    delete _pUvFlipper;
}
