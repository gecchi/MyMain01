#include "jp/ggaf/lib/actor/DefaultSpriteSetActor.h"

#include "jp/ggaf/lib/util/StgUtil.h"
#include "jp/ggaf/lib/util/WorldCollisionChecker.h"

using namespace GgafLib;

DefaultSpriteSetActor::DefaultSpriteSetActor(const char* prm_name, const char* prm_model) :
    GgafDx::SpriteSetActor(prm_name,
                           prm_model,
                           "DefaultSpriteSetEffect",
                           "DefaultSpriteSetTechnique") {

    _class_name = "DefaultSpriteSetActor";
    _pWorldCollisionChecker = (WorldCollisionChecker*)getChecker();
    setZWriteEnable(false);
}

void DefaultSpriteSetActor::drawHitArea() {
#ifdef MY_DEBUG
    WorldCollisionChecker::drawHitArea(_pWorldCollisionChecker);
#endif
}

GgafDx::CollisionChecker* DefaultSpriteSetActor::createChecker() {
    return UTIL::createCollisionChecker(this);
}

DefaultSpriteSetActor::~DefaultSpriteSetActor() {
}
