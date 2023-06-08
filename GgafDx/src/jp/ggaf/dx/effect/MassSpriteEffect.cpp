#include "jp/ggaf/dx/effect/MassSpriteEffect.h"

#include "jp/ggaf/dx/Caretaker.h"
#include "jp/ggaf/dx/exception/CriticalException.h"
#include "jp/ggaf/dx/scene/Spacetime.h"

using namespace GgafDx;

MassSpriteEffect::MassSpriteEffect(const char* prm_effect_name) : World3DimEffect(prm_effect_name), IPlaneEffect(this) {
    _obj_class |= Obj_GgafDx_MassSpriteEffect;
    _obj_class |= Obj_GgafDx_IPlaneEffect;

    Camera* const pCam = pCARETAKER->getSpacetime()->getCamera();
    //シェーダー共通のグローバル変数設定
    _h_tex_blink_power = _pID3DXEffect->GetParameterByName( nullptr, "g_tex_blink_power" );
    _h_tex_blink_threshold = _pID3DXEffect->GetParameterByName( nullptr, "g_tex_blink_threshold" );
}

MassSpriteEffect::~MassSpriteEffect() {
}

