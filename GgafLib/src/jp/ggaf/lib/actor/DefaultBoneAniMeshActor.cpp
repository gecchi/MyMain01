#include "jp/ggaf/lib/actor/DefaultBoneAniMeshActor.h"

#include "jp/ggaf/lib/util/StgUtil.h"
#include "jp/ggaf/lib/util/CollisionChecker.h"

using namespace GgafLib;

DefaultBoneAniMeshActor::DefaultBoneAniMeshActor(const char* prm_name,
                                         const char* prm_model) :

                                         GgafDx::BoneAniMeshActor(prm_name,
                                                              prm_model,
                                                              "DefaultBoneAniMeshEffect",
                                                              "DefaultBoneAniMeshTechnique",
                                                              UTIL::createChecker(this) ) {
    _class_name = "DefaultBoneAniMeshActor";
    _pColliChecker = (CollisionChecker*)_pChecker;
}

void DefaultBoneAniMeshActor::drawHitArea() {
#ifdef MY_DEBUG
    CollisionChecker::drawHitArea(_pColliChecker);
#endif
}

DefaultBoneAniMeshActor::~DefaultBoneAniMeshActor() {
    GGAF_DELETE(_pColliChecker);
}
