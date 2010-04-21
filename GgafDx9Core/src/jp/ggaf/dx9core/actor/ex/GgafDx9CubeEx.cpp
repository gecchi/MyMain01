#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;

GgafDx9CubeEx::GgafDx9CubeEx(const char* prm_name) : GgafDx9CubeActor(prm_name, NULL) {
    _actor_class |= Obj_GgafDx9CubeEx;
    _class_name = "GgafDx9CubeEx";
}


GgafDx9CubeEx::~GgafDx9CubeEx() {
}
