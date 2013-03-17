#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;

DefaultDynaD3DXMeshActor::DefaultDynaD3DXMeshActor(const char* prm_name, const char* prm_model, GgafStatus* prm_pStat) :
    GgafDxDynaD3DXMeshActor(prm_name,
                             prm_model,
                             "DefaultMeshEffect",
                             "DefaultMeshTechnique",
                             prm_pStat,
                             NEW CollisionChecker3D(this) ) {
    _class_name = "DefaultDynaD3DXMeshActor";
    _pScaler = NEW GgafDxScaler(this);
    _pColliChecker = (CollisionChecker3D*)_pChecker;
}

void DefaultDynaD3DXMeshActor::drawHitArea() {
    ColliAABActor::get()->drawHitarea(_pColliChecker); ColliAAPrismActor::get()->drawHitarea(_pColliChecker); ColliSphereActor::get()->drawHitarea(_pColliChecker);
}


DefaultDynaD3DXMeshActor::~DefaultDynaD3DXMeshActor() {
    GGAF_DELETE(_pColliChecker);
    GGAF_DELETE(_pScaler);
}
