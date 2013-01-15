#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;

SpriteMeshSetActor::SpriteMeshSetActor(const char* prm_name, const char* prm_model, GgafStatus* prm_pStat) :
    GgafDxSpriteMeshSetActor(prm_name,
                              prm_model,
                              prm_pStat,
                              NEW CollisionChecker3D(this) ) {

    _class_name = "SpriteMeshSetActor";
    _pColliChecker = (CollisionChecker3D*)_pChecker;
    _pScaler = NEW GgafDxScaler(this);
}

void SpriteMeshSetActor::drawHitArea() {
    ColliAABActor::get()->drawHitarea(_pColliChecker); ColliAAPrismActor::get()->drawHitarea(_pColliChecker); ColliSphereActor::get()->drawHitarea(_pColliChecker);
}

SpriteMeshSetActor::~SpriteMeshSetActor() {
    DELETE_IMPOSSIBLE_NULL(_pColliChecker);
    DELETE_IMPOSSIBLE_NULL(_pScaler);
}
