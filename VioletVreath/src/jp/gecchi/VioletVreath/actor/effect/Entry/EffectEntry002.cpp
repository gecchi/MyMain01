#include "stdafx.h"
#include "EffectEntry002.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxScaler.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

EffectEntry002::EffectEntry002(const char* prm_name) :
        EffectEntry(prm_name, "EffectEntry002") {
    _class_name = "EffectEntry002";
    pScaler_ = NEW GgafDxScaler(this);
    effectBlendOne();
//    defineRotMvWorldMatrix(UTIL::setWorldMatrix_RzBxyzMv); //ビルボードRz回転
}

void EffectEntry002::initialize() {
    EffectEntry::initialize();
    //_pUvFlipper->exec(FLIP_ORDER_LOOP, 1);
    pScaler_->forceRange(R_SC(0.0), R_SC(1.0));
    setAlpha(0.99);
}

void EffectEntry002::onActive() {
    EffectEntry::onActive();
    //_pUvFlipper->setActivePtnToTop();
    pScaler_->setScale(1);
    _pKuroko->setFaceAngVelo(AXIS_Z, 4000);
}

void EffectEntry002::processBehavior() {
    EffectEntry::processBehavior();
    if (getActiveFrame() == 1) {
        pScaler_->scaleLinerUntil(R_SC(1.0), 60);
    }
    if (getActiveFrame() == 120) {
        pScaler_->scaleLinerUntil(R_SC(0.0), 60);
    }
    if (getActiveFrame() == 180) {
        sayonara();
    }
    //_pUvFlipper->behave();
    _pKuroko->behave();
    pScaler_->behave();
}

EffectEntry002::~EffectEntry002() {
    GGAF_DELETE(pScaler_);
}
