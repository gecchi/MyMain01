#include "stdafx.h"
#include "EnemyMassaliaBase.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoA.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxSeTransmitterForActor.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

EnemyMassaliaBase::EnemyMassaliaBase(const char* prm_name, const char* prm_model, GgafCore::GgafStatus* prm_pStat) :
        DefaultMeshSetActor(prm_name, prm_model, prm_pStat) {
    _pSeTx->set(SE_DAMAGED  , "WAVE_ENEMY_DAMAGED_001");
    _pSeTx->set(SE_EXPLOSION, "WAVE_EXPLOSION_001");     //����
}

void EnemyMassaliaBase::onCreateModel() {
}

void EnemyMassaliaBase::processBehavior() {
    //���Z�����N�|�C���g������
    _pStatus->mul(STAT_AddRankPoint, _pStatus->getDouble(STAT_AddRankPoint_Reduction));
    _pKurokoA->behave();
}

void EnemyMassaliaBase::processJudgement() {
    if (isOutOfUniverse()) {
        sayonara();
    }
}

void EnemyMassaliaBase::onHit(GgafActor* prm_pOtherActor) {
    GgafDxGeometricActor* pOther = (GgafDxGeometricActor*)prm_pOtherActor;
    bool was_destroyed = UTIL::proceedEnemyHit(this, pOther);
    if (was_destroyed) {
        //�j��
        _pSeTx->play3D(SE_EXPLOSION);
        //���ʃN���X�̌X�̏���
        processStaminaEnd(pOther);
    } else {
        //��j��
        _pSeTx->play3D(SE_DAMAGED);
    }
}

void EnemyMassaliaBase::appearFragment(const char* prm_dp_name) {
    //�f�Џo��
    DepositoryConnection* pDepoConn = connect_DepositoryManager(prm_dp_name);
    for (int i = 0; i < RF_EnemyMassalia_ShotWay(G_RANK); i++) {
        EnemyMassaliaBase* pFragment = (EnemyMassaliaBase*)(pDepoConn->peek()->dispatch());
        if (pFragment) {
            pFragment->locateAs(this);
            pFragment->_pKurokoA->followMvFrom(this->_pKurokoA);
            pFragment->_pKurokoA->setMvVelo(pFragment->_pKurokoA->_veloMv/2); //�����̃X�s�[�h��
            pFragment->_pKurokoA->addRyMvAng(RND(D_ANG(-45), D_ANG(+45)));
            pFragment->_pKurokoA->addRzMvAng(RND(D_ANG(-45), D_ANG(+45)));
        }
    }
    pDepoConn->close();
}
void EnemyMassaliaBase::onInactive() {
    sayonara();
}


EnemyMassaliaBase::~EnemyMassaliaBase() {
}
