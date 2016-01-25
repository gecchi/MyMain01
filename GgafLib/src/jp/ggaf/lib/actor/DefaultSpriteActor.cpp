#include "jp/ggaf/lib/actor/DefaultSpriteActor.h"

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

DefaultSpriteActor::DefaultSpriteActor(const char* prm_name, const char* prm_model_id, GgafStatus* prm_pStat) :
    GgafDxSpriteActor(prm_name,
                      prm_model_id,
                      "DefaultSpriteEffect",
                      "DefaultSpriteTechnique",
                      prm_pStat,
                      NEW CollisionChecker3D(this) ) {
    _class_name = "DefaultSpriteActor";
    _pColliChecker = (CollisionChecker3D*)_pChecker;
    setZWriteEnable(false);
}

void DefaultSpriteActor::drawHitArea() {
#ifdef MY_DEBUG
    ColliAABoxActor::get()->drawHitarea(_pColliChecker); ColliAAPrismActor::get()->drawHitarea(_pColliChecker); ColliAAPyramidActor::get()->drawHitarea(_pColliChecker); ColliSphereActor::get()->drawHitarea(_pColliChecker);
#endif
}

DefaultSpriteActor::~DefaultSpriteActor() {
    GGAF_DELETE(_pColliChecker);
}
