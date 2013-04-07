#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

EffectEntry002::EffectEntry002(const char* prm_name) :
        DefaultMeshSetActor(prm_name, "EffectEntry002", nullptr) {
    _class_name = "EffectEntry002";
//    defineRotMvWorldMatrix(UTIL::setWorldMatrix_RzBxyzMv); //ビルボードRz回転
}

void EffectEntry002::initialize() {
    //_pUvFlipper->exec(FLIP_ORDER_LOOP, 1);
    _pScaler->forceScaleRange(R_SC(0.0), R_SC(1.0));
    setAlpha(0.99);
}

void EffectEntry002::onActive() {
    setHitAble(false);
    //_pUvFlipper->setActivePtnToTop();
    _pScaler->setScale(1);
    _pKurokoA->setFaceAngVelo(AXIS_Z, 4000);
}

void EffectEntry002::processBehavior() {
    if (getActiveFrame() == 1) {
        _pScaler->intoTargetScaleLinerUntil(R_SC(1.0), 60);
    }
    if (getActiveFrame() == 120) {
        _pScaler->intoTargetScaleLinerUntil(R_SC(0.0), 60);
    }
    if (getActiveFrame() == 180) {
        sayonara();
    }
    //_pUvFlipper->behave();
    _pKurokoA->behave();
    _pScaler->behave();
}

void EffectEntry002::processJudgement() {
}

void EffectEntry002::onInactive() {
}

EffectEntry002::~EffectEntry002() {
}
