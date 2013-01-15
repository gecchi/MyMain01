#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;

DefaultPointSpriteActor::DefaultPointSpriteActor(const char* prm_name, const char* prm_model_id, GgafStatus* prm_pStat) :
    GgafDxPointSpriteActor(prm_name,
                            prm_model_id,
                            "DefaultPointSpriteEffect",
                            "DefaultPointSpriteTechnique",
                            prm_pStat,
                            NEW CollisionChecker3D(this) ) {
    _class_name = "DefaultPointSpriteActor";
    _pColliChecker = (CollisionChecker3D*)_pChecker;
    _pScaler = NEW GgafDxScaler(this);
}

void DefaultPointSpriteActor::drawHitArea() {
    ColliAABActor::get()->drawHitarea(_pColliChecker); ColliAAPrismActor::get()->drawHitarea(_pColliChecker); ColliSphereActor::get()->drawHitarea(_pColliChecker);
}

DefaultPointSpriteActor::~DefaultPointSpriteActor() {
    DELETE_IMPOSSIBLE_NULL(_pColliChecker);
    DELETE_IMPOSSIBLE_NULL(_pScaler);
}
