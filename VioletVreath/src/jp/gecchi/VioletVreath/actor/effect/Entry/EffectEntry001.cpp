#include "stdafx.h"
#include "EffectEntry001.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxScaler.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

EffectEntry001::EffectEntry001(const char* prm_name) :
        EffectEntry(prm_name, "EffectEntry001") {
    _class_name = "EffectEntry001";
    effectBlendOne();
}

void EffectEntry001::initialize() {
    EffectEntry::initialize();
}

void EffectEntry001::onActive() {
    EffectEntry::onActive();
    pScaler_->forceRange(1, 20000);
    setScale(pScaler_->getBottom());
    setFaceAng(D0ANG, D0ANG, D0ANG);
    getKuroko()->setFaceAngVelo(3000, 5000, 7000);
}

void EffectEntry001::processBehavior() {
    EffectEntry::processBehavior();
    getKuroko()->behave();
}

EffectEntry001::~EffectEntry001() {
}
