#include "jp/ggaf/lib/actor/SpriteMeshActor.h"

#include "jp/ggaf/lib/util/StgUtil.h"
#include "jp/ggaf/lib/util/WorldCollisionChecker.h"



using namespace GgafLib;

SpriteMeshActor::SpriteMeshActor(const char* prm_name, const char* prm_model) :
    GgafDx::SpriteMeshActor(prm_name,
                            prm_model) {

    _class_name = "SpriteMeshActor";
    _pWorldCollisionChecker = (WorldCollisionChecker*)getChecker();
}

void SpriteMeshActor::drawHitArea() {
#ifdef MY_DEBUG
    WorldCollisionChecker::drawHitArea(_pWorldCollisionChecker);
#endif
}

GgafDx::CollisionChecker* SpriteMeshActor::createChecker() {
    return UTIL::createCollisionChecker(this);
}

SpriteMeshActor::~SpriteMeshActor() {
}


