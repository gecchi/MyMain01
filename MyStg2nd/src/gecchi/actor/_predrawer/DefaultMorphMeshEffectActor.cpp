#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;


DefaultMorphMeshEffectActor::DefaultMorphMeshEffectActor(const char* prm_name) : DefaultMorphMeshActor(prm_name, "_chk_DefaultMorphMeshEffectTest") {
    _class_name = "DefaultMorphMeshEffectActor";
    setHitAble(false);
}

DefaultMorphMeshEffectActor::~DefaultMorphMeshEffectActor() {
}

