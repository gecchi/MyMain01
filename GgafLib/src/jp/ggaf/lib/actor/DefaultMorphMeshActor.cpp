#include "jp/ggaf/lib/actor/DefaultMorphMeshActor.h"

#include "jp/ggaf/lib/util/StgUtil.h"
#include "jp/ggaf/lib/util/WorldCollisionChecker.h"



using namespace GgafLib;

DefaultMorphMeshActor::DefaultMorphMeshActor(const char* prm_name, const char* prm_model) :
    GgafDx::MorphMeshActor(prm_name,
                         prm_model,
                         "DefaultMorphMeshEffect",
                         "DefaultMorphMeshTechnique") {

    _class_name = "DefaultMorphMeshActor";
    _pWorldCollisionChecker = (WorldCollisionChecker*)getChecker();
}

void DefaultMorphMeshActor::drawHitArea() {
#ifdef MY_DEBUG
    WorldCollisionChecker::drawHitArea(_pWorldCollisionChecker);
#endif
}

GgafDx::CollisionChecker* DefaultMorphMeshActor::createChecker(kind_t prm_kind) {
    return UTIL::createCollisionChecker(this, prm_kind);
}

DefaultMorphMeshActor::~DefaultMorphMeshActor() {
}
