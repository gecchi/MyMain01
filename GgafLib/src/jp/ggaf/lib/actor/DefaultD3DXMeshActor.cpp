#include "jp/ggaf/lib/actor/DefaultD3DXMeshActor.h"

#include "jp/ggaf/lib/util/StgUtil.h"
#include "jp/ggaf/lib/util/WorldCollisionChecker.h"



using namespace GgafLib;

DefaultD3DXMeshActor::DefaultD3DXMeshActor(const char* prm_name, const char* prm_model) :
    GgafDx::D3DXMeshActor(prm_name,
                          prm_model,
                          "DefaultMeshEffect",
                          "DefaultMeshTechnique") {
    _class_name = "DefaultD3DXMeshActor";
    _pWorldCollisionChecker = (WorldCollisionChecker*)getChecker();
}

void DefaultD3DXMeshActor::drawHitArea() {
#ifdef MY_DEBUG
    WorldCollisionChecker::drawHitArea(_pWorldCollisionChecker);
#endif
}

GgafDx::CollisionChecker* DefaultD3DXMeshActor::createChecker(kind_t prm_kind) {
    return UTIL::createCollisionChecker(this, prm_kind);
}

DefaultD3DXMeshActor::~DefaultD3DXMeshActor() {
}
