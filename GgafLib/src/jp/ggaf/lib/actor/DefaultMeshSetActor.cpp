#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;

DefaultMeshSetActor::DefaultMeshSetActor(const char* prm_name, const char* prm_model, GgafStatus* prm_pStat) :
    GgafDxMeshSetActor(prm_name,
                        prm_model,
                        "DefaultMeshSetEffect",
                        "DefaultMeshSetTechnique",
                        prm_pStat,
                        NEW CollisionChecker(this) ) {

    _class_name = "DefaultMeshSetActor";
    _pCollisionChecker = (CollisionChecker*)_pChecker;
    _pScaler = NEW GgafDxScaler(this);
}

void DefaultMeshSetActor::drawHitArea() {
    ColliAABActor::get()->drawHitarea(_pCollisionChecker); ColliAAPrismActor::get()->drawHitarea(_pCollisionChecker); ColliSphereActor::get()->drawHitarea(_pCollisionChecker);
}

DefaultMeshSetActor::~DefaultMeshSetActor() {
    DELETE_IMPOSSIBLE_NULL(_pCollisionChecker);
    DELETE_IMPOSSIBLE_NULL(_pScaler);
}
