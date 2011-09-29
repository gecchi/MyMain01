#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;

DefaultMorphMeshActor::DefaultMorphMeshActor(const char* prm_name, const char* prm_model_id, GgafStatus* prm_pStat) :
    GgafDxMorphMeshActor(prm_name,
                          prm_model_id,
                          "DefaultMorphMeshEffect",
                          "DefaultMorphMeshTechnique",
                          prm_pStat,
                          NEW CollisionChecker(this) ) {

    _class_name = "DefaultMorphMeshActor";
    _offset_frames = 0;
    _pCollisionChecker = (CollisionChecker*)_pChecker;

    _pScaler = NEW GgafDxScaler(this);
    _pMorpher = NEW GgafDxMorpher(this);
}

void DefaultMorphMeshActor::drawHitArea() {
    ColliAABActor::get()->drawHitarea(_pCollisionChecker); ColliAAPrismActor::get()->drawHitarea(_pCollisionChecker); ColliSphereActor::get()->drawHitarea(_pCollisionChecker);
}


DefaultMorphMeshActor::~DefaultMorphMeshActor() {
    DELETE_IMPOSSIBLE_NULL(_pCollisionChecker);
    DELETE_IMPOSSIBLE_NULL(_pScaler);
    DELETE_IMPOSSIBLE_NULL(_pMorpher);
}
