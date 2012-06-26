#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;

CubeMapMorphMeshActor::CubeMapMorphMeshActor(const char* prm_name, const char* prm_model_id, GgafStatus* prm_pStat) :
        GgafDxCubeMapMorphMeshActor(prm_name,
                                    prm_model_id,
                                    "CubeMapMorphMeshEffect",
                                    "CubeMapMorphMeshTechnique",
                                    prm_pStat,
                                    NEW CollisionChecker(this) ) {

    _class_name = "CubeMapMorphMeshActor";
    _pColliChecker = (CollisionChecker*)_pChecker;
    _pScaler = NEW GgafDxScaler(this);
}

void CubeMapMorphMeshActor::drawHitArea() {
    ColliAABActor::get()->drawHitarea(_pColliChecker); ColliAAPrismActor::get()->drawHitarea(_pColliChecker); ColliSphereActor::get()->drawHitarea(_pColliChecker);
}


CubeMapMorphMeshActor::~CubeMapMorphMeshActor() {
    DELETE_IMPOSSIBLE_NULL(_pColliChecker);
    DELETE_IMPOSSIBLE_NULL(_pScaler);
}
