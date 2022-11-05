#include "jp/ggaf/lib/actor/DefaultMeshActor.h"

#include "jp/ggaf/lib/util/StgUtil.h"
#include "jp/ggaf/lib/util/WorldCollisionChecker.h"



using namespace GgafLib;

DefaultMeshActor::DefaultMeshActor(const char* prm_name,
                                   const char* prm_model) :
    GgafDx::MeshActor(prm_name,
                     prm_model,
                     "DefaultMeshEffect",
                     "DefaultMeshTechnique",
                     UTIL::createCollisionChecker(this) ) {
    _class_name = "DefaultMeshActor";
    _pColliCollisionChecker = (WorldCollisionChecker*)_pChecker;
}

void DefaultMeshActor::drawHitArea() {
#ifdef MY_DEBUG
    WorldCollisionChecker::drawHitArea(_pColliCollisionChecker);
#endif
}

DefaultMeshActor::~DefaultMeshActor() {
    GGAF_DELETE(_pColliCollisionChecker);
}
