#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;

CubeMapMeshActor::CubeMapMeshActor(const char* prm_name, const char* prm_model) :
    GgafDx9CubeMapMeshActor(prm_name,
                     prm_model,
                     "CubeMapMeshEffect",
                     "CubeMapMeshTechnique",
                     NEW CollisionChecker(this) ) {

    _class_name = "CubeMapMeshActor";
    _offset_frames = 0;
    _pCollisionChecker = (CollisionChecker*)_pChecker;
    _pScaler = NEW GgafDx9Scaler(this);
}

void CubeMapMeshActor::drawHitArea() {
    ColliAABActor::get()->drawHitarea(_pCollisionChecker); ColliAAPrismActor::get()->drawHitarea(_pCollisionChecker); ColliSphereActor::get()->drawHitarea(_pCollisionChecker);
}

CubeMapMeshActor::~CubeMapMeshActor() {
    DELETE_IMPOSSIBLE_NULL(_pCollisionChecker);
    DELETE_IMPOSSIBLE_NULL(_pScaler);
}
