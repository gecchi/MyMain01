#include "jp/ggaf/lib/actor/DefaultPointSpriteActor.h"

#include "jp/ggaf/lib/util/StgUtil.h"
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

DefaultPointSpriteActor::DefaultPointSpriteActor(const char* prm_name, const char* prm_model_id, GgafStatus* prm_pStat) :
    GgafDxPointSpriteActor(prm_name,
                           prm_model_id,
                           "DefaultPointSpriteEffect",
                           "DefaultPointSpriteTechnique",
                           prm_pStat,
                           UTIL::createChecker(this) ) {

    _class_name = "DefaultPointSpriteActor";
    _pColliChecker = (CollisionChecker3D*)_pChecker;
}

void DefaultPointSpriteActor::drawHitArea() {
#ifdef MY_DEBUG
    ColliAABoxActor::get()->drawHitarea(_pColliChecker); ColliAAPrismActor::get()->drawHitarea(_pColliChecker); ColliAAPyramidActor::get()->drawHitarea(_pColliChecker); ColliSphereActor::get()->drawHitarea(_pColliChecker);
#endif
}

DefaultPointSpriteActor::~DefaultPointSpriteActor() {
    GGAF_DELETE(_pColliChecker);
}
