#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;

CubeMapMorphMeshActor::CubeMapMorphMeshActor(const char* prm_name, const char* prm_model_id) :
    GgafDx9CubeMapMorphMeshActor(prm_name,
                     prm_model_id,
                     "CubeMapMorphMeshEffect",
                     "CubeMapMorphMeshTechnique",
                     NEW CollisionChecker(this) ) {

    _class_name = "CubeMapMorphMeshActor";
    _frame_offset = 0;
    _pCollisionChecker = (CollisionChecker*)_pChecker;

    _pScaler = NEW GgafDx9GeometricScaler(this);
    _pMorpher = NEW GgafDx9Morpher(this);
}

void CubeMapMorphMeshActor::drawHitArea() {
    CubeEx::get()->drawHitarea(_pCollisionChecker); SphereEx::get()->drawHitarea(_pCollisionChecker);
}


CubeMapMorphMeshActor::~CubeMapMorphMeshActor() {
    DELETE_IMPOSSIBLE_NULL(_pCollisionChecker);
    DELETE_IMPOSSIBLE_NULL(_pScaler);
    DELETE_IMPOSSIBLE_NULL(_pMorpher);
}
