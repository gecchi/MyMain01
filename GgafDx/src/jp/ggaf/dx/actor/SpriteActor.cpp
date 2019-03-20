#include "jp/ggaf/dx/actor/SpriteActor.h"

#include "jp/ggaf/dx/exception/CriticalException.h"
#include "jp/ggaf/dx/God.h"
#include "jp/ggaf/dx/util/Util.h"
#include "jp/ggaf/dx/effect/SpriteEffect.h"
#include "jp/ggaf/dx/model/SpriteModel.h"
#include "jp/ggaf/dx/manager/TextureConnection.h"
#include "jp/ggaf/dx/actor/supporter/UvFlipper.h"


using namespace GgafDx;

SpriteActor::SpriteActor(const char* prm_name,
                         const char* prm_model_id,
                         const char* prm_effect_id,
                         const char* prm_technique,
                         Checker* prm_pChecker) :

                             FigureActor(prm_name,
                                         prm_model_id,
                                         TYPE_SPRITE_MODEL,
                                         prm_effect_id,
                                         TYPE_SPRITE_EFFECT,
                                         prm_technique,
                                         prm_pChecker),
_pSpriteModel( (SpriteModel*)_pModel),
_pSpriteEffect( (SpriteEffect*)_pEffect),
_pUvFlipper(NEW UvFlipper(getModel()->getDefaultTextureConnection()->peek())) {

    _obj_class |= Obj_GgafDx_SpriteActor;
    _class_name = "SpriteActor";
    _pUvFlipper->locatePatternNo(_pSpriteModel->_col_texture_split,
                             _pSpriteModel->_row_texture_split );
    _pUvFlipper->setActivePtn(0);
    _pUvFlipper->exec(NOT_ANIMATED, 1);

    defineRotMvWorldMatrix(UTIL::setWorldMatrix_RxRzRyMv); //ƒfƒtƒHƒ‹ƒg‚Ì‰ñ“]~ˆÚ“®‚Ì•ÏŠ·s—ñ
    _far_rate = -1.0f;

    _align = ALIGN_CENTER;
    _valign = VALIGN_MIDDLE;
}

void SpriteActor::processDraw() {
    ID3DXEffect* const pID3DXEffect = _pSpriteEffect->_pID3DXEffect;
    HRESULT hr;
//    if (_align == ALIGN_CENTER) {
//        //do nothing
//    } else if (_align == ALIGN_LEFT) {
//        _matWorld._41 += PX_DX(_pSpriteModel->_model_width_px/2);
//    } else {
//        //ALIGN_RIGHT
//        _matWorld._41 -= PX_DX(_pSpriteModel->_model_width_px/2);
//    }
//    if (_valign == VALIGN_MIDDLE) {
//        //do nothing
//    } else if (_valign == VALIGN_TOP) {
//        _matWorld._42 -= PX_DX(_pSpriteModel->_model_height_px/2);
//    } else {
//        //VALIGN_BOTTOM
//        _matWorld._42 += PX_DX(_pSpriteModel->_model_height_px/2);
//    }
    hr = pID3DXEffect->SetMatrix(_pSpriteEffect->_h_matWorld, &_matWorld );
    checkDxException(hr, D3D_OK, "SetMatrix(_h_matWorld) ‚ÉŽ¸”s‚µ‚Ü‚µ‚½B");
    hr = pID3DXEffect->SetValue(_pSpriteEffect->_h_colMaterialDiffuse, &(_paMaterial[0].Diffuse), sizeof(D3DCOLORVALUE) );
    checkDxException(hr, D3D_OK, "SetValue(_h_colMaterialDiffuse) ‚ÉŽ¸”s‚µ‚Ü‚µ‚½B");
    hr = pID3DXEffect->SetFloat(_pSpriteEffect->_h_far_rate, _far_rate );
    checkDxException(hr, D3D_OK, "SetFloat(_h_far_rate) ‚ÉŽ¸”s‚µ‚Ü‚µ‚½B");
    _pSpriteModel->SpriteModel::draw(this);
}

//void SpriteActor::setAlign(Align prm_align, Valign prm_valign) {
//    _align = prm_align;
//    _valign = prm_valign;
//}
//
//void SpriteActor::setAlign(Align prm_align) {
//    _align = prm_align;
//}
//
//void SpriteActor::setValign(Valign prm_valign) {
//    _valign = prm_valign;
//}

SpriteActor::~SpriteActor() {
    delete _pUvFlipper;
}
