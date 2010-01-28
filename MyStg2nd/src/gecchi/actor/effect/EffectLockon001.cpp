#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

EffectLockOn001::EffectLockOn001(const char* prm_name) : DefaultSpriteSetActor(prm_name, "8/LockOn001") {
    _class_name = "EffectLockOn001";
    setTechnique("DestBlendOne"); //‰ÁŽZ‡¬
    inactivateImmediately();
}

void EffectLockOn001::initialize() {
    setAnimationMethod(ORDER_LOOP, 3);
    setAnimationPatternRenge(0, 15);
    setHitAble(false);
    enableBillboarding();
    _pScaler->setScaleRange(100000, 5000);
}

void EffectLockOn001::onActive() {
    resetActivAnimationPattern();
    setAlpha(1.0);
    _pScaler->setScale(100000);
    _pScaler->intoTargetScaleLinerUntil(10000, 100);
    _pMover->setFaceAngleVelocity(AXIS_Z, 1000);
}

void EffectLockOn001::processBehavior() {

    addNextAnimationFrame();
    _pMover->behave();
    _pScaler->behave();
}

void EffectLockOn001::processJudgement() {
//    if (_fAlpha < 0) {
//        inactivate();
//    }
}

EffectLockOn001::~EffectLockOn001() {
}
