#include "TestPaShot.h"

#include "jp/ggaf/dx/actor/supporter/LocusVehicle.h"
#include "jp/ggaf/dx/actor/supporter/SeTransmitterForActor.h"
#include "jp/ggaf/lib/util/WorldCollisionChecker.h"
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
    WorldCollisionChecker* pChecker = getWorldCollisionChecker();
    pChecker->addCollisionArea(1);
    pChecker->setColliAACube(0, PX_C(60));
}

void TestPaShot::onActive() {
    getStatus()->reset();
    setHitAble(true);
    getLocusVehicle()->setMvVelo(PX_C(30));
}

void TestPaShot::processBehavior() {
    getLocusVehicle()->behave();
}

void TestPaShot::processJudgement() {
    if (isOutOfSpacetime()) {
        sayonara();
    }
}

void TestPaShot::onHit(const GgafCore::Checker* prm_pThisHitChecker, const GgafCore::Checker* prm_pOppHitChecker) {
    setHitAble(false);
    UTIL::activateCommonEffectOf(this, STAT_ExplosionEffectKind);
    sayonara();
}

TestPaShot::~TestPaShot() {
}
