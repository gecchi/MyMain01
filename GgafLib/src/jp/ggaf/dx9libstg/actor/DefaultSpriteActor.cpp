#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;

DefaultSpriteActor::DefaultSpriteActor(const char* prm_name, const char* prm_model_id, GgafStatus* prm_pStat) :
    GgafDx9SpriteActor(prm_name,
                       prm_model_id,
                       "DefaultSpriteEffect",
                       "DefaultSpriteTechnique",
                       prm_pStat,
                       NEW CollisionChecker(this) ) {
    _class_name = "DefaultSpriteActor";
    _offset_frames = 0;
    _pCollisionChecker = (CollisionChecker*)_pChecker;
    _pScaler = NEW GgafDx9Scaler(this);
    setZWriteEnable(false);
}

void DefaultSpriteActor::drawHitArea() {
    ColliAABActor::get()->drawHitarea(_pCollisionChecker); ColliAAPrismActor::get()->drawHitarea(_pCollisionChecker); ColliSphereActor::get()->drawHitarea(_pCollisionChecker);
}

DefaultSpriteActor::~DefaultSpriteActor() {
    DELETE_IMPOSSIBLE_NULL(_pCollisionChecker);
    DELETE_IMPOSSIBLE_NULL(_pScaler);
}
