#include "stdafx.h"
using namespace std;

using namespace GgafCore;

GgafUniverse::GgafUniverse(const char* prm_name) : GgafMainScene(prm_name) {
    _scene_class |= Obj_GgafUniverse;
    _class_name = "GgafUniverse";
}

GgafUniverse::~GgafUniverse() {
}
