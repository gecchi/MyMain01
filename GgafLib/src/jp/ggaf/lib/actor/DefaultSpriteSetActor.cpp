#include "jp/ggaf/lib/actor/DefaultSpriteSetActor.h"

#include "jp/ggaf/lib/util/StgUtil.h"
#include "jp/ggaf/lib/util/CollisionChecker.h"

using namespace GgafLib;

DefaultSpriteSetActor::DefaultSpriteSetActor(const char* prm_name, const char* prm_model) :
    GgafDx::SpriteSetActor(prm_name,
                           prm_model,
                           "DefaultSpriteSetEffect",
                           "DefaultSpriteSetTechnique",
                           UTIL::createChecker(this) ) {

    _class_name = "DefaultSpriteSetActor";
    _pColliChecker = (CollisionChecker*)_pChecker;
    setZWriteEnable(false);
}

void DefaultSpriteSetActor::drawHitArea() {
#ifdef MY_DEBUG
    CollisionChecker::drawHitArea(_pColliChecker);
#endif
}

DefaultSpriteSetActor::~DefaultSpriteSetActor() {
    GGAF_DELETE(_pColliChecker);
}
