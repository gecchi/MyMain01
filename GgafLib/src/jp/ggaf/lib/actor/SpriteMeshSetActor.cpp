#include "jp/ggaf/lib/actor/SpriteMeshSetActor.h"

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

SpriteMeshSetActor::SpriteMeshSetActor(const char* prm_name, const char* prm_model, GgafStatus* prm_pStat) :
    GgafDxSpriteMeshSetActor(prm_name,
                             prm_model,
                             prm_pStat,
                             UTIL::createChecker(this) ) {

    _class_name = "SpriteMeshSetActor";
    _pColliChecker = (CollisionChecker*)_pChecker;
}

void SpriteMeshSetActor::drawHitArea() {
#ifdef MY_DEBUG
    ColliAABoxActor::get()->drawHitarea(_pColliChecker); ColliAAPrismActor::get()->drawHitarea(_pColliChecker); ColliAAPyramidActor::get()->drawHitarea(_pColliChecker); ColliSphereActor::get()->drawHitarea(_pColliChecker);
#endif
}

SpriteMeshSetActor::~SpriteMeshSetActor() {
    GGAF_DELETE(_pColliChecker);
}

