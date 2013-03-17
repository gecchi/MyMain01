#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;

DefaultD3DXMeshActor::DefaultD3DXMeshActor(const char* prm_name, const char* prm_model, GgafStatus* prm_pStat) :
    GgafDxD3DXMeshActor(prm_name,
                         prm_model,
                         "DefaultMeshEffect",
                         "DefaultMeshTechnique",
                         prm_pStat,
                         NEW CollisionChecker3D(this) ) {
    _class_name = "DefaultD3DXMeshActor";
    _pColliChecker = (CollisionChecker3D*)_pChecker;
    _pScaler = NEW GgafDxScaler(this);
}

void DefaultD3DXMeshActor::drawHitArea() {
    ColliAABActor::get()->drawHitarea(_pColliChecker); ColliAAPrismActor::get()->drawHitarea(_pColliChecker); ColliSphereActor::get()->drawHitarea(_pColliChecker);
}

DefaultD3DXMeshActor::~DefaultD3DXMeshActor() {
    GGAF_DELETE(_pColliChecker);
    GGAF_DELETE(_pScaler);
}
