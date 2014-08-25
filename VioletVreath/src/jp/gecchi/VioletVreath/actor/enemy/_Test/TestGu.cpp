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

    GgafDxSeTransmitterForActor* pSeTx = getSeTx();
    pSeTx->set(SE_DAMAGED  , "WAVE_ENEMY_DAMAGED_001");
    pSeTx->set(SE_EXPLOSION, "WAVE_EXPLOSION_MIDDLE_001");
}

void TestGu::onActive() {
    getStatus()->reset();
}

void TestGu::processBehavior() {
    //加算ランクポイントを減少
    UTIL::updateEnemyRankPoint(this);
    getKuroko()->behave();
    //getSeTx()->behave();
    dispStamina();
}

void TestGu::processJudgement() {
    if (isOutOfUniverse()) {
        sayonara();
    }
}

void TestGu::onHit(GgafActor* prm_pOtherActor) {
    GgafDxGeometricActor* pOther = (GgafDxGeometricActor*)prm_pOtherActor;
    if (UTIL::calcEnemyStamina(this, pOther) <= 0) {
        //破壊時
        setHitAble(false);
        UTIL::activateExplosionEffectOf(this); //爆発効果
        getSeTx()->play3D(SE_EXPLOSION);
        sayonara();
    } else {
        //非破壊時
        effectFlush(2); //フラッシュ
        getSeTx()->play3D(SE_DAMAGED);
    }
}

TestGu::~TestGu() {
}
