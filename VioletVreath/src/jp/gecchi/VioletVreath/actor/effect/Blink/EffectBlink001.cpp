#include "EffectBlink001.h"

#include "jp/ggaf/dx/actor/supporter/Scaler.h"
#include "jp/ggaf/dx/actor/supporter/VecVehicle.h"



using namespace GgafLib;
using namespace VioletVreath;

EffectBlink001::EffectBlink001(const char* prm_name) :
        EffectBlink(prm_name, "EffectBlink001") {
    _class_name = "EffectBlink001";
    effectBlendOne();
    setZWriteEnable(false);
}

void EffectBlink001::initialize() {
    EffectBlink::initialize();
}

void EffectBlink001::onActive() {
    EffectBlink::onActive();
    getScaler()->setRange(1, R_SC(40.0));
    setScale(getScaler()->getBottom());
    setFaceAngZero();
    getVecVehicle()->setRollPitchYawFaceAngVelo(3000, 11000, 7000);
}

void EffectBlink001::processBehavior() {
    EffectBlink::processBehavior();
    getVecVehicle()->behave();
}

EffectBlink001::~EffectBlink001() {
}
