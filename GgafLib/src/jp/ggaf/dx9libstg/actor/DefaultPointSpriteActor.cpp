#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;

DefaultPointSpriteActor::DefaultPointSpriteActor(const char* prm_name, const char* prm_model_id, GgafStatus* prm_pStat) :
    GgafDx9PointSpriteActor(prm_name,
                            prm_model_id,
                            "DefaultPointSpriteEffect",
                            "DefaultPointSpriteTechnique",
                            prm_pStat,
                            NEW CollisionChecker(this) ) {
    _class_name = "DefaultPointSpriteActor";
    _offset_frames = 0;
    _pCollisionChecker = (CollisionChecker*)_pChecker;
    _pScaler = NEW GgafDx9Scaler(this);
}

void DefaultPointSpriteActor::drawHitArea() {
    ColliAABActor::get()->drawHitarea(_pCollisionChecker); ColliAAPrismActor::get()->drawHitarea(_pCollisionChecker); ColliSphereActor::get()->drawHitarea(_pCollisionChecker);
}

DefaultPointSpriteActor::~DefaultPointSpriteActor() {
    DELETE_IMPOSSIBLE_NULL(_pCollisionChecker);
    DELETE_IMPOSSIBLE_NULL(_pScaler);
}
