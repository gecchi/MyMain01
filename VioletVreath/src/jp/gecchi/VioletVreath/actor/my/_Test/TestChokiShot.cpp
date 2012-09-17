#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

TestChokiShot::TestChokiShot(const char* prm_name) :
        SingleLaser(prm_name, "TestChokiShot", STATUS(TestChokiShot)) {
    _class_name = "TestChokiShot";
}

void TestChokiShot::initialize() {
    setHitAble(false);
    setAlpha(0.99);
    _pColliChecker->makeCollision(1);
    _pColliChecker->setColliAAB(0, -PX_C(30), -PX_C(30), -PX_C(30),
                                    PX_C(30),  PX_C(30),  PX_C(30));
}

void TestChokiShot::onActive() {
    _pStatus->reset();
    setHitAble(true);
    _pKurokoA->setMvVelo(PX_C(30));
}

void TestChokiShot::processBehavior() {
    _pKurokoA->behave();
}

void TestChokiShot::processJudgement() {
    if (isOutOfUniverse()) {
        sayonara();
    }
}

void TestChokiShot::onHit(GgafActor* prm_pOtherActor) {
    GgafDxGeometricActor* pOther = (GgafDxGeometricActor*)prm_pOtherActor;
    setHitAble(false);
    UTIL::activateExplosionEffectOf(this);
    sayonara();
}

TestChokiShot::~TestChokiShot() {
}