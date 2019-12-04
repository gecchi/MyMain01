#include "jp/ggaf/lib/actor/DefaultAniMeshActor.h"

#include "jp/ggaf/lib/util/StgUtil.h"
#include "jp/ggaf/lib/util/CollisionChecker.h"

using namespace GgafLib;

DefaultAniMeshActor::DefaultAniMeshActor(const char* prm_name,
                                         const char* prm_model) :

                                         GgafDx::AniMeshActor(prm_name,
                                                              prm_model,
                                                              "DefaultAniMeshEffect",
                                                              "DefaultAniMeshTechnique",
                                                              UTIL::createChecker(this) ) {
    _class_name = "DefaultAniMeshActor";
    _pColliChecker = (CollisionChecker*)_pChecker;
}

void DefaultAniMeshActor::drawHitArea() {
#ifdef MY_DEBUG
    CollisionChecker::drawHitArea(_pColliChecker);
#endif
}

DefaultAniMeshActor::~DefaultAniMeshActor() {
    GGAF_DELETE(_pColliChecker);
}
