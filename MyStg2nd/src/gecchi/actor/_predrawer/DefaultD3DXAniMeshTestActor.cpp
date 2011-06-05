#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;


DefaultD3DXAniMeshTestActor::DefaultD3DXAniMeshTestActor(const char* prm_name) : DefaultD3DXAniMeshActor(prm_name, "_chk_DefaultD3DXAniMeshEffectTest") {
    _class_name = "DefaultD3DXAniMeshTestActor";
    setHitAble(false);
}

DefaultD3DXAniMeshTestActor::~DefaultD3DXAniMeshTestActor() {
}

