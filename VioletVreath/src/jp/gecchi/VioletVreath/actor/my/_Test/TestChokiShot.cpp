#include "TestChokiShot.h"

#include "jp/ggaf/dx/actor/supporter/Rikisha.h"
#include "jp/ggaf/dx/actor/supporter/SeTransmitterForActor.h"
#include "jp/ggaf/lib/util/CollisionChecker.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"

using namespace GgafLib;
using namespace VioletVreath;

TestChokiShot::TestChokiShot(const char* prm_name) :
        VvMyActor<SingleLaser>(prm_name, "TestChokiShot", StatusReset(TestChokiShot)) {
    _class_name = "TestChokiShot";
}

void TestChokiShot::initialize() {
    setHitAble(false);
    setCullingDraw(false);
    CollisionChecker* pChecker = getCollisionChecker();
    pChecker->createCollisionArea(1);
    pChecker->setColliAACube(0, PX_C(60));
}

void TestChokiShot::onActive() {
    getStatus()->reset();
    setHitAble(true);
    callRikisha()->setMvVelo(PX_C(30));
}

void TestChokiShot::processBehavior() {
    callRikisha()->behave();
}

void TestChokiShot::processJudgement() {
    if (isOutOfSpacetime()) {
        sayonara();
    }
}

void TestChokiShot::onHit(const GgafCore::Actor* prm_pOtherActor) {
    setHitAble(false);
    UTIL::activateExplosionEffectOf(this);
    sayonara();
}

TestChokiShot::~TestChokiShot() {
}
