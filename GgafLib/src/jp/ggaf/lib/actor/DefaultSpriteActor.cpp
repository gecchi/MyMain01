#include "jp/ggaf/lib/actor/DefaultSpriteActor.h"

#include "jp/ggaf/lib/util/StgUtil.h"
#include "jp/ggaf/lib/util/WorldCollisionChecker.h"



using namespace GgafLib;

DefaultSpriteActor::DefaultSpriteActor(const char* prm_name, const char* prm_model) :
    GgafDx::SpriteActor(prm_name,
                      prm_model,
                      "DefaultSpriteEffect",
                      "DefaultSpriteTechnique",
                      UTIL::createCollisionChecker(this) ) {
    _class_name = "DefaultSpriteActor";
    _pColliCollisionChecker = (WorldCollisionChecker*)_pChecker;
    setZWriteEnable(false);
}

void DefaultSpriteActor::drawHitArea() {
#ifdef MY_DEBUG
    WorldCollisionChecker::drawHitArea(_pColliCollisionChecker);
#endif
}

DefaultSpriteActor::~DefaultSpriteActor() {
    GGAF_DELETE(_pColliCollisionChecker);
}

