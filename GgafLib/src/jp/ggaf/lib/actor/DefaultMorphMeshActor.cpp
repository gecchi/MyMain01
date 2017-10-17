#include "jp/ggaf/lib/actor/DefaultMorphMeshActor.h"

#include "jp/ggaf/lib/util/StgUtil.h"
#include "jp/ggaf/lib/util/CollisionChecker.h"
#ifdef MY_DEBUG
#include "jp/ggaf/lib/actor/ColliAABoxActor.h"
#include "jp/ggaf/lib/actor/ColliAAPrismActor.h"
#include "jp/ggaf/lib/actor/ColliAAPyramidActor.h"
#include "jp/ggaf/lib/actor/ColliSphereActor.h"
#endif

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;

DefaultMorphMeshActor::DefaultMorphMeshActor(const char* prm_name, const char* prm_model_id, GgafStatus* prm_pStat) :
    GgafDxMorphMeshActor(prm_name,
                         prm_model_id,
                         "DefaultMorphMeshEffect",
                         "DefaultMorphMeshTechnique",
                         prm_pStat,
                         UTIL::createChecker(this) ) {

    _class_name = "DefaultMorphMeshActor";
    _pColliChecker = (CollisionChecker*)_pChecker;
}

void DefaultMorphMeshActor::drawHitArea() {
#ifdef MY_DEBUG
    ColliAABoxActor::get()->drawHitarea(_pColliChecker); ColliAAPrismActor::get()->drawHitarea(_pColliChecker); ColliAAPyramidActor::get()->drawHitarea(_pColliChecker); ColliSphereActor::get()->drawHitarea(_pColliChecker);
#endif
}

DefaultMorphMeshActor::~DefaultMorphMeshActor() {
    GGAF_DELETE(_pColliChecker);
}
