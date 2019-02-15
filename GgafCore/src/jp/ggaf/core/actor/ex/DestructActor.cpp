#include "jp/ggaf/core/actor/ex/DestructActor.h"

using namespace GgafCore;

DestructActor::DestructActor(const char* prm_name) : MainActor(prm_name) {
    _obj_class |= Obj_ggaf_DestructActor;
    _class_name = "DestructActor";
    setHitAble(false);
}

DestructActor::~DestructActor() {
}
