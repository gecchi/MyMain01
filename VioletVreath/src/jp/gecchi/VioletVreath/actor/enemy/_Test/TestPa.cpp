#include "TestPa.h"

#include "jp/ggaf/dx/actor/supporter/SeTransmitterForActor.h"
#include "jp/ggaf/dx/actor/supporter/LocoVehicle.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"

using namespace GgafLib;
using namespace VioletVreath;

enum {
    SE_DAMAGED   ,
    SE_EXPLOSION ,
};

TestPa::TestPa(const char* prm_name)
      : TestEnemy(prm_name, "TestPa", StatusReset(TestPa)) {
    _class_name = "TestPa";

    GgafDx::SeTransmitterForActor* pSeTx = getSeTransmitter();
    pSeTx->set(SE_DAMAGED  , "SE_ENEMY_DAMAGED_001");
    pSeTx->set(SE_EXPLOSION, "SE_EXPLOSION_MIDDLE_001");
}

void TestPa::onActive() {
    getStatus()->reset();
}

void TestPa::processBehavior() {
    getLocoVehicle()->behave();
    //getSeTransmitter()->behave();
    dispStamina();
}

void TestPa::processJudgement() {
    if (isOutOfSpacetime()) {
        sayonara();
    }
}

void TestPa::onHit(const GgafCore::Actor* prm_pOtherActor) {
    bool was_destroyed = UTIL::performEnemyHit(this, (const GgafDx::GeometricActor*)prm_pOtherActor);
    if (was_destroyed) {
        //破壊された時(スタミナ <= 0)
        getSeTransmitter()->play3D(SE_EXPLOSION);
        sayonara();
    } else {
        //破壊されなかった時(スタミナ > 0)
        getSeTransmitter()->play3D(SE_DAMAGED);
    }
}

TestPa::~TestPa() {
}
