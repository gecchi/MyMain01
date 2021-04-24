#include "TestPaShot.h"

#include "jp/ggaf/dx/actor/supporter/VecDriver.h"
#include "jp/ggaf/dx/actor/supporter/SeTransmitterForActor.h"
#include "jp/ggaf/lib/util/CollisionChecker.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"



using namespace GgafLib;
using namespace VioletVreath;

TestPaShot::TestPaShot(const char* prm_name) :
        VvMyActor<SingleLaser>(prm_name, "TestPaShot", StatusReset(TestPaShot)) {
    _class_name = "TestPaShot";
}

void TestPaShot::initialize() {
    setHitAble(false);
    setCullingDraw(false);
    CollisionChecker* pChecker = getCollisionChecker();
    pChecker->createCollisionArea(1);
    pChecker->setColliAACube(0, PX_C(60));
}

void TestPaShot::onActive() {
    getStatus()->reset();
    setHitAble(true);
    getVecDriver()->setMvVelo(PX_C(30));
}

void TestPaShot::processBehavior() {
    getVecDriver()->behave();
}

void TestPaShot::processJudgement() {
    if (isOutOfSpacetime()) {
        sayonara();
    }
}

void TestPaShot::onHit(const GgafCore::Actor* prm_pOtherActor) {
    setHitAble(false);
    UTIL::activateExplosionEffectOf(this);
    sayonara();
}

TestPaShot::~TestPaShot() {
}
