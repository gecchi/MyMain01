#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;


TestNomal::TestNomal(const char* prm_name)
      : TestEnemy(prm_name, "TestNomal", STATUS(TestNomal)) {
    _class_name = "TestNomal";
    _pSeTxer->set(SE_DAMAGED  , "WAVE_ENEMY_DAMAGED_001");
    _pSeTxer->set(SE_EXPLOSION, "WAVE_EXPLOSION_MIDDLE_001");
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
    //���Z�����N�|�C���g������
    _pStatus->mul(STAT_AddRankPoint, _pStatus->getDouble(STAT_AddRankPoint_Reduction));
    _pKurokoA->behave();
    //_pSeTxer->behave();
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
        //�j��
        setHitAble(false);
        UTIL::activateExplosionEffectOf(this); //��������
        _pSeTxer->play3D(SE_EXPLOSION);
        sayonara();
    } else {
        //��j��
        effectFlush(2); //�t���b�V��
        _pSeTxer->play3D(SE_DAMAGED);
    }
}

TestNomal::~TestNomal() {
}
