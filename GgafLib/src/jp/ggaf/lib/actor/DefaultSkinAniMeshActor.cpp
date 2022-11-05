#include "jp/ggaf/lib/actor/DefaultSkinAniMeshActor.h"

#include "jp/ggaf/lib/util/StgUtil.h"
#include "jp/ggaf/lib/util/WorldCollisionChecker.h"

using namespace GgafLib;

DefaultSkinAniMeshActor::DefaultSkinAniMeshActor(const char* prm_name,
                                                 const char* prm_model) :

                                         GgafDx::SkinAniMeshActor(prm_name,
                                                                  prm_model,
                                                                  "DefaultSkinAniMeshEffect",
                                                                  "DefaultSkinAniMeshTechnique",
                                                                  UTIL::createCollisionChecker(this) ) {
    _class_name = "DefaultSkinAniMeshActor";
    _pColliCollisionChecker = (WorldCollisionChecker*)_pChecker;
}

void DefaultSkinAniMeshActor::drawHitArea() {
#ifdef MY_DEBUG
    WorldCollisionChecker::drawHitArea(_pColliCollisionChecker);
#endif
}

DefaultSkinAniMeshActor::~DefaultSkinAniMeshActor() {
    GGAF_DELETE(_pColliCollisionChecker);
}
