#include "jp/ggaf/lib/actor/DefaultSkinAniMeshActor.h"

#include "jp/ggaf/lib/util/StgUtil.h"
#include "jp/ggaf/lib/util/WorldCollisionChecker.h"

using namespace GgafLib;

DefaultSkinAniMeshActor::DefaultSkinAniMeshActor(const char* prm_name,
                                                 const char* prm_model) :

                                         GgafDx::SkinAniMeshActor(prm_name,
                                                                  prm_model,
                                                                  "DefaultSkinAniMeshEffect",
                                                                  "DefaultSkinAniMeshTechnique") {
    _class_name = "DefaultSkinAniMeshActor";
    _pWorldCollisionChecker = (WorldCollisionChecker*)getChecker();
}

void DefaultSkinAniMeshActor::drawHitArea() {
#ifdef MY_DEBUG
    WorldCollisionChecker::drawHitArea(_pWorldCollisionChecker);
#endif
}

GgafDx::CollisionChecker* DefaultSkinAniMeshActor::createChecker(kind_t prm_kind) {
    return UTIL::createCollisionChecker(this, prm_kind);
}

DefaultSkinAniMeshActor::~DefaultSkinAniMeshActor() {
}
