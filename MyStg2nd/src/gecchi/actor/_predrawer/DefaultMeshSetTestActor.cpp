#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;


DefaultMeshSetTestActor::DefaultMeshSetTestActor(const char* prm_name) : DefaultMeshSetActor(prm_name, "_chk_DefaultMeshEffectTest") {
    _class_name = "DefaultMeshSetTestActor";
    setHitAble(false);
}

DefaultMeshSetTestActor::~DefaultMeshSetTestActor() {
}

