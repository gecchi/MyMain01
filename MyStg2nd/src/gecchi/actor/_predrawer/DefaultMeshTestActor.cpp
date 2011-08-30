#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;


DefaultMeshTestActor::DefaultMeshTestActor(const char* prm_name) :
        DefaultMeshActor(prm_name, "_chk_DefaultMeshEffectTest", NULL) {
    _class_name = "DefaultMeshTestActor";
    setHitAble(false);
}

DefaultMeshTestActor::~DefaultMeshTestActor() {
}

