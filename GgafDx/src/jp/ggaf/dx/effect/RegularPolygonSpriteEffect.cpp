#include "jp/ggaf/dx/effect/RegularPolygonSpriteEffect.h"

#include "jp/ggaf/dx/Caretaker.h"
#include "jp/ggaf/dx/exception/CriticalException.h"
#include "jp/ggaf/dx/scene/Spacetime.h"


using namespace GgafDx;

RegularPolygonSpriteEffect::RegularPolygonSpriteEffect(const char* prm_effect_name) : World3DimEffect(prm_effect_name), IPlaneEffect(this) {
    _obj_class |= Obj_GgafDx_RegularPolygonSpriteEffect;
    _obj_class |= Obj_GgafDx_IPlaneEffect;

    Camera* const pCam = pCARETAKER->getSpacetime()->getCamera();
    //シェーダー共通のグローバル変数設定
    HRESULT hr;
    _h_matWorld = _pID3DXEffect->GetParameterByName( nullptr, "g_matWorld" );
    _h_offset_u = _pID3DXEffect->GetParameterByName( nullptr, "g_offset_u" );
    _h_offset_v = _pID3DXEffect->GetParameterByName( nullptr, "g_offset_v" );
    _h_colMaterialDiffuse = _pID3DXEffect->GetParameterByName( nullptr, "g_colMaterialDiffuse" );
    _h_tex_blink_power = _pID3DXEffect->GetParameterByName( nullptr, "g_tex_blink_power" );
    _h_tex_blink_threshold = _pID3DXEffect->GetParameterByName( nullptr, "g_tex_blink_threshold" );
    _h_sin_rz = _pID3DXEffect->GetParameterByName( nullptr, "g_sin_rz" );
    _h_cos_rz = _pID3DXEffect->GetParameterByName( nullptr, "g_cos_rz" );
    _h_u_center = _pID3DXEffect->GetParameterByName( nullptr, "g_u_center" );
    _h_v_center = _pID3DXEffect->GetParameterByName( nullptr, "g_v_center" );
}

RegularPolygonSpriteEffect::~RegularPolygonSpriteEffect() {
}

