#include "jp/ggaf/lib/actor/CubeMapMeshActor.h"

#include "jp/ggaf/lib/util/StgUtil.h"
#include "jp/ggaf/lib/util/CollisionChecker.h"



using namespace GgafLib;

CubeMapMeshActor::CubeMapMeshActor(const char* prm_name, const char* prm_model, GgafCore::Status* prm_pStat) :
    GgafDx::CubeMapMeshActor(prm_name,
                           prm_model,
                           "CubeMapMeshEffect",
                           "CubeMapMeshTechnique",
                           prm_pStat,
                           UTIL::createChecker(this) ) {
    _class_name = "CubeMapMeshActor";
    _pColliChecker = (CollisionChecker*)_pChecker;
}

void CubeMapMeshActor::drawHitArea() {
#ifdef MY_DEBUG
    CollisionChecker::drawHitArea(_pColliChecker);
#endif
}

CubeMapMeshActor::~CubeMapMeshActor() {
    GGAF_DELETE(_pColliChecker);
}
