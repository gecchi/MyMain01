#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;

GgafDx9BaseActor::GgafDx9BaseActor(const char* prm_name) : GgafMainActor(prm_name) {
    _obj_class |= Obj_GgafDx9BaseActor;
    _class_name = "GgafDx9BaseActor";
}

GgafDx9BaseActor::~GgafDx9BaseActor() {
}
