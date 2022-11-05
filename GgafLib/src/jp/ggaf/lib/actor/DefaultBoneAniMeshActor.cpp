#include "jp/ggaf/lib/actor/DefaultBoneAniMeshActor.h"

#include "jp/ggaf/lib/util/StgUtil.h"
#include "jp/ggaf/lib/util/WorldCollisionChecker.h"

using namespace GgafLib;

DefaultBoneAniMeshActor::DefaultBoneAniMeshActor(const char* prm_name,
                                         const char* prm_model) :

                                         GgafDx::BoneAniMeshActor(prm_name,
                                                              prm_model,
                                                              "DefaultBoneAniMeshEffect",
                                                              "DefaultBoneAniMeshTechnique",
                                                              UTIL::createCollisionChecker(this) ) {
    _class_name = "DefaultBoneAniMeshActor";
    _pColliCollisionChecker = (WorldCollisionChecker*)_pChecker;
}

void DefaultBoneAniMeshActor::drawHitArea() {
#ifdef MY_DEBUG
    WorldCollisionChecker::drawHitArea(_pColliCollisionChecker);
#endif
}

DefaultBoneAniMeshActor::~DefaultBoneAniMeshActor() {
    GGAF_DELETE(_pColliCollisionChecker);
}
