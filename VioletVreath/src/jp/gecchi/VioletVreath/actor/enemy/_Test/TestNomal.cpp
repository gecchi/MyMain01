#include "TestNomal.h"

#include "jp/ggaf/dx/actor/supporter/SeTransmitterForActor.h"
#include "jp/ggaf/dx/actor/supporter/LocusVehicle.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"

using namespace GgafLib;
using namespace VioletVreath;

TestNomal::TestNomal(const char* prm_name)
      : TestEnemy(prm_name, "TestNomal", StatusReset(TestNomal)) {
    _class_name = "TestNomal";
}

void TestNomal::onActive() {
    getStatus()->reset();
}

void TestNomal::processBehavior() {
    getLocusVehicle()->behave();
    dispStamina();
}

void TestNomal::processJudgement() {
    if (isOutOfSpacetime()) {
        sayonara();
    }
}

void TestNomal::onHit(const GgafCore::Checker* prm_pThisHitChecker, const GgafCore::Checker* prm_pOppHitChecker) {
_TRACE_(FUNC_NAME<<" !");

    bool is_stamina_zero = performEnemyHit(prm_pOppHitChecker);
    if (is_stamina_zero) {
        //破壊された時(スタミナ <= 0)
        //sayonara();
    } else {
        //破壊されなかった時(スタミナ > 0)
    }

    getStatus()->reset();
}

TestNomal::~TestNomal() {
}
