#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;

DefaultD3DXAniMeshActor::DefaultD3DXAniMeshActor(const char* prm_name, const char* prm_model, GgafStatus* prm_pStat) :
    GgafDxD3DXAniMeshActor(prm_name,
                            prm_model,
                            "DefaultD3DXAniMeshEffect",
                            "DefaultD3DXAniMeshTechnique",
                            prm_pStat,
                            NEW CollisionChecker(this) ) {
    _class_name = "DefaultD3DXAniMeshActor";
    _offset_frames = 0;
    _pCollisionChecker = (CollisionChecker*)_pChecker;
    _pScaler = NEW GgafDxScaler(this);

}

void DefaultD3DXAniMeshActor::drawHitArea() {
    ColliAABActor::get()->drawHitarea(_pCollisionChecker);
    ColliSphereActor::get()->drawHitarea(_pCollisionChecker);
}

DefaultD3DXAniMeshActor::~DefaultD3DXAniMeshActor() {
    DELETE_IMPOSSIBLE_NULL(_pCollisionChecker);
    DELETE_IMPOSSIBLE_NULL(_pScaler);
}
