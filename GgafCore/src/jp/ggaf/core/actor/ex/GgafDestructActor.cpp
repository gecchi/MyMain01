#include "jp/ggaf/core/actor/ex/GgafDestructActor.h"

using namespace GgafCore;

GgafDestructActor::GgafDestructActor(const char* prm_name, GgafStatus* prm_pStat) : GgafMainActor(prm_name, prm_pStat) {
    _obj_class |= Obj_GgafDestructActor;
    _class_name = "GgafDestructActor";
    setHitAble(false);
}

GgafDestructActor::~GgafDestructActor() {
}
