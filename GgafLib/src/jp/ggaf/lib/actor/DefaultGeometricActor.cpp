#include "jp/ggaf/lib/actor/DefaultGeometricActor.h"

#include "jp/ggaf/lib/util/WorldCollisionChecker.h"

using namespace GgafLib;

DefaultGeometricActor::DefaultGeometricActor(const char* prm_name, GgafDx::CollisionChecker* prm_pChecker) :
    GgafDx::GeometricActor(prm_name, prm_pChecker)
{
    _class_name = "DefaultGeometricActor";
    _pColliCollisionChecker = (WorldCollisionChecker*)_pChecker;
}

void DefaultGeometricActor::drawHitArea() {
#ifdef MY_DEBUG
    WorldCollisionChecker::drawHitArea(_pColliCollisionChecker);
#endif
}


DefaultGeometricActor::~DefaultGeometricActor() {
}

