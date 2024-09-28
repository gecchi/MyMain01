#include "jp/ggaf/lib/actor/DefaultPointSpriteActor.h"

#include "jp/ggaf/lib/util/StgUtil.h"
#include "jp/ggaf/lib/util/WorldCollisionChecker.h"



using namespace GgafLib;

DefaultPointSpriteActor::DefaultPointSpriteActor(const char* prm_name, const char* prm_model) :
    GgafDx::PointSpriteActor(prm_name,
                           prm_model,
                           "DefaultPointSpriteEffect",
                           "DefaultPointSpriteTechnique") {

    _class_name = "DefaultPointSpriteActor";
    _pWorldCollisionChecker = (WorldCollisionChecker*)getChecker();
}

void DefaultPointSpriteActor::drawHitArea() {
#ifdef MY_DEBUG
    WorldCollisionChecker::drawHitArea(_pWorldCollisionChecker);
#endif
}

GgafDx::CollisionChecker* DefaultPointSpriteActor::createChecker() {
    return UTIL::createCollisionChecker(this);
}

DefaultPointSpriteActor::~DefaultPointSpriteActor() {
}
