#include "jp/ggaf/lib/actor/DefaultMeshSetActor.h"

#include "jp/ggaf/lib/util/StgUtil.h"
#include "jp/ggaf/lib/util/CollisionChecker.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;

DefaultMeshSetActor::DefaultMeshSetActor(const char* prm_name, const char* prm_model, GgafStatus* prm_pStat) :
    GgafDxMeshSetActor(prm_name,
                       prm_model,
                       "DefaultMeshSetEffect",
                       "DefaultMeshSetTechnique",
                       prm_pStat,
                       UTIL::createChecker(this) ) {
    _class_name = "DefaultMeshSetActor";
    _pColliChecker = (CollisionChecker*)_pChecker;
}

void DefaultMeshSetActor::drawHitArea() {
#ifdef MY_DEBUG
    CollisionChecker::drawHitArea(_pColliChecker);
#endif
}

DefaultMeshSetActor::~DefaultMeshSetActor() {
    GGAF_DELETE(_pColliChecker);
}
