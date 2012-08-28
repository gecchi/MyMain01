#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;


TestPa::TestPa(const char* prm_name)
      : TestEnemy(prm_name, "TestPa", STATUS(TestPa)) {
    _class_name = "TestPa";
    _pSeTxer->set(SE_DAMAGED  , "yume_shototsu", GgafRepeatSeq::nextVal("CH_yume_shototsu"));
    _pSeTxer->set(SE_EXPLOSION, "bom10"        , GgafRepeatSeq::nextVal("CH_bom10"));
}

void TestPa::initialize() {
    setHitAble(true);
    _pColliChecker->makeCollision(1);
    _pColliChecker->setColliAAB(0, -30000, -30000, -30000, 30000, 30000, 30000);
}

void TestPa::onActive() {
    _pStatus->reset();
}

void TestPa::processBehavior() {
    //加算ランクポイントを減少
    _pStatus->mul(STAT_AddRankPoint, _pStatus->getDouble(STAT_AddRankPoint_Reduction));
    _pKurokoA->behave();
    //_pSeTxer->behave();
    dispStamina();
}

void TestPa::processJudgement() {
    if (isOutOfUniverse()) {
        sayonara();
    }
}

void TestPa::onHit(GgafActor* prm_pOtherActor) {
    GgafDxGeometricActor* pOther = (GgafDxGeometricActor*)prm_pOtherActor;
    if (UTIL::calcEnemyStamina(this, pOther) <= 0) {
        //破壊時
        setHitAble(false);
        UTIL::activateExplosionEffectOf(this); //爆発効果
        _pSeTxer->play3D(SE_EXPLOSION);
        sayonara();
    } else {
        //非破壊時
        effectFlush(2); //フラッシュ
        _pSeTxer->play3D(SE_DAMAGED);
    }
}

TestPa::~TestPa() {
}
