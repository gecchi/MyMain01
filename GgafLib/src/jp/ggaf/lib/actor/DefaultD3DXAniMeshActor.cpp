#include "jp/ggaf/lib/actor/DefaultD3DXAniMeshActor.h"

#include "jp/ggaf/lib/util/StgUtil.h"
#include "jp/ggaf/lib/util/WorldCollisionChecker.h"



using namespace GgafLib;

DefaultD3DXAniMeshActor::DefaultD3DXAniMeshActor(const char* prm_name, const char* prm_model) :
    GgafDx::D3DXAniMeshActor(prm_name,
                           prm_model,
                           "DefaultD3DXAniMeshEffect",
                           "DefaultD3DXAniMeshTechnique") {
    _class_name = "DefaultD3DXAniMeshActor";
    _pWorldCollisionChecker = (WorldCollisionChecker*)getChecker();
}

void DefaultD3DXAniMeshActor::drawHitArea() {
#ifdef MY_DEBUG
    WorldCollisionChecker::drawHitArea(_pWorldCollisionChecker);
#endif
}

GgafDx::CollisionChecker* DefaultD3DXAniMeshActor::createChecker(kind_t prm_kind) {
    return UTIL::createCollisionChecker(this, prm_kind);
}

DefaultD3DXAniMeshActor::~DefaultD3DXAniMeshActor() {
}
