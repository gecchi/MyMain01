#include "TestGu.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxSeTransmitterForActor.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

TestGu::TestGu(const char* prm_name)
      : TestEnemy(prm_name, "TestGu", STATUS(TestGu)) {
    _class_name = "TestGu";

    GgafDxSeTransmitterForActor* pSeTx = getSeTransmitter();
    pSeTx->set(SE_DAMAGED  , "WAVE_ENEMY_DAMAGED_001");
    pSeTx->set(SE_EXPLOSION, "WAVE_EXPLOSION_MIDDLE_001");
}

void TestGu::onActive() {
    getStatus()->reset();
}

void TestGu::processBehavior() {
    getKuroko()->behave();
    //getSeTransmitter()->behave();
    dispStamina();
}

void TestGu::processJudgement() {
    if (isOutOfSpacetime()) {
        sayonara();
    }
}

void TestGu::onHit(const GgafActor* prm_pOtherActor) {
    bool was_destroyed = UTIL::performEnemyHit(this, (const GgafDxGeometricActor*)prm_pOtherActor);
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
