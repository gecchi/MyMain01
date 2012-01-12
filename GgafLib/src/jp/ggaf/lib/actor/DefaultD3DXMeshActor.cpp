#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;

DefaultD3DXMeshActor::DefaultD3DXMeshActor(const char* prm_name, const char* prm_model, GgafStatus* prm_pStat) :
    GgafDxD3DXMeshActor(prm_name,
                         prm_model,
                         "DefaultMeshEffect",
                         "DefaultMeshTechnique",
                         prm_pStat,
                         NEW CollisionChecker(this) ) {
    _class_name = "DefaultD3DXMeshActor";
    _pCollisionChecker = (CollisionChecker*)_pChecker;
    _pScaler = NEW GgafDxScaler(this);
}

void DefaultD3DXMeshActor::drawHitArea() {
    ColliAABActor::get()->drawHitarea(_pCollisionChecker); ColliAAPrismActor::get()->drawHitarea(_pCollisionChecker); ColliSphereActor::get()->drawHitarea(_pCollisionChecker);
}

DefaultD3DXMeshActor::~DefaultD3DXMeshActor() {
    DELETE_IMPOSSIBLE_NULL(_pCollisionChecker);
    DELETE_IMPOSSIBLE_NULL(_pScaler);
}
