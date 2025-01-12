#include "TestNomalShot.h"

#include "jp/ggaf/dx/actor/supporter/LocusVehicle.h"
#include "jp/ggaf/dx/actor/supporter/SeTransmitterForActor.h"
#include "jp/ggaf/lib/util/WorldCollisionChecker.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"

using namespace GgafLib;
using namespace VioletVreath;

TestNomalShot::TestNomalShot(const char* prm_name) :
        VvMyActor<SingleLaser>(prm_name, "TestNomalShot", StatusReset(TestNomalShot)) {
    _class_name = "TestNomalShot";
}

void TestNomalShot::initialize() {
    setHitAble(false);
    setCullingDraw(false);
    WorldCollisionChecker* pChecker = getWorldCollisionChecker();
    pChecker->addCollisionArea(1);
    pChecker->setColliAACube(0, PX_C(60));
}

void TestNomalShot::onActive() {
    getStatus()->reset();
    setHitAble(true);
    getLocusVehicle()->setMvVelo(PX_C(30));
}

void TestNomalShot::processBehavior() {
    getLocusVehicle()->behave();
}

void TestNomalShot::processJudgement() {
    if (isOutOfSpacetime()) {
        sayonara();
    }
}

void TestNomalShot::onHit(const GgafCore::Checker* prm_pThisHitChecker, const GgafCore::Checker* prm_pOppHitChecker) {
    setHitAble(false);
    UTIL::activateCommonEffectOf(this, STAT_ExplosionEffectKind);
    sayonara();
}

TestNomalShot::~TestNomalShot() {
}
