#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;

DefaultSpriteActor::DefaultSpriteActor(const char* prm_name, const char* prm_model_id, GgafStatus* prm_pStat) :
    GgafDxSpriteActor(prm_name,
                       prm_model_id,
                       "DefaultSpriteEffect",
                       "DefaultSpriteTechnique",
                       prm_pStat,
                       NEW CollisionChecker(this) ) {
    _class_name = "DefaultSpriteActor";
    _pCollisionChecker = (CollisionChecker*)_pChecker;
    _pScaler = NEW GgafDxScaler(this);
    setZWriteEnable(false);
}

void DefaultSpriteActor::drawHitArea() {
    ColliAABActor::get()->drawHitarea(_pCollisionChecker); ColliAAPrismActor::get()->drawHitarea(_pCollisionChecker); ColliSphereActor::get()->drawHitarea(_pCollisionChecker);
}

DefaultSpriteActor::~DefaultSpriteActor() {
    DELETE_IMPOSSIBLE_NULL(_pCollisionChecker);
    DELETE_IMPOSSIBLE_NULL(_pScaler);
}
