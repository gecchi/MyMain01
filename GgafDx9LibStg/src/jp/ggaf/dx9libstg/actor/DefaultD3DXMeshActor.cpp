#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;

DefaultD3DXMeshActor::DefaultD3DXMeshActor(const char* prm_name, const char* prm_model) :
    GgafDx9D3DXMeshActor(prm_name,
                         prm_model,
                         "DefaultMeshEffect",
                         "DefaultMeshTechnique",
                         NEW CollisionChecker(this) ) {
    _class_name = "DefaultD3DXMeshActor";
    _frame_offset = 0;
    _pCollisionChecker = (CollisionChecker*)_pChecker;
    _pScaler = NEW GgafDx9Scaler(this);

}

void DefaultD3DXMeshActor::drawHitArea() {
    ColliAABActor::get()->drawHitarea(_pCollisionChecker); ColliAAPrismActor::get()->drawHitarea(_pCollisionChecker); ColliSphereActor::get()->drawHitarea(_pCollisionChecker);
}

DefaultD3DXMeshActor::~DefaultD3DXMeshActor() {
    DELETE_IMPOSSIBLE_NULL(_pCollisionChecker);
    DELETE_IMPOSSIBLE_NULL(_pScaler);
}
