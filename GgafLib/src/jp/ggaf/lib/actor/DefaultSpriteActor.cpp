#include "jp/ggaf/lib/actor/DefaultSpriteActor.h"

#include "jp/ggaf/lib/util/StgUtil.h"
#include "jp/ggaf/lib/util/CollisionChecker.h"



using namespace GgafLib;

DefaultSpriteActor::DefaultSpriteActor(const char* prm_name, const char* prm_model_id) :
    GgafDx::SpriteActor(prm_name,
                      prm_model_id,
                      "DefaultSpriteEffect",
                      "DefaultSpriteTechnique",
                      UTIL::createChecker(this) ) {
    _class_name = "DefaultSpriteActor";
    _pColliChecker = (CollisionChecker*)_pChecker;
    setZWriteEnable(false);
}

void DefaultSpriteActor::drawHitArea() {
#ifdef MY_DEBUG
    CollisionChecker::drawHitArea(_pColliChecker);
#endif
}

DefaultSpriteActor::~DefaultSpriteActor() {
    GGAF_DELETE(_pColliChecker);
}

