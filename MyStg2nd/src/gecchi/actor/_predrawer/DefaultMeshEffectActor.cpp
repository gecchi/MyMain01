#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;


DefaultMeshEffectActor::DefaultMeshEffectActor(const char* prm_name) : DefaultMeshActor(prm_name, "DefaultMeshEffect") {
    _class_name = "DefaultMeshEffectActor";
    setHitAble(false);
}

DefaultMeshEffectActor::~DefaultMeshEffectActor() {
}

