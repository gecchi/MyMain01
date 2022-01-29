#include "jp/ggaf/lib/actor/DefaultFramedSpriteActor.h"

#include "jp/ggaf/lib/util/StgUtil.h"
#include "jp/ggaf/lib/util/CollisionChecker.h"



using namespace GgafLib;

DefaultFramedSpriteActor::DefaultFramedSpriteActor(const char* prm_name, const char* prm_model) :
    GgafDx::FramedSpriteActor(prm_name,
                      prm_model,
                      "DefaultFramedSpriteEffect",
                      "DefaultFramedSpriteTechnique",
                      UTIL::createChecker(this) ) {
    _class_name = "DefaultFramedSpriteActor";
    _pColliChecker = (CollisionChecker*)_pChecker;
    setZWriteEnable(false);
}

void DefaultFramedSpriteActor::drawHitArea() {
#ifdef MY_DEBUG
    CollisionChecker::drawHitArea(_pColliChecker);
#endif
}

DefaultFramedSpriteActor::~DefaultFramedSpriteActor() {
    GGAF_DELETE(_pColliChecker);
}

