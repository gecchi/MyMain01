#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;


CubeMapMeshEffectActor::CubeMapMeshEffectActor(const char* prm_name) : CubeMapMeshActor(prm_name, "CubeMapMeshEffectTest") {
    _class_name = "CubeMapMeshEffectActor";
    setHitAble(false);
}

CubeMapMeshEffectActor::~CubeMapMeshEffectActor() {
}

