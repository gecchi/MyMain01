#include "jp/ggaf/lib/actor/DefaultDynaD3DXMeshActor.h"

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

DefaultDynaD3DXMeshActor::DefaultDynaD3DXMeshActor(const char* prm_name, const char* prm_model, GgafStatus* prm_pStat) :
    GgafDxDynaD3DXMeshActor(prm_name,
                             prm_model,
                             "DefaultMeshEffect",
                             "DefaultMeshTechnique",
                             prm_pStat,
                             NEW CollisionChecker3D(this) ) {
    _class_name = "DefaultDynaD3DXMeshActor";
    _pColliChecker = (CollisionChecker3D*)_pChecker;
}

void DefaultDynaD3DXMeshActor::drawHitArea() {
#ifdef MY_DEBUG
    ColliAABoxActor::get()->drawHitarea(_pColliChecker); ColliAAPrismActor::get()->drawHitarea(_pColliChecker); ColliAAPyramidActor::get()->drawHitarea(_pColliChecker); ColliSphereActor::get()->drawHitarea(_pColliChecker);
#endif
}


DefaultDynaD3DXMeshActor::~DefaultDynaD3DXMeshActor() {
    GGAF_DELETE(_pColliChecker);
}
