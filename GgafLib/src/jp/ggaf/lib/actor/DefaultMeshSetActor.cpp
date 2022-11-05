#include "jp/ggaf/lib/actor/DefaultMeshSetActor.h"

#include "jp/ggaf/lib/util/StgUtil.h"
#include "jp/ggaf/lib/util/WorldCollisionChecker.h"



using namespace GgafLib;

DefaultMeshSetActor::DefaultMeshSetActor(const char* prm_name, const char* prm_model) :
    GgafDx::MeshSetActor(prm_name,
                       prm_model,
                       "DefaultMeshSetEffect",
                       "DefaultMeshSetTechnique",
                       UTIL::createCollisionChecker(this) ) {
    _class_name = "DefaultMeshSetActor";
    _pColliCollisionChecker = (WorldCollisionChecker*)_pChecker;
}

void DefaultMeshSetActor::drawHitArea() {
#ifdef MY_DEBUG
    WorldCollisionChecker::drawHitArea(_pColliCollisionChecker);
#endif
}

DefaultMeshSetActor::~DefaultMeshSetActor() {
    GGAF_DELETE(_pColliCollisionChecker);
}
