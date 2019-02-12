#include "jp/ggaf/core/actor/ex/DestructActor.h"

using namespace GgafCore;

DestructActor::DestructActor(const char* prm_name, Status* prm_pStat) : MainActor(prm_name, prm_pStat) {
    _obj_class |= Obj_ggaf_DestructActor;
    _class_name = "DestructActor";
    setHitAble(false);
}

DestructActor::~DestructActor() {
}
