#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;


SpriteMeshSetEffectActor::SpriteMeshSetEffectActor(const char* prm_name) : SpriteMeshSetActor(prm_name, "_chk_DefaultMeshSetEffectTest") {
    _class_name = "DefaultMeshSetEffectActor";
    setHitAble(false);
}

SpriteMeshSetEffectActor::~SpriteMeshSetEffectActor() {
}

