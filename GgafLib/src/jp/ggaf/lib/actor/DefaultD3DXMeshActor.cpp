#include "jp/ggaf/lib/actor/DefaultD3DXMeshActor.h"

#include "jp/ggaf/lib/util/StgUtil.h"
#include "jp/ggaf/lib/util/CollisionChecker.h"

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
    CollisionChecker::drawHitArea(_pColliChecker);
#endif
}

DefaultD3DXMeshActor::~DefaultD3DXMeshActor() {
    GGAF_DELETE(_pColliChecker);
}
