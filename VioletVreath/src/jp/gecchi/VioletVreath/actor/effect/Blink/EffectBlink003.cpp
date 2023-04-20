#include "EffectBlink003.h"

#include "jp/ggaf/dx/actor/supporter/Scaler.h"
#include "jp/ggaf/dx/actor/supporter/LocoVehicle.h"



using namespace GgafLib;
using namespace VioletVreath;

EffectBlink003::EffectBlink003(const char* prm_name) :
        EffectBlink(prm_name, "EffectBlink003") {
    _class_name = "EffectBlink003";
    effectBlendOne();
    setZWriteEnable(false);
}

void EffectBlink003::initialize() {
    EffectBlink::initialize();
}

void EffectBlink003::onActive() {
    EffectBlink::onActive();
    getScaler()->setRange(1, 128000);
    setScale(getScaler()->getBottom());
    setFaceAngZero();
    getLocoVehicle()->setRollPitchYawFaceAngVelo(11000,7000,5000);
}

void EffectBlink003::processBehavior() {
    EffectBlink::processBehavior();
    getLocoVehicle()->behave();
}

EffectBlink003::~EffectBlink003() {
}
