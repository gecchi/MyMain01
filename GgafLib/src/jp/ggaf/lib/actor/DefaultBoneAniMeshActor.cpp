#include "jp/ggaf/lib/actor/DefaultBoneAniMeshActor.h"

#include "jp/ggaf/lib/util/StgUtil.h"
#include "jp/ggaf/lib/util/WorldCollisionChecker.h"

using namespace GgafLib;

DefaultBoneAniMeshActor::DefaultBoneAniMeshActor(
                                         const char* prm_name,
                                         const char* prm_model) :

                                         GgafDx::BoneAniMeshActor(prm_name,
                                                                  prm_model,
                                                                  "DefaultBoneAniMeshEffect",
                                                                  "DefaultBoneAniMeshTechnique") {
    _class_name = "DefaultBoneAniMeshActor";
    _pWorldCollisionChecker = (WorldCollisionChecker*)getChecker();
}

void DefaultBoneAniMeshActor::drawHitArea() {
#ifdef MY_DEBUG
    WorldCollisionChecker::drawHitArea(_pWorldCollisionChecker);
#endif
}
GgafDx::CollisionChecker* DefaultBoneAniMeshActor::createChecker() {
    return UTIL::createCollisionChecker(this);
}
DefaultBoneAniMeshActor::~DefaultBoneAniMeshActor() {
}
