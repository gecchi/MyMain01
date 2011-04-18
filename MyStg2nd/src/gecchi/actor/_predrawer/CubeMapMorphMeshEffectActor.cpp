#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;


CubeMapMorphMeshEffectActor::CubeMapMorphMeshEffectActor(const char* prm_name) : CubeMapMorphMeshActor(prm_name, "CubeMapMorphMeshEffectTest") {
    _class_name = "CubeMapMorphMeshEffectActor";
    setHitAble(false);
}

CubeMapMorphMeshEffectActor::~CubeMapMorphMeshEffectActor() {
}

