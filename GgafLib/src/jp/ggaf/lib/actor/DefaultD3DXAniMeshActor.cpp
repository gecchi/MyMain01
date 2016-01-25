#include "jp/ggaf/lib/actor/DefaultD3DXAniMeshActor.h"

#include "jp/ggaf/lib/util/CollisionChecker3D.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxScaler.h"

#ifdef MY_DEBUG
#include "jp/ggaf/lib/actor/ColliAABoxActor.h"
#include "jp/ggaf/lib/actor/ColliAAPrismActor.h"
#include "jp/ggaf/lib/actor/ColliAAPyramidActor.h"
#include "jp/ggaf/lib/actor/ColliSphereActor.h"
#endif

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;

DefaultD3DXAniMeshActor::DefaultD3DXAniMeshActor(const char* prm_name, const char* prm_model, GgafStatus* prm_pStat) :
    GgafDxD3DXAniMeshActor(prm_name,
                           prm_model,
                           "DefaultD3DXAniMeshEffect",
                           "DefaultD3DXAniMeshTechnique",
                           prm_pStat,
                           NEW CollisionChecker3D(this) ) {
    _class_name = "DefaultD3DXAniMeshActor";
    _pColliChecker = (CollisionChecker3D*)_pChecker;
}

void DefaultD3DXAniMeshActor::drawHitArea() {
#ifdef MY_DEBUG
    ColliAABoxActor::get()->drawHitarea(_pColliChecker); ColliAAPrismActor::get()->drawHitarea(_pColliChecker); ColliAAPyramidActor::get()->drawHitarea(_pColliChecker); ColliSphereActor::get()->drawHitarea(_pColliChecker);
#endif
}

DefaultD3DXAniMeshActor::~DefaultD3DXAniMeshActor() {
    GGAF_DELETE(_pColliChecker);
}
