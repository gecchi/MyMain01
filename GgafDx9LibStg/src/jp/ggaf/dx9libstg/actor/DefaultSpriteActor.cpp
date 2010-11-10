#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;

DefaultSpriteActor::DefaultSpriteActor(const char* prm_name, const char* prm_model_id) :
    GgafDx9SpriteActor(prm_name,
                       prm_model_id,
                       "DefaultSpriteEffect",
                       "DefaultSpriteTechnique",
                       NEW CollisionChecker(this) ) {
    _class_name = "DefaultSpriteActor";
    _frame_offset = 0;
    _pCollisionChecker = (CollisionChecker*)_pChecker;
    _pScaler = NEW GgafDx9GeometricScaler(this);
    setZWriteEnable(false);
}

void DefaultSpriteActor::drawHitArea() {
    CubeEx::get()->drawHitarea(_pCollisionChecker); SphereEx::get()->drawHitarea(_pCollisionChecker);
}

DefaultSpriteActor::~DefaultSpriteActor() {
    DELETE_IMPOSSIBLE_NULL(_pCollisionChecker);
    DELETE_IMPOSSIBLE_NULL(_pScaler);
}
