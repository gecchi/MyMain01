#include "jp/ggaf/dxcore/effect/ex/GgafDxWorldBoundEffect.h"

using namespace GgafCore;
using namespace GgafDxCore;

GgafDxWorldBoundEffect::GgafDxWorldBoundEffect(const char* prm_effect_name) : GgafDxMorphMeshEffect(prm_effect_name) {
    _obj_effect |= Obj_GgafDxWorldBoundEffect;
}

GgafDxWorldBoundEffect::~GgafDxWorldBoundEffect() {
}

