#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;

DefaultMorphMeshActor::DefaultMorphMeshActor(const char* prm_name, const char* prm_model_id) :
    GgafDx9MorphMeshActor(prm_name,
                     prm_model_id,
                     "DefaultMorphMeshEffect",
                     "DefaultMorphMeshTechnique",
                     NEW CollisionChecker(this) ) {

    _class_name = "DefaultMorphMeshActor";
    _offset_frames = 0;
    _pCollisionChecker = (CollisionChecker*)_pChecker;

    _pScaler = NEW GgafDx9Scaler(this);
    _pMorpher = NEW GgafDx9Morpher(this);
}

void DefaultMorphMeshActor::drawHitArea() {
    ColliAABActor::get()->drawHitarea(_pCollisionChecker); ColliAAPrismActor::get()->drawHitarea(_pCollisionChecker); ColliSphereActor::get()->drawHitarea(_pCollisionChecker);
}


DefaultMorphMeshActor::~DefaultMorphMeshActor() {
    DELETE_IMPOSSIBLE_NULL(_pCollisionChecker);
    DELETE_IMPOSSIBLE_NULL(_pScaler);
    DELETE_IMPOSSIBLE_NULL(_pMorpher);
}
