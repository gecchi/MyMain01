#include "jp/ggaf/dxcore/actor/GgafDxRegularPolygonSpriteActor.h"

#include "jp/ggaf/dxcore/exception/GgafDxCriticalException.h"
#include "jp/ggaf/dxcore/GgafDxGod.h"
#include "jp/ggaf/dxcore/util/GgafDxUtil.h"
#include "jp/ggaf/dxcore/effect/GgafDxRegularPolygonSpriteEffect.h"
#include "jp/ggaf/dxcore/model/GgafDxRegularPolygonSpriteModel.h"
#include "jp/ggaf/dxcore/manager/GgafDxTextureConnection.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxUvFlipper.h"

using namespace GgafCore;
using namespace GgafDxCore;

GgafDxRegularPolygonSpriteActor::GgafDxRegularPolygonSpriteActor(const char* prm_name,
                                     const char* prm_model_id,
                                     const char* prm_effect_id,
                                     const char* prm_technique,
                                     GgafStatus* prm_pStat,
                                     GgafDxChecker* prm_pChecker) :

                                         GgafDxFigureActor(prm_name,
                                                           prm_model_id,
                                                           TYPE_REGULARPOLYGONSPRITE_MODEL,
                                                           prm_effect_id,
                                                           TYPE_REGULARPOLYGONSPRITE_EFFECT,
                                                           prm_technique,
                                                           prm_pStat,
                                                           prm_pChecker),
_pRegularPolygonSpriteModel( (GgafDxRegularPolygonSpriteModel*)_pModel),
_pRegularPolygonSpriteEffect( (GgafDxRegularPolygonSpriteEffect*)_pEffect),
_pUvFlipper(NEW GgafDxUvFlipper(getModel()->getDefaultTextureConnection()->peek())) {

    _obj_class |= Obj_GgafDxRegularPolygonSpriteActor;
    _class_name = "GgafDxRegularPolygonSpriteActor";
    _pUvFlipper->setRotation(_pRegularPolygonSpriteModel->_col_texture_split,
                             _pRegularPolygonSpriteModel->_row_texture_split );
    _pUvFlipper->setActivePtn(0);
    _pUvFlipper->exec(NOT_ANIMATED, 1);

    defineRotMvWorldMatrix(UTIL::setWorldMatrix_RxRzRyMv); //ƒfƒtƒHƒ‹ƒg‚Ì‰ñ“]~ˆÚ“®‚Ì•ÏŠ·s—ñ
    _far_rate = -1.0f;

    _draw_fan_num = _pRegularPolygonSpriteModel->_angle_num;
    _cull_mode = _pRegularPolygonSpriteModel->_drawing_order == 1 ?  D3DCULL_CCW : D3DCULL_CW;
    _circumference_begin_position = 0;
    _align = ALIGN_CENTER;
    _valign = VALIGN_MIDDLE;
}

void GgafDxRegularPolygonSpriteActor::processDraw() {
    ID3DXEffect* const pID3DXEffect = _pRegularPolygonSpriteEffect->_pID3DXEffect;
    HRESULT hr;
    angle a = UTIL::simplifyAng(_circumference_begin_position);
    float sin_rz = ANG_SIN(a);
    float cos_rz = ANG_COS(a);
//    if (_align == ALIGN_CENTER) {
//        //do nothing
//    } else if (_align == ALIGN_LEFT) {
//        _matWorld._41 += PX_DX(_pRegularPolygonSpriteModel->_model_width_px/2);
//    } else {
//        //ALIGN_RIGHT
//        _matWorld._41 -= PX_DX(_pRegularPolygonSpriteModel->_model_width_px/2);
//    }
//    if (_valign == VALIGN_MIDDLE) {
//        //do nothing
//    } else if (_valign == VALIGN_TOP) {
//        _matWorld._42 -= PX_DX(_pRegularPolygonSpriteModel->_model_height_px/2);
//    } else {
//        //VALIGN_BOTTOM
//        _matWorld._42 += PX_DX(_pRegularPolygonSpriteModel->_model_height_px/2);
//    }
    hr = pID3DXEffect->SetMatrix(_pRegularPolygonSpriteEffect->_h_matWorld, &_matWorld );
    checkDxException(hr, D3D_OK, "SetMatrix(_h_matWorld) ‚ÉŽ¸”s‚µ‚Ü‚µ‚½B");
    hr = pID3DXEffect->SetValue(_pRegularPolygonSpriteEffect->_h_colMaterialDiffuse, &(_paMaterial[0].Diffuse), sizeof(D3DCOLORVALUE) );
    checkDxException(hr, D3D_OK, "SetValue(_h_colMaterialDiffuse) ‚ÉŽ¸”s‚µ‚Ü‚µ‚½B");
    hr = pID3DXEffect->SetFloat(_pRegularPolygonSpriteEffect->_h_far_rate, _far_rate );
    checkDxException(hr, D3D_OK, "SetFloat(_h_far_rate) ‚ÉŽ¸”s‚µ‚Ü‚µ‚½B");
    hr = pID3DXEffect->SetFloat(_pRegularPolygonSpriteEffect->_h_sin_rz, sin_rz);
    checkDxException(hr, D3D_OK, "SetFloat(_h_sin_rz) ‚ÉŽ¸”s‚µ‚Ü‚µ‚½B");
    hr = pID3DXEffect->SetFloat(_pRegularPolygonSpriteEffect->_h_cos_rz, cos_rz);
    checkDxException(hr, D3D_OK, "SetFloat(_h_cos_rz) ‚ÉŽ¸”s‚µ‚Ü‚µ‚½B");
    //¡‰ñ•`‰æ‚ÌUV
    float u,v;
    _pUvFlipper->getUV(u,v);
    hr = pID3DXEffect->SetFloat(_pRegularPolygonSpriteEffect->_h_offset_u, u);
    checkDxException(hr, D3D_OK, "SetFloat(_h_offset_u) ‚ÉŽ¸”s‚µ‚Ü‚µ‚½B");
    hr = pID3DXEffect->SetFloat(_pRegularPolygonSpriteEffect->_h_offset_v, v);
    checkDxException(hr, D3D_OK, "SetFloat(_h_offset_v) ‚ÉŽ¸”s‚µ‚Ü‚µ‚½B");
    _pRegularPolygonSpriteModel->GgafDxRegularPolygonSpriteModel::draw(this);
}

//void GgafDxRegularPolygonSpriteActor::setAlign(GgafDxAlign prm_align, GgafDxValign prm_valign) {
//    _align = prm_align;
//    _valign = prm_valign;
//}
//
//void GgafDxRegularPolygonSpriteActor::setAlign(GgafDxAlign prm_align) {
//    _align = prm_align;
//}
//
//void GgafDxRegularPolygonSpriteActor::setValign(GgafDxValign prm_valign) {
//    _valign = prm_valign;
//}

GgafDxRegularPolygonSpriteActor::~GgafDxRegularPolygonSpriteActor() {
    delete _pUvFlipper;
}
