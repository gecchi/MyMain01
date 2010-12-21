#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;

DefaultCubeMapMeshActor::DefaultCubeMapMeshActor(const char* prm_name, const char* prm_model) :
    GgafDx9CubeMapMeshActor(prm_name,
                     prm_model,
                     "CubeMapMeshEffect",
                     "CubeMapMeshTechnique",
                     NEW CollisionChecker(this) ) {

    _class_name = "DefaultCubeMapMeshActor";
    _frame_offset = 0;
    _pCollisionChecker = (CollisionChecker*)_pChecker;
    _pScaler = NEW GgafDx9GeometricScaler(this);
}

void DefaultCubeMapMeshActor::drawHitArea() {
    CubeEx::get()->drawHitarea(_pCollisionChecker); SphereEx::get()->drawHitarea(_pCollisionChecker);
}

DefaultCubeMapMeshActor::~DefaultCubeMapMeshActor() {
    DELETE_IMPOSSIBLE_NULL(_pCollisionChecker);
    DELETE_IMPOSSIBLE_NULL(_pScaler);
}
