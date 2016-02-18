#include "jp/ggaf/lib/actor/DefaultMassMeshActor.h"

#include "jp/ggaf/lib/util/CollisionChecker3D.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxScaler.h"
#ifdef MY_DEBUG
#include "jp/ggaf/lib/actor/ColliAABoxActor.h"
#include "jp/ggaf/lib/actor/ColliAAPrismActor.h"
#include "jp/ggaf/lib/actor/ColliAAPyramidActor.h"
#include "jp/ggaf/lib/actor/ColliSphereActor.h"
#endif

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;

DefaultMassMeshActor::DefaultMassMeshActor(const char* prm_name, const char* prm_model, GgafStatus* prm_pStat) :
    GgafDxMassMeshActor(prm_name,
                       prm_model,
                       "DefaultMassMeshEffect",
                       "DefaultMassMeshTechnique",
                       prm_pStat,
                       NEW CollisionChecker3D(this) ) {
    _class_name = "DefaultMassMeshActor";
    _pColliChecker = (CollisionChecker3D*)_pChecker;
}

void DefaultMassMeshActor::drawHitArea() {
#ifdef MY_DEBUG
    ColliAABoxActor::get()->drawHitarea(_pColliChecker); ColliAAPrismActor::get()->drawHitarea(_pColliChecker); ColliAAPyramidActor::get()->drawHitarea(_pColliChecker); ColliSphereActor::get()->drawHitarea(_pColliChecker);
#endif
}

DefaultMassMeshActor::~DefaultMassMeshActor() {
    GGAF_DELETE(_pColliChecker);
}
