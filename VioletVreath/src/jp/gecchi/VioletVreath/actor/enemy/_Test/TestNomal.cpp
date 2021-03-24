#include "TestNomal.h"

#include "jp/ggaf/dx/actor/supporter/SeTransmitterForActor.h"
#include "jp/ggaf/dx/actor/supporter/VecDriver.h"
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
    pSeTx->set(SE_DAMAGED  , "WAVE_ENEMY_DAMAGED_001");
    pSeTx->set(SE_EXPLOSION, "WAVE_EXPLOSION_MIDDLE_001");
}

void TestNomal::onActive() {
    getStatus()->reset();
}

void TestNomal::processBehavior() {
    callVecDriver()->behave();
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
        //�j�󂳂ꂽ��(�X�^�~�i <= 0)
        getSeTransmitter()->play3D(SE_EXPLOSION);
        //sayonara();
    } else {
        //�j�󂳂�Ȃ�������(�X�^�~�i > 0)
        getSeTransmitter()->play3D(SE_DAMAGED);
    }

    getStatus()->reset();
}

TestNomal::~TestNomal() {
}
