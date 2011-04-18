#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;


DefaultD3DXAniMeshEffectActor::DefaultD3DXAniMeshEffectActor(const char* prm_name) : DefaultD3DXAniMeshActor(prm_name, "DefaultD3DXAniMeshEffectTest") {
    _class_name = "DefaultD3DXAniMeshEffectActor";
    setHitAble(false);
}

DefaultD3DXAniMeshEffectActor::~DefaultD3DXAniMeshEffectActor() {
}

