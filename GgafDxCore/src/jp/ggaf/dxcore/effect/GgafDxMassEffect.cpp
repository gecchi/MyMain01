#include "jp/ggaf/dxcore/effect/GgafDxMassEffect.h"

#include "jp/ggaf/dxcore/GgafDxGod.h"
#include "jp/ggaf/dxcore/exception/GgafDxCriticalException.h"
#include "jp/ggaf/dxcore/scene/GgafDxSpacetime.h"

using namespace GgafCore;
using namespace GgafDxCore;

GgafDxMassEffect::GgafDxMassEffect(const char* prm_effect_name) : GgafDxEffect(prm_effect_name) {
    _obj_effect |= Obj_GgafDxMassEffect;
}

GgafDxMassEffect::~GgafDxMassEffect() {
}

