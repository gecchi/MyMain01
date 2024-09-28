#include "jp/ggaf/lib/actor/DefaultFramedSpriteActor.h"

#include "jp/ggaf/lib/util/StgUtil.h"
#include "jp/ggaf/lib/util/WorldCollisionChecker.h"



using namespace GgafLib;

DefaultFramedSpriteActor::DefaultFramedSpriteActor(const char* prm_name, const char* prm_model) :
    GgafDx::FramedSpriteActor(prm_name,
                      prm_model,
                      "DefaultFramedSpriteEffect",
                      "DefaultFramedSpriteTechnique") {
    _class_name = "DefaultFramedSpriteActor";
    _pWorldCollisionChecker = (WorldCollisionChecker*)getChecker();
    setZWriteEnable(false);
}

void DefaultFramedSpriteActor::drawHitArea() {
#ifdef MY_DEBUG
    WorldCollisionChecker::drawHitArea(_pWorldCollisionChecker);
#endif
}

GgafDx::CollisionChecker* DefaultFramedSpriteActor::createChecker() {
    return UTIL::createCollisionChecker(this);
}

DefaultFramedSpriteActor::~DefaultFramedSpriteActor() {
}

