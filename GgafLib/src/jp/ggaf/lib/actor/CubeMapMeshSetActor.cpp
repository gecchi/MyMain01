#include "jp/ggaf/lib/actor/CubeMapMeshSetActor.h"

#include "jp/ggaf/lib/util/StgUtil.h"
#include "jp/ggaf/lib/util/WorldCollisionChecker.h"



using namespace GgafLib;

CubeMapMeshSetActor::CubeMapMeshSetActor(const char* prm_name, const char* prm_model) :
    GgafDx::CubeMapMeshSetActor(prm_name,
                                prm_model,
                                "CubeMapMeshSetEffect",
                                "CubeMapMeshSetTechnique") {
    _class_name = "CubeMapMeshSetActor";
    _pWorldCollisionChecker = (WorldCollisionChecker*)getChecker();
}

void CubeMapMeshSetActor::drawHitArea() {
#ifdef MY_DEBUG
    WorldCollisionChecker::drawHitArea(_pWorldCollisionChecker);
#endif
}

GgafDx::CollisionChecker* CubeMapMeshSetActor::createChecker(kind_t prm_kind) {
    return UTIL::createCollisionChecker(this, prm_kind);
}

CubeMapMeshSetActor::~CubeMapMeshSetActor() {
}
