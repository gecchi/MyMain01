#include "jp/ggaf/lib/actor/DefaultSpriteActor.h"

#include "jp/ggaf/lib/util/StgUtil.h"
#include "jp/ggaf/lib/util/CollisionChecker.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;

DefaultSpriteActor::DefaultSpriteActor(const char* prm_name, const char* prm_model_id, GgafStatus* prm_pStat) :
    GgafDxSpriteActor(prm_name,
                      prm_model_id,
                      "DefaultSpriteEffect",
                      "DefaultSpriteTechnique",
                      prm_pStat,
                      UTIL::createChecker(this) ) {
    _class_name = "DefaultSpriteActor";
    _pColliChecker = (CollisionChecker*)_pChecker;
    setZWriteEnable(false);
}

void DefaultSpriteActor::drawHitArea() {
#ifdef MY_DEBUG
    CollisionChecker::drawHitArea(_pColliChecker);
#endif
}

DefaultSpriteActor::~DefaultSpriteActor() {
    GGAF_DELETE(_pColliChecker);
}

