#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;


SpriteMeshEffectActor::SpriteMeshEffectActor(const char* prm_name) : SpriteMeshActor(prm_name, "SpriteMeshEffectTest") {
    _class_name = "SpriteMeshEffectActor";
    setHitAble(false);
}

SpriteMeshEffectActor::~SpriteMeshEffectActor() {
}

