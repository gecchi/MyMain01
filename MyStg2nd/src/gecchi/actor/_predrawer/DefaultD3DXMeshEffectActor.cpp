#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;


DefaultD3DXMeshEffectActor::DefaultD3DXMeshEffectActor(const char* prm_name) : DefaultD3DXMeshActor(prm_name, "DefaultD3DXMeshEffectTest") {
    _class_name = "DefaultD3DXMeshEffectActor";
    setHitAble(false);
}

DefaultD3DXMeshEffectActor::~DefaultD3DXMeshEffectActor() {
}

