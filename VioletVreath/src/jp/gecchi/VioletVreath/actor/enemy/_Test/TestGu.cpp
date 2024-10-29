#include "TestGu.h"

#include "jp/ggaf/dx/actor/supporter/SeTransmitterForActor.h"
#include "jp/ggaf/dx/actor/supporter/LocusVehicle.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"

using namespace GgafLib;
using namespace VioletVreath;

TestGu::TestGu(const char* prm_name)
      : TestEnemy(prm_name, "TestGu", StatusReset(TestGu)) {
    _class_name = "TestGu";
}

void TestGu::onActive() {
    getStatus()->reset();
}

void TestGu::processBehavior() {
    getLocusVehicle()->behave();
    dispStamina();
}

void TestGu::processJudgement() {
    if (isOutOfSpacetime()) {
        sayonara();
    }
}

void TestGu::onHit(const GgafCore::Checker* prm_pOtherChecker, const GgafCore::Actor* prm_pOtherActor) {
    bool is_stamina_zero = performEnemyHit((const GgafDx::GeometricActor*)prm_pOtherActor);
    if (is_stamina_zero) {
        //破壊された時(スタミナ <= 0)
        sayonara();
    } else {
        //破壊されなかった時(スタミナ > 0)
    }
}

TestGu::~TestGu() {
}
