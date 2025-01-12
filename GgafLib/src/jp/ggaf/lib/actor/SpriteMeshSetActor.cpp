#include "jp/ggaf/lib/actor/SpriteMeshSetActor.h"

#include "jp/ggaf/lib/util/StgUtil.h"
#include "jp/ggaf/lib/util/WorldCollisionChecker.h"



using namespace GgafLib;

SpriteMeshSetActor::SpriteMeshSetActor(const char* prm_name, const char* prm_model) :
    GgafDx::SpriteMeshSetActor(prm_name,
                             prm_model) {

    _class_name = "SpriteMeshSetActor";
    _pWorldCollisionChecker = (WorldCollisionChecker*)getChecker();
}

void SpriteMeshSetActor::drawHitArea() {
#ifdef MY_DEBUG
    WorldCollisionChecker::drawHitArea(_pWorldCollisionChecker);
#endif
}

GgafDx::CollisionChecker* SpriteMeshSetActor::createChecker(kind_t prm_kind) {
    return UTIL::createCollisionChecker(this, prm_kind);
}

SpriteMeshSetActor::~SpriteMeshSetActor() {
}

