#include "stdafx.h"
#include "jp/ggaf/lib/actor/DefaultD3DXMeshActor.h"

#include "jp/ggaf/lib/util/CollisionChecker3D.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxScaler.h"
#include "jp/ggaf/lib/actor/ColliAABActor.h"
#include "jp/ggaf/lib/actor/ColliAAPrismActor.h"
#include "jp/ggaf/lib/actor/ColliSphereActor.h"

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
}

void DefaultD3DXMeshActor::drawHitArea() {
    ColliAABActor::get()->drawHitarea(_pColliChecker); ColliAAPrismActor::get()->drawHitarea(_pColliChecker); ColliSphereActor::get()->drawHitarea(_pColliChecker);
}

DefaultD3DXMeshActor::~DefaultD3DXMeshActor() {
    GGAF_DELETE(_pColliChecker);
}
