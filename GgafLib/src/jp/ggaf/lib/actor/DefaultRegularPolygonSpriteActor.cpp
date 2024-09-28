#include "jp/ggaf/lib/actor/DefaultRegularPolygonSpriteActor.h"

#include "jp/ggaf/lib/util/StgUtil.h"
#include "jp/ggaf/lib/util/WorldCollisionChecker.h"



using namespace GgafLib;

DefaultRegularPolygonSpriteActor::DefaultRegularPolygonSpriteActor(const char* prm_name, const char* prm_model) :
    GgafDx::RegularPolygonSpriteActor(prm_name,
                                  prm_model,
                                  "DefaultRegularPolygonSpriteEffect",
                                  "DefaultRegularPolygonSpriteTechnique") {
    _class_name = "DefaultRegularPolygonSpriteActor";
    _pWorldCollisionChecker = (WorldCollisionChecker*)getChecker();
    setZWriteEnable(false);
}

void DefaultRegularPolygonSpriteActor::drawHitArea() {
#ifdef MY_DEBUG
    WorldCollisionChecker::drawHitArea(_pWorldCollisionChecker);
#endif
}

GgafDx::CollisionChecker* DefaultRegularPolygonSpriteActor::createChecker() {
    return UTIL::createCollisionChecker(this);
}

DefaultRegularPolygonSpriteActor::~DefaultRegularPolygonSpriteActor() {
}

