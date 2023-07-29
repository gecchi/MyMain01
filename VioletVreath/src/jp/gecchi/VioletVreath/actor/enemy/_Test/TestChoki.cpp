#include "TestChoki.h"

#include "jp/ggaf/dx/actor/supporter/LocoVehicle.h"
#include "jp/ggaf/dx/actor/supporter/SeTransmitterForActor.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"



using namespace GgafLib;
using namespace VioletVreath;

enum {
    SE_DAMAGED   ,
    SE_EXPLOSION ,
};

TestChoki::TestChoki(const char* prm_name) : TestEnemy(prm_name, "TestChoki", StatusReset(TestChoki)) {
    _class_name = "TestChoki";
    GgafDx::SeTransmitterForActor* pSeXmtr = getSeXmtr();
    pSeXmtr->set(SE_DAMAGED  , "SE_ENEMY_DAMAGED_001");
    pSeXmtr->set(SE_EXPLOSION, "SE_EXPLOSION_MIDDLE_001");
}

void TestChoki::onActive() {
    getStatus()->reset();
}

void TestChoki::processBehavior() {
    getLocoVehicle()->behave();
    //getSeXmtr()->behave();
    dispStamina();
}

void TestChoki::processJudgement() {
    if (isOutOfSpacetime()) {
        sayonara();
    }
}

void TestChoki::onHit(const GgafCore::Actor* prm_pOtherActor) {
    bool was_destroyed = performEnemyHit((const GgafDx::GeometricActor*)prm_pOtherActor);
    if (was_destroyed) {
        //破壊された時(スタミナ <= 0)
        getSeXmtr()->play3D(SE_EXPLOSION);
        sayonara();
    } else {
        //破壊されなかった時(スタミナ > 0)
        getSeXmtr()->play3D(SE_DAMAGED);
    }
}

TestChoki::~TestChoki() {
}
