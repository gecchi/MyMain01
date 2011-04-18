#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;


CubeMapMeshSetEffectActor::CubeMapMeshSetEffectActor(const char* prm_name) : CubeMapMeshSetActor(prm_name, "CubeMapMeshSetEffectTest") {
    _class_name = "CubeMapMeshSetEffectActor";
    setHitAble(false);
}

CubeMapMeshSetEffectActor::~CubeMapMeshSetEffectActor() {
}

