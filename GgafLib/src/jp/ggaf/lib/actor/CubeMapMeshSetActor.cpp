#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;

CubeMapMeshSetActor::CubeMapMeshSetActor(const char* prm_name, const char* prm_model, GgafStatus* prm_pStat) :
    GgafDxCubeMapMeshSetActor(prm_name,
                               prm_model,
                               "CubeMapMeshSetEffect",
                               "CubeMapMeshSetTechnique",
                               prm_pStat,
                               NEW CollisionChecker3D(this) ) {

    _class_name = "CubeMapMeshSetActor";
    _pColliChecker = (CollisionChecker3D*)_pChecker;
    _pScaler = NEW GgafDxScaler(this);
}

void CubeMapMeshSetActor::drawHitArea() {
    ColliAABActor::get()->drawHitarea(_pColliChecker); ColliAAPrismActor::get()->drawHitarea(_pColliChecker); ColliSphereActor::get()->drawHitarea(_pColliChecker);
}

CubeMapMeshSetActor::~CubeMapMeshSetActor() {
    DELETE_IMPOSSIBLE_NULL(_pColliChecker);
    DELETE_IMPOSSIBLE_NULL(_pScaler);
}
