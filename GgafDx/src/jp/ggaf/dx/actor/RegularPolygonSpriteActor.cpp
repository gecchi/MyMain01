#include "jp/ggaf/dx/actor/RegularPolygonSpriteActor.h"

#include "jp/ggaf/dx/exception/CriticalException.h"
#include "jp/ggaf/dx/Caretaker.h"
#include "jp/ggaf/dx/util/Util.h"
#include "jp/ggaf/dx/effect/RegularPolygonSpriteEffect.h"
#include "jp/ggaf/dx/model/RegularPolygonSpriteModel.h"
#include "jp/ggaf/dx/manager/TextureConnection.h"
#include "jp/ggaf/dx/actor/supporter/UvFlipper.h"


using namespace GgafDx;

RegularPolygonSpriteActor::RegularPolygonSpriteActor(const char* prm_name,
                                                     const char* prm_model,
                                                     const char* prm_effect_id,
                                                     const char* prm_technique,
                                                     CollisionChecker* prm_pChecker) :

                                                         FigureActor(prm_name,
                                                                     prm_model,
                                                                     TYPE_REGULARPOLYGONSPRITE_MODEL,
                                                                     prm_effect_id,
                                                                     TYPE_REGULARPOLYGONSPRITE_EFFECT,
                                                                     prm_technique,
                                                                     prm_pChecker),
_pRegularPolygonSpriteModel( (RegularPolygonSpriteModel*)_pModel),
_pRegularPolygonSpriteEffect( (RegularPolygonSpriteEffect*)_pEffect),
_pUvFlipper(NEW UvFlipper()) {

    _obj_class |= Obj_GgafDx_RegularPolygonSpriteActor;
    _class_name = "RegularPolygonSpriteActor";
    _pUvFlipper->locatePatternNo(_pRegularPolygonSpriteModel);

    defineRotMvWorldMatrix(UTIL::setWorldMatrix_RxRzRyMv); //ƒfƒtƒHƒ‹ƒg‚Ì‰ñ“]~ˆÚ“®‚Ì•ÏŠ·s—ñ
    _draw_fan_num = _pRegularPolygonSpriteModel->_angle_num;
    _cull_mode = _pRegularPolygonSpriteModel->_drawing_order == 1 ?  D3DCULL_CCW : D3DCULL_CW;
    _circumference_begin_position = 0;
}

void RegularPolygonSpriteActor::processDraw() {
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
    _pRegularPolygonSpriteModel->RegularPolygonSpriteModel::draw(this);
}

void RegularPolygonSpriteActor::changeModelByIndex(int prm_model_index) {
    FigureActor::changeModelByIndex(prm_model_index);
    _pRegularPolygonSpriteModel = (RegularPolygonSpriteModel*)_pModel;
}


RegularPolygonSpriteActor::~RegularPolygonSpriteActor() {
    delete _pUvFlipper;
}
