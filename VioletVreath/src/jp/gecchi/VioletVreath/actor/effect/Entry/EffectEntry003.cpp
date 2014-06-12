#include "stdafx.h"
#include "EffectEntry003.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxScaler.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

EffectEntry003::EffectEntry003(const char* prm_name) :
        EffectEntry(prm_name, "EffectEntry003") {
    _class_name = "EffectEntry003";
    effectBlendOne();
}

void EffectEntry003::initialize() {
    EffectEntry::initialize();
}

void EffectEntry003::onActive() {
    EffectEntry::onActive();
    pScaler_->forceRange(1, 128000);
    setScale(pScaler_->getBottom());
    setFaceAng(D0ANG, D0ANG, D0ANG);
    getKuroko()->setFaceAngVelo(11000,5000,7000);
}

void EffectEntry003::processBehavior() {
    EffectEntry::processBehavior();
    getKuroko()->behave();
}

EffectEntry003::~EffectEntry003() {
}
