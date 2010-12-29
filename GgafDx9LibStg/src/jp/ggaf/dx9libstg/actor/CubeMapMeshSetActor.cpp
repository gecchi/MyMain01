#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;

CubeMapMeshSetActor::CubeMapMeshSetActor(const char* prm_name, const char* prm_model) :
    GgafDx9CubeMapMeshSetActor(prm_name,
                        prm_model,
                        "CubeMapMeshSetEffect",
                        "CubeMapMeshSetTechnique",
                        NEW CollisionChecker(this) ) {

    _class_name = "CubeMapMeshSetActor";
    _frame_offset = 0;
    _pCollisionChecker = (CollisionChecker*)_pChecker;
    _pScaler = NEW GgafDx9GeometricScaler(this);
}

void CubeMapMeshSetActor::drawHitArea() {
    ColliAABActor::get()->drawHitarea(_pCollisionChecker); ColliSphereActor::get()->drawHitarea(_pCollisionChecker);
}

CubeMapMeshSetActor::~CubeMapMeshSetActor() {
    DELETE_IMPOSSIBLE_NULL(_pCollisionChecker);
    DELETE_IMPOSSIBLE_NULL(_pScaler);
}
