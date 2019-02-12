#include "jp/ggaf/dx/actor/BaseActor.h"


using namespace GgafDx;

BaseActor::BaseActor(const char* prm_name, GgafCore::Status* prm_pStat) : GgafCore::MainActor(prm_name, prm_pStat) {
    _obj_class |= Obj_GgafDx_BaseActor;
    _class_name = "BaseActor";
}

BaseActor::~BaseActor() {
}
