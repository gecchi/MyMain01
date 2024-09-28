#include "jp/ggaf/lib/actor/DefaultGeometricActor.h"

#include "jp/ggaf/lib/util/WorldCollisionChecker.h"

using namespace GgafLib;

DefaultGeometricActor::DefaultGeometricActor(const char* prm_name) :
    GgafDx::GeometricActor(prm_name)
{
    _class_name = "DefaultGeometricActor";
    _pWorldCollisionChecker = (WorldCollisionChecker*)getChecker();
}

void DefaultGeometricActor::drawHitArea() {
#ifdef MY_DEBUG
    WorldCollisionChecker::drawHitArea(_pWorldCollisionChecker);
#endif
}

DefaultGeometricActor::~DefaultGeometricActor() {
}

