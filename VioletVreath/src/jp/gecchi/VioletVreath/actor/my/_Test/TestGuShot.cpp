#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

TestGuShot::TestGuShot(const char* prm_name) :
        SingleLaser(prm_name, "TestGuShot", STATUS(TestGuShot)) {
    _class_name = "TestGuShot";
}

void TestGuShot::initialize() {
    setHitAble(false);
    setAlpha(0.99);
    _pColliChecker->makeCollision(1);
    _pColliChecker->setColliAAB(0, -PX_C(30), -PX_C(30), -PX_C(30),
                                    PX_C(30),  PX_C(30),  PX_C(30));
}

void TestGuShot::onActive() {
    _pStatus->reset();
    setHitAble(true);
    _pKurokoA->setMvVelo(PX_C(30));
}

void TestGuShot::processBehavior() {
    _pKurokoA->behave();
}

void TestGuShot::processJudgement() {
    if (isOutOfUniverse()) {
        sayonara();
    }
}

void TestGuShot::onHit(GgafActor* prm_pOtherActor) {
    GgafDxGeometricActor* pOther = (GgafDxGeometricActor*)prm_pOtherActor;
    setHitAble(false);
    UTIL::activateExplosionEffectOf(this);
    sayonara();
}

TestGuShot::~TestGuShot() {
}
