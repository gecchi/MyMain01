#include "EffectBlink001.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxScaler.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

EffectBlink001::EffectBlink001(const char* prm_name) :
        EffectBlink(prm_name, "EffectBlink001") {
    _class_name = "EffectBlink001";
    effectBlendOne();
    setZEnable(false);
    setZWriteEnable(false);
}

void EffectBlink001::initialize() {
    EffectBlink::initialize();
}

void EffectBlink001::onActive() {
    EffectBlink::onActive();
    pScaler_->forceRange(1, R_SC(40.0));
    setScale(pScaler_->getBottom());
    setFaceAngZero();
    getKuroko()->setRollPitchYawFaceAngVelo(3000, 11000, 7000);
}

void EffectBlink001::processBehavior() {
    EffectBlink::processBehavior();
    getKuroko()->behave();
}

EffectBlink001::~EffectBlink001() {
}
