#include "jp/ggaf/lib/actor/DefaultD3DXAniMeshActor.h"

#include "jp/ggaf/lib/util/StgUtil.h"
#include "jp/ggaf/lib/util/WorldCollisionChecker.h"



using namespace GgafLib;

DefaultD3DXAniMeshActor::DefaultD3DXAniMeshActor(const char* prm_name, const char* prm_model) :
    GgafDx::D3DXAniMeshActor(prm_name,
                           prm_model,
                           "DefaultD3DXAniMeshEffect",
                           "DefaultD3DXAniMeshTechnique",
                           UTIL::createCollisionChecker(this) ) {
    _class_name = "DefaultD3DXAniMeshActor";
    _pColliCollisionChecker = (WorldCollisionChecker*)_pChecker;
}

void DefaultD3DXAniMeshActor::drawHitArea() {
#ifdef MY_DEBUG
    WorldCollisionChecker::drawHitArea(_pColliCollisionChecker);
#endif
}

DefaultD3DXAniMeshActor::~DefaultD3DXAniMeshActor() {
    GGAF_DELETE(_pColliCollisionChecker);
}
