#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;

DefaultSpriteSetActor::DefaultSpriteSetActor(const char* prm_name, const char* prm_model_id, GgafStatus* prm_pStat) :
    GgafDxSpriteSetActor(prm_name,
                          prm_model_id,
                          "DefaultSpriteSetEffect",
                          "DefaultSpriteSetTechnique",
                          prm_pStat,
                          NEW CollisionChecker3D(this) ) {
    _class_name = "DefaultSpriteSetActor";
    _pColliChecker = (CollisionChecker3D*)_pChecker;
    _pScaler = NEW GgafDxScaler(this);
    setZWriteEnable(false);
}

void DefaultSpriteSetActor::drawHitArea() {
    ColliAABActor::get()->drawHitarea(_pColliChecker); ColliAAPrismActor::get()->drawHitarea(_pColliChecker); ColliSphereActor::get()->drawHitarea(_pColliChecker);
}


DefaultSpriteSetActor::~DefaultSpriteSetActor() {
    GGAF_DELETE(_pColliChecker);
    GGAF_DELETE(_pScaler);
}
