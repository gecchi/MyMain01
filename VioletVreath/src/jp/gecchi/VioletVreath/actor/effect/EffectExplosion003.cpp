#include "EffectExplosion003.h"

#include "jp/ggaf/dx/actor/supporter/Scaler.h"
#include "jp/ggaf/dx/actor/supporter/LocusVehicle.h"
#include "jp/ggaf/dx/actor/supporter/UvFlipper.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"

using namespace GgafLib;
using namespace VioletVreath;

EffectExplosion003::EffectExplosion003(const char* prm_name) :
        VvEffectActor<DefaultPointSpriteSetActor>(prm_name, "EffectExplosion003") {
    _class_name = "EffectExplosion003";
    setHitAble(false);
}

int EffectExplosion003::isOutOfView() {
    //‰æ–ÊŠO”»’è–³‚µ
    return 0;
}

void EffectExplosion003::initialize() {

}

void EffectExplosion003::onActive() {
    setScale(0);
    getScaler()->transitionAcceUntilVelo(R_SC(0.01) , R_SC(0.1), -R_SC(0.001));
    getUvFlipper()->exec(FLIP_ORDER_LOOP, 1);
    setRzRyFaceAng(getLocusVehicle()->getRzMvAng(), getLocusVehicle()->getRyMvAng());
}

void EffectExplosion003::processBehavior() {
    getUvFlipper()->behave();
    getLocusVehicle()->behave();
    getScaler()->behave();
}

void EffectExplosion003::processJudgement() {
    if (!getScaler()->isTransitioning()) {
        sayonara();
    }
}

EffectExplosion003::~EffectExplosion003() {
}
