#include "EffectBlink003.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxScaler.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"

using namespace GgafCore;
using namespace GgafDxCore;
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
    pScaler_->forceRange(1, 128000);
    setScale(pScaler_->getBottom());
    setFaceAngZero();
    getKuroko()->setRollPitchYawFaceAngVelo(11000,7000,5000);
}

void EffectBlink003::processBehavior() {
    EffectBlink::processBehavior();
    getKuroko()->behave();
}

EffectBlink003::~EffectBlink003() {
}
