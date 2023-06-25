#include "jp/ggaf/dx/effect/MassSpriteEffect.h"

#include "jp/ggaf/dx/Caretaker.h"
#include "jp/ggaf/dx/exception/CriticalException.h"
#include "jp/ggaf/dx/scene/Spacetime.h"

using namespace GgafDx;

MassSpriteEffect::MassSpriteEffect(const char* prm_effect_name) : World3DimEffect(prm_effect_name), IPlaneEffect(this) {
    _obj_class |= Obj_GgafDx_MassSpriteEffect;
    _obj_class |= Obj_GgafDx_IPlaneEffect;

    Camera* const pCam = pCARETAKER->getSpacetime()->getCamera();
}

MassSpriteEffect::~MassSpriteEffect() {
}

