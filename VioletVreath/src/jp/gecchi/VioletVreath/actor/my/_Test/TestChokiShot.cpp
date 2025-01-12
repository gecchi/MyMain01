#include "TestChokiShot.h"

#include "jp/ggaf/dx/actor/supporter/LocusVehicle.h"
#include "jp/ggaf/dx/actor/supporter/SeTransmitterForActor.h"
#include "jp/ggaf/lib/util/WorldCollisionChecker.h"
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
    WorldCollisionChecker* pChecker = getWorldCollisionChecker();
    pChecker->addCollisionArea(1);
    pChecker->setColliAACube(0, PX_C(60));
}

void TestChokiShot::onActive() {
    getStatus()->reset();
    setHitAble(true);
    getLocusVehicle()->setMvVelo(PX_C(30));
}

void TestChokiShot::processBehavior() {
    getLocusVehicle()->behave();
}

void TestChokiShot::processJudgement() {
    if (isOutOfSpacetime()) {
        sayonara();
    }
}

void TestChokiShot::onHit(const GgafCore::Checker* prm_pThisHitChecker, const GgafCore::Checker* prm_pOppHitChecker) {
    setHitAble(false);
    UTIL::activateCommonEffectOf(this, STAT_ExplosionEffectKind);
    sayonara();
}

TestChokiShot::~TestChokiShot() {
}
