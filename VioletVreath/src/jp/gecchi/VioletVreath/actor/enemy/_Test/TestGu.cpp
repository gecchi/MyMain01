#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;


TestGu::TestGu(const char* prm_name)
      : TestEnemy(prm_name, "TestGu", STATUS(TestGu)) {
    _class_name = "TestGu";
    _pSeTxer->set(SE_DAMAGED  , "yume_shototsu", GgafRepeatSeq::nextVal("CH_yume_shototsu"));
    _pSeTxer->set(SE_EXPLOSION, "bom10"        , GgafRepeatSeq::nextVal("CH_bom10"));
}

void TestGu::initialize() {
    setHitAble(true);
    _pColliChecker->makeCollision(1);
    _pColliChecker->setColliAAB(0, -30000, -30000, -30000, 30000, 30000, 30000);
}

void TestGu::onActive() {
    _pStatus->reset();
}

void TestGu::processBehavior() {
    //���Z�����N�|�C���g������
    _pStatus->mul(STAT_AddRankPoint, _pStatus->getDouble(STAT_AddRankPoint_Reduction));
    _pKurokoA->behave();
    //_pSeTxer->behave();
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

TestGu::~TestGu() {
}
