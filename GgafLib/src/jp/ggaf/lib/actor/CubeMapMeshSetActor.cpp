#include "jp/ggaf/lib/actor/CubeMapMeshSetActor.h"

#include "jp/ggaf/lib/util/StgUtil.h"
#include "jp/ggaf/lib/util/CollisionChecker.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;

CubeMapMeshSetActor::CubeMapMeshSetActor(const char* prm_name, const char* prm_model, GgafStatus* prm_pStat) :
    GgafDxCubeMapMeshSetActor(prm_name,
                              prm_model,
                              "CubeMapMeshSetEffect",
                              "CubeMapMeshSetTechnique",
                              prm_pStat,
                              UTIL::createChecker(this) ) {
    _class_name = "CubeMapMeshSetActor";
    _pColliChecker = (CollisionChecker*)_pChecker;
}

void CubeMapMeshSetActor::drawHitArea() {
#ifdef MY_DEBUG
    CollisionChecker::drawHitArea(_pColliChecker);
#endif
}

CubeMapMeshSetActor::~CubeMapMeshSetActor() {
    GGAF_DELETE(_pColliChecker);
}
