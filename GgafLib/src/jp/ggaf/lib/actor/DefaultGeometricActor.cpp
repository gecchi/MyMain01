#include "jp/ggaf/lib/actor/DefaultGeometricActor.h"

#include "jp/ggaf/lib/util/CollisionChecker.h"

using namespace GgafLib;

DefaultGeometricActor::DefaultGeometricActor(const char* prm_name, GgafDx::Checker* prm_pChecker) :
    GgafDx::GeometricActor(prm_name, prm_pChecker)
{
    _class_name = "DefaultGeometricActor";
    _pColliChecker = (CollisionChecker*)_pChecker;
}

void DefaultGeometricActor::drawHitArea() {
#ifdef MY_DEBUG
    CollisionChecker::drawHitArea(_pColliChecker);
#endif
}


DefaultGeometricActor::~DefaultGeometricActor() {
}

