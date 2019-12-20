#include "jp/ggaf/lib/actor/DefaultSkinAniMeshActor.h"

#include "jp/ggaf/lib/util/StgUtil.h"
#include "jp/ggaf/lib/util/CollisionChecker.h"

using namespace GgafLib;

DefaultSkinAniMeshActor::DefaultSkinAniMeshActor(const char* prm_name,
                                                 const char* prm_model) :

                                         GgafDx::SkinAniMeshActor(prm_name,
                                                                  prm_model,
                                                                  "DefaultSkinAniMeshEffect",
                                                                  "DefaultSkinAniMeshTechnique",
                                                                  UTIL::createChecker(this) ) {
    _class_name = "DefaultSkinAniMeshActor";
    _pColliChecker = (CollisionChecker*)_pChecker;
}

void DefaultSkinAniMeshActor::drawHitArea() {
#ifdef MY_DEBUG
    CollisionChecker::drawHitArea(_pColliChecker);
#endif
}

DefaultSkinAniMeshActor::~DefaultSkinAniMeshActor() {
    GGAF_DELETE(_pColliChecker);
}
