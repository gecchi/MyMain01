#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;

DefaultMeshSetActor::DefaultMeshSetActor(const char* prm_name, const char* prm_model, GgafStatus* prm_pStat) :
    GgafDxMeshSetActor(prm_name,
                       prm_model,
                       "DefaultMeshSetEffect",
                       "DefaultMeshSetTechnique",
                       prm_pStat,
                       NEW CollisionChecker3D(this) ) {

    _class_name = "DefaultMeshSetActor";
    _pColliChecker = (CollisionChecker3D*)_pChecker;
    _pScaler = NEW GgafDxScaler(this);
}

void DefaultMeshSetActor::drawHitArea() {
    ColliAABActor::get()->drawHitarea(_pColliChecker); ColliAAPrismActor::get()->drawHitarea(_pColliChecker); ColliSphereActor::get()->drawHitarea(_pColliChecker);
}

DefaultMeshSetActor::~DefaultMeshSetActor() {
    GGAF_DELETE(_pColliChecker);
    GGAF_DELETE(_pScaler);
}
