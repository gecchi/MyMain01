#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;

SpriteMeshActor::SpriteMeshActor(const char* prm_name, const char* prm_model, GgafStatus* prm_pStat) :
    GgafDxSpriteMeshActor(prm_name,
                           prm_model,
                           prm_pStat,
                           NEW CollisionChecker(this) ) {

    _class_name = "SpriteMeshActor";
    _pCollisionChecker = (CollisionChecker*)_pChecker;
    _pScaler = NEW GgafDxScaler(this);
}

void SpriteMeshActor::drawHitArea() {
    ColliAABActor::get()->drawHitarea(_pCollisionChecker); ColliAAPrismActor::get()->drawHitarea(_pCollisionChecker); ColliSphereActor::get()->drawHitarea(_pCollisionChecker);
}

SpriteMeshActor::~SpriteMeshActor() {
    DELETE_IMPOSSIBLE_NULL(_pCollisionChecker);
    DELETE_IMPOSSIBLE_NULL(_pScaler);
}
