#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;

DefaultSpriteSetActor::DefaultSpriteSetActor(const char* prm_name, const char* prm_model_id) :
    GgafDx9SpriteSetActor(prm_name,
                          prm_model_id,
                          "DefaultSpriteSetEffect",
                          "DefaultSpriteSetTechnique",
                          NEW CollisionChecker(this) ) {
    _class_name = "DefaultSpriteSetActor";
    _offset_frames = 0;
    _pCollisionChecker = (CollisionChecker*)_pChecker;
    _pScaler = NEW GgafDx9Scaler(this);
    setZWriteEnable(false);
}

void DefaultSpriteSetActor::drawHitArea() {
    ColliAABActor::get()->drawHitarea(_pCollisionChecker); ColliAAPrismActor::get()->drawHitarea(_pCollisionChecker); ColliSphereActor::get()->drawHitarea(_pCollisionChecker);
}


DefaultSpriteSetActor::~DefaultSpriteSetActor() {
    DELETE_IMPOSSIBLE_NULL(_pCollisionChecker);
    DELETE_IMPOSSIBLE_NULL(_pScaler);
}
