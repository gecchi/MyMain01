#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;


TestChoki::TestChoki(const char* prm_name)
      : TestEnemy(prm_name, "TestChoki", STATUS(TestChoki)) {
    _class_name = "TestChoki";
    _pSeTx->set(SE_DAMAGED  , "WAVE_ENEMY_DAMAGED_001");
    _pSeTx->set(SE_EXPLOSION, "WAVE_EXPLOSION_MIDDLE_001");
}

void TestChoki::initialize() {
    setHitAble(true);
    _pColliChecker->makeCollision(1);
    _pColliChecker->setColliAAB(0, -30000, -30000, -30000, 30000, 30000, 30000);
}

void TestChoki::onActive() {
    _pStatus->reset();
}

void TestChoki::processBehavior() {
    //���Z�����N�|�C���g������
    _pStatus->mul(STAT_AddRankPoint, _pStatus->getDouble(STAT_AddRankPoint_Reduction));
    _pKurokoA->behave();
    //_pSeTx->behave();
    dispStamina();
}

void TestChoki::processJudgement() {
    if (isOutOfUniverse()) {
        sayonara();
    }
}

void TestChoki::onHit(GgafActor* prm_pOtherActor) {
    GgafDxGeometricActor* pOther = (GgafDxGeometricActor*)prm_pOtherActor;
    if (UTIL::calcEnemyStamina(this, pOther) <= 0) {
        //�j��
        setHitAble(false);
        UTIL::activateExplosionEffectOf(this); //��������
        _pSeTx->play3D(SE_EXPLOSION);
        sayonara();
    } else {
        //��j��
        effectFlush(2); //�t���b�V��
        _pSeTx->play3D(SE_DAMAGED);
    }
}

TestChoki::~TestChoki() {
}
