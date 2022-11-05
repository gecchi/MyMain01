#include "jp/ggaf/lib/actor/DefaultFramedSpriteActor.h"

#include "jp/ggaf/lib/util/StgUtil.h"
#include "jp/ggaf/lib/util/WorldCollisionChecker.h"



using namespace GgafLib;

DefaultFramedSpriteActor::DefaultFramedSpriteActor(const char* prm_name, const char* prm_model) :
    GgafDx::FramedSpriteActor(prm_name,
                      prm_model,
                      "DefaultFramedSpriteEffect",
                      "DefaultFramedSpriteTechnique",
                      UTIL::createCollisionChecker(this) ) {
    _class_name = "DefaultFramedSpriteActor";
    _pColliCollisionChecker = (WorldCollisionChecker*)_pChecker;
    setZWriteEnable(false);
}

void DefaultFramedSpriteActor::drawHitArea() {
#ifdef MY_DEBUG
    WorldCollisionChecker::drawHitArea(_pColliCollisionChecker);
#endif
}

DefaultFramedSpriteActor::~DefaultFramedSpriteActor() {
    GGAF_DELETE(_pColliCollisionChecker);
}

