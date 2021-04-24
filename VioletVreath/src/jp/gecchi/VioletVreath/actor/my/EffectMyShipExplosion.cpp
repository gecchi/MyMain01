#include "EffectMyShipExplosion.h"

#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/ggaf/dx/actor/supporter/UvFlipper.h"
#include "jp/ggaf/dx/actor/supporter/Scaler.h"
#include "jp/ggaf/dx/actor/supporter/VecDriver.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/MyShipScene.h"



using namespace GgafLib;
using namespace VioletVreath;

EffectMyShipExplosion::EffectMyShipExplosion(const char* prm_name) :
        DefaultSpriteSetActor(prm_name, "EffectExplosion001") {
    _class_name = "EffectMyShipExplosion";
    effectBlendOne(); //���Z����
    defineRotMvWorldMatrix_Billboard();
}

void EffectMyShipExplosion::initialize() {
    getUvFlipper()->setFlipPtnRange(0, 15);
    setHitAble(false);
}

void EffectMyShipExplosion::onActive() {
    GgafDx::UvFlipper* pUvFlipper = getUvFlipper();
    pUvFlipper->setActivePtnToTop();
    pUvFlipper->exec(FLIP_ORDER_NOLOOP, 20);
    setPositionAt(pMYSHIP);
    setCullingDraw(false);
    setScale(8000);
    getVecDriver()->setFaceAngVelo(AXIS_Z, 2000);
}

void EffectMyShipExplosion::processBehavior() {
    _alpha -= 0.01;
    setPositionAt(pMYSHIP);
    getUvFlipper()->behave();
    getVecDriver()->behave();
    getScaler()->behave();

    if (getUvFlipper()->_uvflip_method == NOT_ANIMATED) {
        inactivate();
    }
}

EffectMyShipExplosion::~EffectMyShipExplosion() {
}
