#include "jp/ggaf/lib/actor/CubeMapMeshActor.h"

#include "jp/ggaf/lib/util/StgUtil.h"
#include "jp/ggaf/lib/util/WorldCollisionChecker.h"



using namespace GgafLib;

CubeMapMeshActor::CubeMapMeshActor(const char* prm_name, const char* prm_model) :
    GgafDx::CubeMapMeshActor(prm_name,
                           prm_model,
                           "CubeMapMeshEffect",
                           "CubeMapMeshTechnique",
                           UTIL::createCollisionChecker(this) ) {
    _class_name = "CubeMapMeshActor";
    _pColliCollisionChecker = (WorldCollisionChecker*)_pChecker;
}

void CubeMapMeshActor::drawHitArea() {
#ifdef MY_DEBUG
    WorldCollisionChecker::drawHitArea(_pColliCollisionChecker);
#endif
}

CubeMapMeshActor::~CubeMapMeshActor() {
    GGAF_DELETE(_pColliCollisionChecker);
}
