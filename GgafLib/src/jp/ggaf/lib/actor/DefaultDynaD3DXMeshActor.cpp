#include "jp/ggaf/lib/actor/DefaultDynaD3DXMeshActor.h"

#include "jp/ggaf/lib/util/StgUtil.h"
#include "jp/ggaf/lib/util/WorldCollisionChecker.h"



using namespace GgafLib;

DefaultDynaD3DXMeshActor::DefaultDynaD3DXMeshActor(const char* prm_name, const char* prm_model) :
    GgafDx::DynaD3DXMeshActor(prm_name,
                             prm_model,
                             "DefaultMeshEffect",
                             "DefaultMeshTechnique") {
    _class_name = "DefaultDynaD3DXMeshActor";
    _pWorldCollisionChecker = (WorldCollisionChecker*)getChecker();
}

void DefaultDynaD3DXMeshActor::drawHitArea() {
#ifdef MY_DEBUG
    WorldCollisionChecker::drawHitArea(_pWorldCollisionChecker);
#endif
}

GgafDx::CollisionChecker* DefaultDynaD3DXMeshActor::createChecker() {
    return UTIL::createCollisionChecker(this);
}

DefaultDynaD3DXMeshActor::~DefaultDynaD3DXMeshActor() {
}
