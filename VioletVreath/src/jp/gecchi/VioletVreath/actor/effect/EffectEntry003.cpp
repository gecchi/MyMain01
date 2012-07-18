#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

EffectEntry003::EffectEntry003(const char* prm_name) :
        DefaultSpriteSetActor(prm_name, "Entry003", NULL) {
    _class_name = "EffectEntry003";
//    defineRotMvWorldMatrix(UTIL::setWorldMatrix_RzBxyzMv); //ビルボードRz回転
}

void EffectEntry003::initialize() {
    _pUvFlipper->setFlipMethod(FLIP_ORDER_LOOP, 1);
    _pScaler->forceScaleRange(R_SC(0.0), R_SC(1.0));
    setAlpha(0.99);
}

void EffectEntry003::onActive() {
    setHitAble(false);
    _pUvFlipper->setActivePtnToTop();
    _pScaler->setScale(1);
    _pKurokoA->setFaceAngVelo(AXIS_Z, 4000);
}

void EffectEntry003::processBehavior() {
    if (getActivePartFrame() == 1) {
        _pScaler->intoTargetScaleLinerUntil(R_SC(1.0), 60);
    }
    if (getActivePartFrame() == 120) {
        _pScaler->intoTargetScaleLinerUntil(R_SC(0.0), 60);
    }
    if (getActivePartFrame() == 180) {
        sayonara();
    }
    _pUvFlipper->behave();
    _pKurokoA->behave();
    _pScaler->behave();
}

void EffectEntry003::processJudgement() {
}

void EffectEntry003::onInactive() {
}

EffectEntry003::~EffectEntry003() {
}
