#include "jp/ggaf/lib/actor/DefaultD3DXAniMeshActor.h"

#include "jp/ggaf/lib/util/StgUtil.h"
#include "jp/ggaf/lib/util/CollisionChecker.h"



using namespace GgafLib;

DefaultD3DXAniMeshActor::DefaultD3DXAniMeshActor(const char* prm_name, const char* prm_model) :
    GgafDx::D3DXAniMeshActor(prm_name,
                           prm_model,
                           "DefaultD3DXAniMeshEffect",
                           "DefaultD3DXAniMeshTechnique",
                           UTIL::createChecker(this) ) {
    _class_name = "DefaultD3DXAniMeshActor";
    _pColliChecker = (CollisionChecker*)_pChecker;
}

void DefaultD3DXAniMeshActor::drawHitArea() {
#ifdef MY_DEBUG
    CollisionChecker::drawHitArea(_pColliChecker);
#endif
}

DefaultD3DXAniMeshActor::~DefaultD3DXAniMeshActor() {
    GGAF_DELETE(_pColliChecker);
}
