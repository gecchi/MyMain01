#include "stdafx.h"
#include "jp/ggaf/dxcore/actor/GgafDxSpriteActor.h"

#include "jp/ggaf/dxcore/exception/GgafDxCriticalException.h"
#include "jp/ggaf/dxcore/GgafDxGod.h"
#include "jp/ggaf/dxcore/util/GgafDxUtil.h"
#include "jp/ggaf/dxcore/effect/GgafDxSpriteEffect.h"
#include "jp/ggaf/dxcore/model/GgafDxSpriteModel.h"
#include "jp/ggaf/dxcore/manager/GgafDxTextureConnection.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxUvFlipper.h"

using namespace GgafCore;
using namespace GgafDxCore;

GgafDxSpriteActor::GgafDxSpriteActor(const char* prm_name,
                                     const char* prm_model_id,
                                     const char* prm_effect_id,
                                     const char* prm_technique,
                                     GgafStatus* prm_pStat,
                                     GgafDxChecker* prm_pChecker) :

                                         GgafDxDrawableActor(prm_name,
                                                             prm_model_id,
                                                             "S",
                                                             prm_effect_id,
                                                             "S",
                                                             prm_technique,
                                                             prm_pStat,
                                                             prm_pChecker),
_pSpriteModel( (GgafDxSpriteModel*)_pModel),
_pSpriteEffect( (GgafDxSpriteEffect*)_pEffect),
_pUvFlipper(NEW GgafDxUvFlipper(_pSpriteModel->_papTextureConnection[0]->peek())) {

    _obj_class |= Obj_GgafDxSpriteActor;
    _class_name = "GgafDxSpriteActor";
    _pUvFlipper->setRotation(_pSpriteModel->_col_texture_split,
                             _pSpriteModel->_row_texture_split );
    _pUvFlipper->setActivePtn(0);
    _pUvFlipper->exec(NOT_ANIMATED, 1);

    _pFunc_calc_rot_mv_world_matrix = UTIL::setWorldMatrix_RxRzRyMv;
    (*_pFunc_calc_rot_mv_world_matrix)(this, _matWorldRotMv);
    _far_rate = -1.0f;

    _align = ALIGN_CENTER;
    _valign = VALIGN_MIDDLE;
}

void GgafDxSpriteActor::processDraw() {
    ID3DXEffect* pID3DXEffect = _pSpriteEffect->_pID3DXEffect;
    HRESULT hr;
    if (_align == ALIGN_CENTER) {
        //do nothing
    } else if (_align == ALIGN_LEFT) {
        _matWorld._41 += PX_C(_pSpriteModel->_model_width_px*0.5f);
    } else {
        //ALIGN_RIGHT
        _matWorld._41 -= PX_C(_pSpriteModel->_model_width_px*0.5f);
    }
    if (_valign == VALIGN_MIDDLE) {
        //do nothing
    } else if (_valign == VALIGN_TOP) {
        _matWorld._42 -= PX_C(_pSpriteModel->_model_height_px*0.5f);
    } else {
        //VALIGN_BOTTOM
        _matWorld._42 += PX_C(_pSpriteModel->_model_height_px*0.5f);
    }
//    hr = pID3DXEffect->SetMatrix(_pSpriteEffect->_h_matView, &P_CAM->_matView );
//    checkDxException(hr, D3D_OK, "GgafDxMeshActor::GgafDxMeshEffect SetMatrix(g_matView) に失敗しました。");
    //(*_pFunc_calc_rot_mv_world_matrix)(this, _matWorld);
    hr = pID3DXEffect->SetMatrix(_pSpriteEffect->_h_matWorld, &_matWorld );
    checkDxException(hr, D3D_OK, "GgafDxSpriteActor::processDraw SetMatrix(_h_matWorld) に失敗しました。");
//    hr = pID3DXEffect->SetFloat(_pSpriteEffect->_h_alpha, _alpha);
//    checkDxException(hr, D3D_OK, "GgafDxSpriteActor::processDraw SetFloat(_alpha) に失敗しました。");
    hr = pID3DXEffect->SetValue(_pSpriteEffect->_h_colMaterialDiffuse, &(_paMaterial[0].Diffuse), sizeof(D3DCOLORVALUE) );
    checkDxException(hr, D3D_OK, "GgafDxSpriteActor::draw() SetValue(_h_colMaterialDiffuse) に失敗しました。");
    hr = pID3DXEffect->SetFloat(_pSpriteEffect->_h_far_rate, _far_rate );
    checkDxException(hr, D3D_OK, "GgafDxMeshActor::processDraw() SetFloat(_h_far_rate) に失敗しました。");
    _pSpriteModel->GgafDxSpriteModel::draw(this);
}

void GgafDxSpriteActor::setAlpha(float prm_alpha) {
    _alpha = prm_alpha;
    //α設定、現在マテリアルはDiffuse以外関係ない
    _paMaterial[0].Ambient.a = _alpha;
    _paMaterial[0].Diffuse.a = _alpha;
}

void GgafDxSpriteActor::addAlpha(float prm_alpha) {
    _alpha += prm_alpha;
    //α設定、現在マテリアルはDiffuse以外関係ない
    _paMaterial[0].Ambient.a = _alpha;
    _paMaterial[0].Diffuse.a = _alpha;
}

void GgafDxSpriteActor::setAlign(GgafDxAlign prm_align, GgafDxValign prm_valign) {
    _align = prm_align;
    _valign = prm_valign;
}

void GgafDxSpriteActor::setAlign(GgafDxAlign prm_align) {
    _align = prm_align;
}

void GgafDxSpriteActor::setValign(GgafDxValign prm_valign) {
    _valign = prm_valign;
}

GgafDxSpriteActor::~GgafDxSpriteActor() {
    delete _pUvFlipper;
}
