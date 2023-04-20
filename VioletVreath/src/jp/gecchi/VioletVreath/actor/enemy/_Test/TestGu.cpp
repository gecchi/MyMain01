#include "TestGu.h"

#include "jp/ggaf/dx/actor/supporter/SeTransmitterForActor.h"
#include "jp/ggaf/dx/actor/supporter/LocoVehicle.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"

using namespace GgafLib;
using namespace VioletVreath;

enum {
    SE_DAMAGED   ,
    SE_EXPLOSION ,
};

TestGu::TestGu(const char* prm_name)
      : TestEnemy(prm_name, "TestGu", StatusReset(TestGu)) {
    _class_name = "TestGu";
    GgafDx::SeTransmitterForActor* pSeTx = getSeTransmitter();
    pSeTx->set(SE_DAMAGED  , "SE_ENEMY_DAMAGED_001");
    pSeTx->set(SE_EXPLOSION, "SE_EXPLOSION_MIDDLE_001");
}

void TestGu::onActive() {
    getStatus()->reset();
}

void TestGu::processBehavior() {
    getLocoVehicle()->behave();
    //getSeTransmitter()->behave();
    dispStamina();
}

void TestGu::processJudgement() {
    if (isOutOfSpacetime()) {
        sayonara();
    }
}

void TestGu::onHit(const GgafCore::Actor* prm_pOtherActor) {
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

TestGu::~TestGu() {
}
