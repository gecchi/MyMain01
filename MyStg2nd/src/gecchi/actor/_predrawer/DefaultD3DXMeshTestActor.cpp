#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;


DefaultD3DXMeshTestActor::DefaultD3DXMeshTestActor(const char* prm_name) : DefaultD3DXMeshActor(prm_name, "_chk_DefaultD3DXMeshEffectTest") {
    _class_name = "DefaultD3DXMeshTestActor";
    setHitAble(false);
}

DefaultD3DXMeshTestActor::~DefaultD3DXMeshTestActor() {
}

