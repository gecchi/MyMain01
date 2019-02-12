#include "jp/ggaf/dx/effect/ex/WorldBoundEffect.h"


using namespace GgafDx;

WorldBoundEffect::WorldBoundEffect(const char* prm_effect_name) : MorphMeshEffect(prm_effect_name) {
    _obj_effect |= Obj_GgafDx_WorldBoundEffect;
}

WorldBoundEffect::~WorldBoundEffect() {
}

