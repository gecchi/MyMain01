#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;

CubeMapMeshActor::CubeMapMeshActor(const char* prm_name, const char* prm_model, GgafStatus* prm_pStat) :
    GgafDxCubeMapMeshActor(prm_name,
                     prm_model,
                     "CubeMapMeshEffect",
                     "CubeMapMeshTechnique",
                     prm_pStat,
                     NEW CollisionChecker3D(this) ) {

    _class_name = "CubeMapMeshActor";
    _pColliChecker = (CollisionChecker3D*)_pChecker;
    _pScaler = NEW GgafDxScaler(this);
}

void CubeMapMeshActor::drawHitArea() {
    ColliAABActor::get()->drawHitarea(_pColliChecker); ColliAAPrismActor::get()->drawHitarea(_pColliChecker); ColliSphereActor::get()->drawHitarea(_pColliChecker);
}

CubeMapMeshActor::~CubeMapMeshActor() {
    GGAF_DELETE(_pColliChecker);
    GGAF_DELETE(_pScaler);
}
