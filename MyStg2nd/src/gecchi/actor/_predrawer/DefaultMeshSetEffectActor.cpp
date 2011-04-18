#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;


DefaultMeshSetEffectActor::DefaultMeshSetEffectActor(const char* prm_name) : DefaultMeshSetActor(prm_name, "_chk_DefaultMeshEffectTest") {
    _class_name = "DefaultMeshSetEffectActor";
    setHitAble(false);
}

DefaultMeshSetEffectActor::~DefaultMeshSetEffectActor() {
}

