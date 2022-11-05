#include "jp/ggaf/lib/actor/DefaultD3DXMeshActor.h"

#include "jp/ggaf/lib/util/StgUtil.h"
#include "jp/ggaf/lib/util/WorldCollisionChecker.h"



using namespace GgafLib;

DefaultD3DXMeshActor::DefaultD3DXMeshActor(const char* prm_name, const char* prm_model) :
    GgafDx::D3DXMeshActor(prm_name,
                        prm_model,
                        "DefaultMeshEffect",
                        "DefaultMeshTechnique",
                        UTIL::createCollisionChecker(this) ) {
    _class_name = "DefaultD3DXMeshActor";
    _pColliCollisionChecker = (WorldCollisionChecker*)_pChecker;
}

void DefaultD3DXMeshActor::drawHitArea() {
#ifdef MY_DEBUG
    WorldCollisionChecker::drawHitArea(_pColliCollisionChecker);
#endif
}

DefaultD3DXMeshActor::~DefaultD3DXMeshActor() {
    GGAF_DELETE(_pColliCollisionChecker);
}
