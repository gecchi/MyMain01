#include "stdafx.h"
using namespace std;

using namespace GgafCore;

GgafMainScene::GgafMainScene(const char* prm_name) : GgafScene(prm_name) {
    _obj_class |= Obj_GgafMainScene;
    _class_name = "GgafMainScene";
}

GgafMainScene::~GgafMainScene() {
}
