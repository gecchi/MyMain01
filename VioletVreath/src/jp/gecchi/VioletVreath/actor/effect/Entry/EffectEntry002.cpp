#include "stdafx.h"
#include "EffectEntry002.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxScaler.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoA.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

EffectEntry002::EffectEntry002(const char* prm_name) :
        EffectEntry(prm_name, "EffectEntry002") {
    _class_name = "EffectEntry002";
    effectBlendOne();
//    defineRotMvWorldMatrix(UTIL::setWorldMatrix_RzBxyzMv); //ビルボードRz回転
}

void EffectEntry002::initialize() {
    EffectEntry::initialize();
    //_pUvFlipper->exec(FLIP_ORDER_LOOP, 1);
    _pScaler->forceRange(R_SC(0.0), R_SC(1.0));
    setAlpha(0.99);
}

void EffectEntry002::onActive() {
    EffectEntry::onActive();
    //_pUvFlipper->setActivePtnToTop();
    _pScaler->setScale(1);
    _pKurokoA->setFaceAngVelo(AXIS_Z, 4000);
}

void EffectEntry002::processBehavior() {
    EffectEntry::processBehavior();
    if (getActiveFrame() == 1) {
        _pScaler->scaleLinerUntil(R_SC(1.0), 60);
    }
    if (getActiveFrame() == 120) {
        _pScaler->scaleLinerUntil(R_SC(0.0), 60);
    }
    if (getActiveFrame() == 180) {
        sayonara();
    }
    //_pUvFlipper->behave();
    _pKurokoA->behave();
    _pScaler->behave();
}

EffectEntry002::~EffectEntry002() {
}
