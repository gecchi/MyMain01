#include "TestPa.h"

#include "jp/ggaf/dx/actor/supporter/SeTransmitterForActor.h"
#include "jp/ggaf/dx/actor/supporter/LocusVehicle.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"

using namespace GgafLib;
using namespace VioletVreath;

TestPa::TestPa(const char* prm_name)
      : TestEnemy(prm_name, "TestPa", StatusReset(TestPa)) {
    _class_name = "TestPa";
}

void TestPa::onActive() {
    getStatus()->reset();
}

void TestPa::processBehavior() {
    getLocusVehicle()->behave();
    dispStamina();
}

void TestPa::processJudgement() {
    if (isOutOfSpacetime()) {
        sayonara();
    }
}

void TestPa::onHit(const GgafCore::Checker* prm_pOtherChecker, const GgafCore::Actor* prm_pOtherActor) {
    bool is_stamina_zero = performEnemyHit((const GgafDx::GeometricActor*)prm_pOtherActor);
    if (is_stamina_zero) {
        //破壊された時(スタミナ <= 0)
        sayonara();
    } else {
        //破壊されなかった時(スタミナ > 0)
    }
}

TestPa::~TestPa() {
}
