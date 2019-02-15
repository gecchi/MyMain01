#include "jp/ggaf/lib/actor/DefaultRegularPolygonSpriteActor.h"

#include "jp/ggaf/lib/util/StgUtil.h"
#include "jp/ggaf/lib/util/CollisionChecker.h"



using namespace GgafLib;

DefaultRegularPolygonSpriteActor::DefaultRegularPolygonSpriteActor(const char* prm_name, const char* prm_model_id) :
    GgafDx::RegularPolygonSpriteActor(prm_name,
                                  prm_model_id,
                                  "DefaultRegularPolygonSpriteEffect",
                                  "DefaultRegularPolygonSpriteTechnique",
                                  UTIL::createChecker(this) ) {
    _class_name = "DefaultRegularPolygonSpriteActor";
    _pColliChecker = (CollisionChecker*)_pChecker;
    setZWriteEnable(false);
}

void DefaultRegularPolygonSpriteActor::drawHitArea() {
#ifdef MY_DEBUG
    CollisionChecker::drawHitArea(_pColliChecker);
#endif
}

DefaultRegularPolygonSpriteActor::~DefaultRegularPolygonSpriteActor() {
    GGAF_DELETE(_pColliChecker);
}

