#include "stdafx.h"
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
    _pSeTx->set(SE_DAMAGED  , "WAVE_ENEMY_DAMAGED_001");
    _pSeTx->set(SE_EXPLOSION, "WAVE_EXPLOSION_MIDDLE_001");
}

void TestGu::onActive() {
    _pStatus->reset();
}

void TestGu::processBehavior() {
    //���Z�����N�|�C���g������
    _pStatus->mul(STAT_AddRankPoint, _pStatus->getDouble(STAT_AddRankPoint_Reduction));
    _pKuroko->behave();
    //_pSeTx->behave();
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
        _pSeTx->play3D(SE_EXPLOSION);
        sayonara();
    } else {
        //��j��
        effectFlush(2); //�t���b�V��
        _pSeTx->play3D(SE_DAMAGED);
    }
}

TestGu::~TestGu() {
}
