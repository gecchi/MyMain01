#include "jp/ggaf/lib/actor/DefaultD3DXAniMeshActor.h"

#include "jp/ggaf/lib/util/StgUtil.h"
#include "jp/ggaf/lib/util/CollisionChecker.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;

DefaultD3DXAniMeshActor::DefaultD3DXAniMeshActor(const char* prm_name, const char* prm_model, GgafStatus* prm_pStat) :
    GgafDxD3DXAniMeshActor(prm_name,
                           prm_model,
                           "DefaultD3DXAniMeshEffect",
                           "DefaultD3DXAniMeshTechnique",
                           prm_pStat,
                           UTIL::createChecker(this) ) {
    _class_name = "DefaultD3DXAniMeshActor";
    _pColliChecker = (CollisionChecker*)_pChecker;
}

void DefaultD3DXAniMeshActor::drawHitArea() {
#ifdef MY_DEBUG
    CollisionChecker::drawHitArea(_pColliChecker);
#endif
}

DefaultD3DXAniMeshActor::~DefaultD3DXAniMeshActor() {
    GGAF_DELETE(_pColliChecker);
}
