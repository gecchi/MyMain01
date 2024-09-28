#include "jp/ggaf/lib/actor/CubeMapMorphMeshActor.h"

#include "jp/ggaf/lib/util/StgUtil.h"
#include "jp/ggaf/lib/util/WorldCollisionChecker.h"



using namespace GgafLib;

CubeMapMorphMeshActor::CubeMapMorphMeshActor(const char* prm_name, const char* prm_model) :
        GgafDx::CubeMapMorphMeshActor(prm_name,
                                    prm_model,
                                    "CubeMapMorphMeshEffect",
                                    "CubeMapMorphMeshTechnique") {
    _class_name = "CubeMapMorphMeshActor";
    _pWorldCollisionChecker = (WorldCollisionChecker*)getChecker();
}

void CubeMapMorphMeshActor::drawHitArea() {
#ifdef MY_DEBUG
    WorldCollisionChecker::drawHitArea(_pWorldCollisionChecker);
#endif
}

GgafDx::CollisionChecker* CubeMapMorphMeshActor::createChecker() {
    return UTIL::createCollisionChecker(this);
}
CubeMapMorphMeshActor::~CubeMapMorphMeshActor() {
}
