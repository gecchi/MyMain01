#include "jp/ggaf/dx/actor/BaseActor.h"

using namespace GgafDx;

BaseActor::BaseActor(const char* prm_name) : GgafCore::MainActor(prm_name) {
    _obj_class |= Obj_GgafDx_BaseActor;
    _class_name = "BaseActor";
}

BaseActor::~BaseActor() {
}
