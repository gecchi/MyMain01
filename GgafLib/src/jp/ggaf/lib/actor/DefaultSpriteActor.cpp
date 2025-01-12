#include "jp/ggaf/lib/actor/DefaultSpriteActor.h"

#include "jp/ggaf/lib/util/StgUtil.h"
#include "jp/ggaf/lib/util/WorldCollisionChecker.h"



using namespace GgafLib;

DefaultSpriteActor::DefaultSpriteActor(const char* prm_name, const char* prm_model) :
    GgafDx::SpriteActor(prm_name,
                        prm_model,
                        "DefaultSpriteEffect",
                        "DefaultSpriteTechnique") {
    _class_name = "DefaultSpriteActor";
    _pWorldCollisionChecker = (WorldCollisionChecker*)getChecker();
    setZBufferWriteEnable(false);
}

void DefaultSpriteActor::drawHitArea() {
#ifdef MY_DEBUG
    WorldCollisionChecker::drawHitArea(_pWorldCollisionChecker);
#endif
}

GgafDx::CollisionChecker* DefaultSpriteActor::createChecker(kind_t prm_kind) {
    return UTIL::createCollisionChecker(this, prm_kind);
}

DefaultSpriteActor::~DefaultSpriteActor() {
}

