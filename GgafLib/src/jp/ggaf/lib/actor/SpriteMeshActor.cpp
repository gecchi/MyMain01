#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;

SpriteMeshActor::SpriteMeshActor(const char* prm_name, const char* prm_model, GgafStatus* prm_pStat) :
    GgafDxSpriteMeshActor(prm_name,
                           prm_model,
                           prm_pStat,
                           NEW CollisionChecker3D(this) ) {

    _class_name = "SpriteMeshActor";
    _pColliChecker = (CollisionChecker3D*)_pChecker;
    _pScaler = NEW GgafDxScaler(this);
}

void SpriteMeshActor::drawHitArea() {
    ColliAABActor::get()->drawHitarea(_pColliChecker); ColliAAPrismActor::get()->drawHitarea(_pColliChecker); ColliSphereActor::get()->drawHitarea(_pColliChecker);
}

SpriteMeshActor::~SpriteMeshActor() {
    DELETE_IMPOSSIBLE_NULL(_pColliChecker);
    DELETE_IMPOSSIBLE_NULL(_pScaler);
}
