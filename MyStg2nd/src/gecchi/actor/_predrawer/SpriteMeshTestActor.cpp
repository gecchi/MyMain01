#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;


SpriteMeshTestActor::SpriteMeshTestActor(const char* prm_name) : SpriteMeshActor(prm_name, "_chk_SpriteMeshEffectTest") {
    _class_name = "SpriteMeshTestActor";
    setHitAble(false);
}

SpriteMeshTestActor::~SpriteMeshTestActor() {
}

