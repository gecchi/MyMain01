#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

EffectEntry001::EffectEntry001(const char* prm_name) :
        DefaultMeshSetActor(prm_name, "EffectEntry001", nullptr) {
    _class_name = "EffectEntry001";
//    defineRotMvWorldMatrix(UTIL::setWorldMatrix_RzBxyzMv); //ビルボードRz回転
}

void EffectEntry001::initialize() {
    _pScaler->forceScaleRange(R_SC(0.0), R_SC(1.0));
    setAlpha(0.99);
}

void EffectEntry001::onActive() {
    setHitAble(false);
    _pScaler->setScale(1);
    _pKurokoA->setFaceAngVelo(AXIS_Z, 4000);
}

void EffectEntry001::processBehavior() {
    if (getActivePartFrame() == 1) {
        _pScaler->intoTargetScaleLinerUntil(R_SC(5.0), 60);
    }
    if (getActivePartFrame() == 120) {
        _pScaler->intoTargetScaleLinerUntil(R_SC(0.0), 60);
    }
    if (getActivePartFrame() == 180) {
        sayonara();
    }
    _pKurokoA->behave();
    _pScaler->behave();
}

void EffectEntry001::processJudgement() {
}

void EffectEntry001::onInactive() {
}

EffectEntry001::~EffectEntry001() {
}
