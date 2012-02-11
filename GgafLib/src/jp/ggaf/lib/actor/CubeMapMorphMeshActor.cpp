#include "stdafx.h"
using namespace std;
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
    _pCollisionChecker = (CollisionChecker*)_pChecker;

    _pScaler = NEW GgafDxScaler(this);
    _pMorpher = NEW GgafDxMorpher(this);
}

void CubeMapMorphMeshActor::drawHitArea() {
    ColliAABActor::get()->drawHitarea(_pCollisionChecker); ColliAAPrismActor::get()->drawHitarea(_pCollisionChecker); ColliSphereActor::get()->drawHitarea(_pCollisionChecker);
}


CubeMapMorphMeshActor::~CubeMapMorphMeshActor() {
    DELETE_IMPOSSIBLE_NULL(_pCollisionChecker);
    DELETE_IMPOSSIBLE_NULL(_pScaler);
    DELETE_IMPOSSIBLE_NULL(_pMorpher);
}
