#include "jp/ggaf/lib/actor/DefaultMeshSetActor.h"

#include "jp/ggaf/lib/util/StgUtil.h"
#include "jp/ggaf/lib/util/WorldCollisionChecker.h"



using namespace GgafLib;

DefaultMeshSetActor::DefaultMeshSetActor(const char* prm_name, const char* prm_model) :
    GgafDx::MeshSetActor(prm_name,
                       prm_model,
                       "DefaultMeshSetEffect",
                       "DefaultMeshSetTechnique") {
    _class_name = "DefaultMeshSetActor";
    _pWorldCollisionChecker = (WorldCollisionChecker*)getChecker();
}

GgafDx::CollisionChecker* DefaultMeshSetActor::createChecker() {
    return UTIL::createCollisionChecker(this);
}

void DefaultMeshSetActor::drawHitArea() {
#ifdef MY_DEBUG
    WorldCollisionChecker::drawHitArea(_pWorldCollisionChecker);
#endif
}

DefaultMeshSetActor::~DefaultMeshSetActor() {
}
