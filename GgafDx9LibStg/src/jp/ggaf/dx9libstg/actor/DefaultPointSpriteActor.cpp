#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;

DefaultPointSpriteActor::DefaultPointSpriteActor(const char* prm_name, const char* prm_model_id) :
    GgafDx9PointSpriteActor(prm_name,
                       prm_model_id,
                       "DefaultPointSpriteEffect",
                       "DefaultPointSpriteTechnique",
                       NEW CollisionChecker(this) ) {
    _class_name = "DefaultPointSpriteActor";
    _frame_offset = 0;
    _pCollisionChecker = (CollisionChecker*)_pChecker;
    _pScaler = NEW GgafDx9GeometryScaler(this);
}

void DefaultPointSpriteActor::drawHitArea() {
    CubeEx::get()->drawHitarea(_pCollisionChecker); SphereEx::get()->drawHitarea(_pCollisionChecker);
}

DefaultPointSpriteActor::~DefaultPointSpriteActor() {
    DELETE_IMPOSSIBLE_NULL(_pCollisionChecker);
    DELETE_IMPOSSIBLE_NULL(_pScaler);
}
