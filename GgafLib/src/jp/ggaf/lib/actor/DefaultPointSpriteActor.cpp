#include "jp/ggaf/lib/actor/DefaultPointSpriteActor.h"

#include "jp/ggaf/lib/util/StgUtil.h"
#include "jp/ggaf/lib/util/CollisionChecker.h"



using namespace GgafLib;

DefaultPointSpriteActor::DefaultPointSpriteActor(const char* prm_name, const char* prm_model_id) :
    GgafDx::PointSpriteActor(prm_name,
                           prm_model_id,
                           "DefaultPointSpriteEffect",
                           "DefaultPointSpriteTechnique",
                           UTIL::createChecker(this) ) {

    _class_name = "DefaultPointSpriteActor";
    _pColliChecker = (CollisionChecker*)_pChecker;
}

void DefaultPointSpriteActor::drawHitArea() {
#ifdef MY_DEBUG
    CollisionChecker::drawHitArea(_pColliChecker);
#endif
}

DefaultPointSpriteActor::~DefaultPointSpriteActor() {
    GGAF_DELETE(_pColliChecker);
}
