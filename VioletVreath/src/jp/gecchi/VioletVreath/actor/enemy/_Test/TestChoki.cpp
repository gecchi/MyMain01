#include "TestChoki.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxSeTransmitterForActor.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;


TestChoki::TestChoki(const char* prm_name) : TestEnemy(prm_name, "TestChoki", STATUS(TestChoki)) {
    _class_name = "TestChoki";
    GgafDxSeTransmitterForActor* pSeTx = getSeTx();
    pSeTx->set(SE_DAMAGED  , "WAVE_ENEMY_DAMAGED_001");
    pSeTx->set(SE_EXPLOSION, "WAVE_EXPLOSION_MIDDLE_001");
}

void TestChoki::onActive() {
    getStatus()->reset();
}

void TestChoki::processBehavior() {
    getKuroko()->behave();
    //getSeTx()->behave();
    dispStamina();
}

void TestChoki::processJudgement() {
    if (isOutOfSpacetime()) {
        sayonara();
    }
}

void TestChoki::onHit(const GgafActor* prm_pOtherActor) {
    bool was_destroyed = UTIL::transactEnemyHit(this, (const GgafDxGeometricActor*)prm_pOtherActor);
    if (was_destroyed) {
        //破壊された時(スタミナ <= 0)
        getSeTx()->play3D(SE_EXPLOSION);
        sayonara();
    } else {
        //破壊されなかった時(スタミナ > 0)
        getSeTx()->play3D(SE_DAMAGED);
    }
}

TestChoki::~TestChoki() {
}
