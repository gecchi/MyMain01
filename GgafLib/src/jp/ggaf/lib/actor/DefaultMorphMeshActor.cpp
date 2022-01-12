#include "jp/ggaf/lib/actor/DefaultMorphMeshActor.h"

#include "jp/ggaf/lib/util/StgUtil.h"
#include "jp/ggaf/lib/util/CollisionChecker.h"



using namespace GgafLib;

DefaultMorphMeshActor::DefaultMorphMeshActor(const char* prm_name, const char* prm_model) :
    GgafDx::MorphMeshActor(prm_name,
                         prm_model,
                         "DefaultMorphMeshEffect",
                         "DefaultMorphMeshTechnique",
                         UTIL::createChecker(this) ) {

    _class_name = "DefaultMorphMeshActor";
    _pColliChecker = (CollisionChecker*)_pChecker;
}

void DefaultMorphMeshActor::drawHitArea() {
#ifdef MY_DEBUG
    CollisionChecker::drawHitArea(_pColliChecker);
#endif
}

DefaultMorphMeshActor::~DefaultMorphMeshActor() {
    GGAF_DELETE(_pColliChecker);
}
