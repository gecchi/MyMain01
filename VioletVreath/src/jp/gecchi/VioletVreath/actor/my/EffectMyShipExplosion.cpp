#include "EffectMyShipExplosion.h"

#include "jp/gecchi/VioletVreath/Caretaker.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/ggaf/dx/actor/supporter/UvFlipper.h"
#include "jp/ggaf/dx/actor/supporter/Scaler.h"
#include "jp/ggaf/dx/actor/supporter/VecVehicle.h"
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
    getVecVehicle()->setFaceAngVelo(AXIS_Z, 2000);
}

void EffectMyShipExplosion::processBehavior() {
    addAlpha(-0.01);
    setPositionAt(pMYSHIP);
    getUvFlipper()->behave();
    getVecVehicle()->behave();
    getScaler()->behave();

    if (getUvFlipper()->_uvflip_method == NOT_ANIMATED) {
        inactivate();
    }
}

EffectMyShipExplosion::~EffectMyShipExplosion() {
}
