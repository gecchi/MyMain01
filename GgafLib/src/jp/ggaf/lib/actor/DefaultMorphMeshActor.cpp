#include "jp/ggaf/lib/actor/DefaultMorphMeshActor.h"

#include "jp/ggaf/lib/util/StgUtil.h"
#include "jp/ggaf/lib/util/WorldCollisionChecker.h"



using namespace GgafLib;

DefaultMorphMeshActor::DefaultMorphMeshActor(const char* prm_name, const char* prm_model) :
    GgafDx::MorphMeshActor(prm_name,
                         prm_model,
                         "DefaultMorphMeshEffect",
                         "DefaultMorphMeshTechnique",
                         UTIL::createCollisionChecker(this) ) {

    _class_name = "DefaultMorphMeshActor";
    _pColliCollisionChecker = (WorldCollisionChecker*)_pChecker;
}

void DefaultMorphMeshActor::drawHitArea() {
#ifdef MY_DEBUG
    WorldCollisionChecker::drawHitArea(_pColliCollisionChecker);
#endif
}

DefaultMorphMeshActor::~DefaultMorphMeshActor() {
    GGAF_DELETE(_pColliCollisionChecker);
}
