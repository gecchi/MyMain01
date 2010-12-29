#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;

DefaultD3DXAniMeshActor::DefaultD3DXAniMeshActor(const char* prm_name, const char* prm_model) :
    GgafDx9D3DXAniMeshActor(prm_name,
                         prm_model,
                         "DefaultAniMeshEffect",
                         "DefaultAniMeshTechnique",
                         NEW CollisionChecker(this) ) {
    _class_name = "DefaultD3DXAniMeshActor";
    _frame_offset = 0;
    _pCollisionChecker = (CollisionChecker*)_pChecker;
    _pScaler = NEW GgafDx9GeometricScaler(this);

}

void DefaultD3DXAniMeshActor::drawHitArea() {
    ColliAABActor::get()->drawHitarea(_pCollisionChecker);
    ColliSphereActor::get()->drawHitarea(_pCollisionChecker);
}

DefaultD3DXAniMeshActor::~DefaultD3DXAniMeshActor() {
    DELETE_IMPOSSIBLE_NULL(_pCollisionChecker);
    DELETE_IMPOSSIBLE_NULL(_pScaler);
}
