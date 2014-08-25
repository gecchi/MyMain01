#include "jp/ggaf/core/actor/ex/GgafDummyActor.h"

using namespace GgafCore;

GgafDummyActor::GgafDummyActor(const char* prm_name, GgafStatus* prm_pStat) : GgafMainActor(prm_name, prm_pStat) {
    _obj_class |= Obj_GgafDummyActor;
    _class_name = "GgafDummyActor";
    setHitAble(false);
}

GgafDummyActor::~GgafDummyActor() {
}
