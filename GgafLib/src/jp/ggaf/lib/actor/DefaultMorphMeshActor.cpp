#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;

DefaultMorphMeshActor::DefaultMorphMeshActor(const char* prm_name, const char* prm_model_id, GgafStatus* prm_pStat) :
    GgafDxMorphMeshActor(prm_name,
                          prm_model_id,
                          "DefaultMorphMeshEffect",
                          "DefaultMorphMeshTechnique",
                          prm_pStat,
                          NEW CollisionChecker3D(this) ) {

    _class_name = "DefaultMorphMeshActor";
    _pColliChecker = (CollisionChecker3D*)_pChecker;
    _pScaler = NEW GgafDxScaler(this);
}

void DefaultMorphMeshActor::drawHitArea() {
    ColliAABActor::get()->drawHitarea(_pColliChecker); ColliAAPrismActor::get()->drawHitarea(_pColliChecker); ColliSphereActor::get()->drawHitarea(_pColliChecker);
}


DefaultMorphMeshActor::~DefaultMorphMeshActor() {
    GGAF_DELETE(_pColliChecker);
    GGAF_DELETE(_pScaler);
}
