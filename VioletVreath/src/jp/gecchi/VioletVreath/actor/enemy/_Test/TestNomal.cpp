#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;


TestNomal::TestNomal(const char* prm_name)
      : TestEnemy(prm_name, "TestNomal", STATUS(TestNomal)) {
    _class_name = "TestNomal";
    _pSeTx->set(SE_DAMAGED  , "WAVE_ENEMY_DAMAGED_001");
    _pSeTx->set(SE_EXPLOSION, "WAVE_EXPLOSION_MIDDLE_001");
}

void TestNomal::initialize() {
    setHitAble(true);
    _pColliChecker->makeCollision(1);
    _pColliChecker->setColliAAB(0, -30000, -30000, -30000, 30000, 30000, 30000);
}

void TestNomal::onActive() {
    _pStatus->reset();
}

void TestNomal::processBehavior() {
    //加算ランクポイントを減少
    _pStatus->mul(STAT_AddRankPoint, _pStatus->getDouble(STAT_AddRankPoint_Reduction));
    _pKurokoA->behave();
    //_pSeTx->behave();
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
        _pSeTx->play3D(SE_EXPLOSION);
        sayonara();
    } else {
        //非破壊時
        effectFlush(2); //フラッシュ
        _pSeTx->play3D(SE_DAMAGED);
    }
}

TestNomal::~TestNomal() {
}
