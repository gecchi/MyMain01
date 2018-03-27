#include "jp/ggaf/lib/actor/DefaultMeshActor.h"

#include "jp/ggaf/lib/util/StgUtil.h"
#include "jp/ggaf/lib/util/CollisionChecker.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;

DefaultMeshActor::DefaultMeshActor(const char* prm_name,
                                   const char* prm_model,
                                   GgafStatus* prm_pStat) :
    GgafDxMeshActor(prm_name,
                     prm_model,
                     "DefaultMeshEffect",
                     "DefaultMeshTechnique",
                     prm_pStat,
                     UTIL::createChecker(this) ) {
    _class_name = "DefaultMeshActor";
    _pColliChecker = (CollisionChecker*)_pChecker;
}

void DefaultMeshActor::drawHitArea() {
#ifdef MY_DEBUG
    CollisionChecker::drawHitArea(_pColliChecker);
#endif
}

DefaultMeshActor::~DefaultMeshActor() {
    GGAF_DELETE(_pColliChecker);
}
