#include "stdafx.h"
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
    _pStatus->reset();
}

void TestNomal::processBehavior() {
    //加算ランクポイントを減少
    _pStatus->mul(STAT_AddRankPoint, _pStatus->getDouble(STAT_AddRankPoint_Reduction));
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

TestNomal::~TestNomal() {
}
