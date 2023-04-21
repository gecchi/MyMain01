#include "jp/ggaf/lib/actor/DefaultPointSpriteSetActor.h"

#include "jp/ggaf/lib/util/StgUtil.h"
#include "jp/ggaf/lib/util/WorldCollisionChecker.h"



using namespace GgafLib;

DefaultPointSpriteSetActor::DefaultPointSpriteSetActor(const char* prm_name, const char* prm_model) :
    GgafDx::PointSpriteSetActor(prm_name,
                                prm_model,
                                "DefaultPointSpriteSetEffect",
                                "DefaultPointSpriteSetTechnique",
                                UTIL::createCollisionChecker(this) ) {
    _class_name = "DefaultPointSpriteSetActor";
    _pColliCollisionChecker = (WorldCollisionChecker*)_pChecker;
}

void DefaultPointSpriteSetActor::drawHitArea() {
#ifdef MY_DEBUG
    WorldCollisionChecker::drawHitArea(_pColliCollisionChecker);
#endif
}

DefaultPointSpriteSetActor::~DefaultPointSpriteSetActor() {
    GGAF_DELETE(_pColliCollisionChecker);
}
