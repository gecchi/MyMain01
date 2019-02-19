#include "TestChoki.h"

#include "jp/ggaf/dx/actor/supporter/Kuroko.h"
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
    GgafDx::SeTransmitterForActor* pSeTx = getSeTransmitter();
    pSeTx->set(SE_DAMAGED  , "WAVE_ENEMY_DAMAGED_001");
    pSeTx->set(SE_EXPLOSION, "WAVE_EXPLOSION_MIDDLE_001");
}

void TestChoki::onActive() {
    getStatus()->reset();
}

void TestChoki::processBehavior() {
    getKuroko()->behave();
    //getSeTransmitter()->behave();
    dispStamina();
}

void TestChoki::processJudgement() {
    if (isOutOfSpacetime()) {
        sayonara();
    }
}

void TestChoki::onHit(const GgafCore::Actor* prm_pOtherActor) {
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

TestChoki::~TestChoki() {
}
