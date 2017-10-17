#include "jp/ggaf/lib/actor/DefaultD3DXMeshActor.h"

#include "jp/ggaf/lib/util/StgUtil.h"
#include "jp/ggaf/lib/util/CollisionChecker.h"
#ifdef MY_DEBUG
#include "jp/ggaf/lib/actor/ColliAABoxActor.h"
#include "jp/ggaf/lib/actor/ColliAAPrismActor.h"
#include "jp/ggaf/lib/actor/ColliAAPyramidActor.h"
#include "jp/ggaf/lib/actor/ColliSphereActor.h"
#endif


using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;

DefaultD3DXMeshActor::DefaultD3DXMeshActor(const char* prm_name, const char* prm_model, GgafStatus* prm_pStat) :
    GgafDxD3DXMeshActor(prm_name,
                        prm_model,
                        "DefaultMeshEffect",
                        "DefaultMeshTechnique",
                        prm_pStat,
                        UTIL::createChecker(this) ) {
    _class_name = "DefaultD3DXMeshActor";
    _pColliChecker = (CollisionChecker*)_pChecker;
}

void DefaultD3DXMeshActor::drawHitArea() {
#ifdef MY_DEBUG
    ColliAABoxActor::get()->drawHitarea(_pColliChecker); ColliAAPrismActor::get()->drawHitarea(_pColliChecker); ColliAAPyramidActor::get()->drawHitarea(_pColliChecker); ColliSphereActor::get()->drawHitarea(_pColliChecker);
#endif
}

DefaultD3DXMeshActor::~DefaultD3DXMeshActor() {
    GGAF_DELETE(_pColliChecker);
}
