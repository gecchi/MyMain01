#include "jp/ggaf/lib/actor/DefaultPointSpriteSetActor.h"

#include "jp/ggaf/lib/util/StgUtil.h"
#include "jp/ggaf/lib/util/CollisionChecker.h"

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
    CollisionChecker::drawHitArea(_pColliChecker);
#endif
}

DefaultPointSpriteSetActor::~DefaultPointSpriteSetActor() {
    GGAF_DELETE(_pColliChecker);
}
