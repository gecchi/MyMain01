#include "jp/ggaf/lib/actor/DefaultPointSpriteSetActor.h"

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

DefaultPointSpriteSetActor::DefaultPointSpriteSetActor(const char* prm_name, const char* prm_model, GgafStatus* prm_pStat) :
    GgafDxPointSpriteSetActor(prm_name,
                              prm_model,
                              "DefaultPointSpriteSetEffect",
                              "DefaultPointSpriteSetTechnique",
                              prm_pStat,
                              UTIL::createChecker(this) ) {
    _class_name = "DefaultPointSpriteSetActor";
    _pColliChecker = (CollisionChecker*)_pChecker;
}

void DefaultPointSpriteSetActor::drawHitArea() {
#ifdef MY_DEBUG
    ColliAABoxActor::get()->drawHitarea(_pColliChecker); ColliAAPrismActor::get()->drawHitarea(_pColliChecker); ColliAAPyramidActor::get()->drawHitarea(_pColliChecker); ColliSphereActor::get()->drawHitarea(_pColliChecker);
#endif
}

DefaultPointSpriteSetActor::~DefaultPointSpriteSetActor() {
    GGAF_DELETE(_pColliChecker);
}
