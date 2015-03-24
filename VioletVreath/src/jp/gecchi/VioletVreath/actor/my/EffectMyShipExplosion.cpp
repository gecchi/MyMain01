#include "EffectMyShipExplosion.h"

#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxUvFlipper.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxScaler.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/MyShipScene.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

EffectMyShipExplosion::EffectMyShipExplosion(const char* prm_name) :
        DefaultSpriteSetActor(prm_name, "EffectExplosion001", nullptr) {
    _class_name = "EffectMyShipExplosion";
    pScaler_ = NEW GgafDxScaler(this);
    effectBlendOne(); //‰ÁŽZ‡¬
    defineRotMvWorldMatrix(UTIL::setWorldMatrix_RzBxyzMv);
}

void EffectMyShipExplosion::initialize() {
    getUvFlipper()->setFlipPtnRange(0, 15);
    setHitAble(false);
}

void EffectMyShipExplosion::onActive() {
    GgafDxUvFlipper* pUvFlipper = getUvFlipper();
    pUvFlipper->setActivePtnToTop();
    pUvFlipper->exec(FLIP_ORDER_NOLOOP, 20);
    positionAs(P_MYSHIP);
    setAlpha(0.99);
    setScale(8000);
    getKuroko()->setFaceAngVelo(AXIS_Z, 2000);
}

void EffectMyShipExplosion::processBehavior() {
    _alpha -= 0.01;
    positionAs(P_MYSHIP);
    getUvFlipper()->behave();
    getKuroko()->behave();
    pScaler_->behave();
}

void EffectMyShipExplosion::processJudgement() {
    if (getUvFlipper()->_uvflip_method == NOT_ANIMATED) {
        inactivate();
    }
}

EffectMyShipExplosion::~EffectMyShipExplosion() {
    GGAF_DELETE(pScaler_);
}
