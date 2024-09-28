#include "jp/ggaf/lib/actor/DefaultMeshActor.h"

#include "jp/ggaf/lib/util/StgUtil.h"
#include "jp/ggaf/lib/util/WorldCollisionChecker.h"



using namespace GgafLib;

DefaultMeshActor::DefaultMeshActor(const char* prm_name,
                                   const char* prm_model) :
    GgafDx::MeshActor(prm_name,
                     prm_model,
                     "DefaultMeshEffect",
                     "DefaultMeshTechnique") {
    _class_name = "DefaultMeshActor";
    _pWorldCollisionChecker = (WorldCollisionChecker*)getChecker();
}

void DefaultMeshActor::drawHitArea() {
#ifdef MY_DEBUG
    WorldCollisionChecker::drawHitArea(_pWorldCollisionChecker);
#endif
}

GgafDx::CollisionChecker* DefaultMeshActor::createChecker() {
    return UTIL::createCollisionChecker(this);
}

DefaultMeshActor::~DefaultMeshActor() {
}
