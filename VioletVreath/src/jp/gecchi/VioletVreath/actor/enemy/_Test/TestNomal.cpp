#include "TestNomal.h"

#include "jp/ggaf/dx/actor/supporter/SeTransmitterForActor.h"
#include "jp/ggaf/dx/actor/supporter/LocoVehicle.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"

using namespace GgafLib;
using namespace VioletVreath;

enum {
    SE_DAMAGED   ,
    SE_EXPLOSION ,
};

TestNomal::TestNomal(const char* prm_name)
      : TestEnemy(prm_name, "TestNomal", StatusReset(TestNomal)) {
    _class_name = "TestNomal";

    GgafDx::SeTransmitterForActor* pSeTx = getSeTransmitter();
    pSeTx->set(SE_DAMAGED  , "SE_ENEMY_DAMAGED_001");
    pSeTx->set(SE_EXPLOSION, "SE_EXPLOSION_MIDDLE_001");
}

void TestNomal::onActive() {
    getStatus()->reset();
}

void TestNomal::processBehavior() {
    getLocoVehicle()->behave();
    //getSeTransmitter()->behave();
    dispStamina();
}

void TestNomal::processJudgement() {
    if (isOutOfSpacetime()) {
        sayonara();
    }
}

void TestNomal::onHit(const GgafCore::Actor* prm_pOtherActor) {
_TRACE_(FUNC_NAME<<" !");

    bool was_destroyed = UTIL::performEnemyHit(this, (const GgafDx::GeometricActor*)prm_pOtherActor);
    if (was_destroyed) {
        //破壊された時(スタミナ <= 0)
        getSeTransmitter()->play3D(SE_EXPLOSION);
        //sayonara();
    } else {
        //破壊されなかった時(スタミナ > 0)
        getSeTransmitter()->play3D(SE_DAMAGED);
    }

    getStatus()->reset();
}

TestNomal::~TestNomal() {
}
