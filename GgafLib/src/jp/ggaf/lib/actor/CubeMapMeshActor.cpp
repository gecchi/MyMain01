#include "jp/ggaf/lib/actor/CubeMapMeshActor.h"

#include "jp/ggaf/lib/util/StgUtil.h"
#include "jp/ggaf/lib/util/WorldCollisionChecker.h"



using namespace GgafLib;

CubeMapMeshActor::CubeMapMeshActor(const char* prm_name, const char* prm_model) :
    GgafDx::CubeMapMeshActor(prm_name,
                             prm_model,
                             "CubeMapMeshEffect",
                             "CubeMapMeshTechnique") {
    _class_name = "CubeMapMeshActor";
    _pWorldCollisionChecker = (WorldCollisionChecker*)getChecker();
}

void CubeMapMeshActor::drawHitArea() {
#ifdef MY_DEBUG
    WorldCollisionChecker::drawHitArea(_pWorldCollisionChecker);
#endif
}
GgafDx::CollisionChecker* CubeMapMeshActor::createChecker(kind_t prm_kind) {
    return UTIL::createCollisionChecker(this, prm_kind);
}

CubeMapMeshActor::~CubeMapMeshActor() {
}
