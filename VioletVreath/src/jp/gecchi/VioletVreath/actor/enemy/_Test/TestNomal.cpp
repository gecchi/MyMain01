#include "TestNomal.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxSeTransmitterForActor.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

TestNomal::TestNomal(const char* prm_name)
      : TestEnemy(prm_name, "TestNomal", STATUS(TestNomal)) {
    _class_name = "TestNomal";

    GgafDxSeTransmitterForActor* pSeTx = getSeTx();
    pSeTx->set(SE_DAMAGED  , "WAVE_ENEMY_DAMAGED_001");
    pSeTx->set(SE_EXPLOSION, "WAVE_EXPLOSION_MIDDLE_001");
}

void TestNomal::onActive() {
    getStatus()->reset();
}

void TestNomal::processBehavior() {
    //加算ランクポイントを減少
    UTIL::updateEnemyRankPoint(this);
    getKuroko()->behave();
    //getSeTx()->behave();
    dispStamina();
}

void TestNomal::processJudgement() {
    if (isOutOfUniverse()) {
        sayonara();
    }
}

void TestNomal::onHit(GgafActor* prm_pOtherActor) {
    const bool was_destroyed = UTIL::transactEnemyHit(this, (GgafDxGeometricActor*)prm_pOtherActor);
    if (was_destroyed) {
        //破壊された時(スタミナ <= 0)
        getSeTx()->play3D(SE_EXPLOSION);
        sayonara();
    } else {
        //破壊されなかった時(スタミナ > 0)
        getSeTx()->play3D(SE_DAMAGED);
    }
}

TestNomal::~TestNomal() {
}
