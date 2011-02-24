#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;

SpriteMeshSetActor::SpriteMeshSetActor(const char* prm_name, const char* prm_model) :
    GgafDx9SpriteMeshSetActor(prm_name,
                     prm_model,
                     NEW CollisionChecker(this) ) {

    _class_name = "SpriteMeshSetActor";
    _frame_offset = 0;
    _pCollisionChecker = (CollisionChecker*)_pChecker;
    _pScaler = NEW GgafDx9Scaler(this);
}

void SpriteMeshSetActor::drawHitArea() {
    ColliAABActor::get()->drawHitarea(_pCollisionChecker); ColliAAPrismActor::get()->drawHitarea(_pCollisionChecker); ColliSphereActor::get()->drawHitarea(_pCollisionChecker);
}

SpriteMeshSetActor::~SpriteMeshSetActor() {
    DELETE_IMPOSSIBLE_NULL(_pCollisionChecker);
    DELETE_IMPOSSIBLE_NULL(_pScaler);
}
