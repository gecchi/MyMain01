#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

EnemyMassaliaBase::EnemyMassaliaBase(const char* prm_name, const char* prm_model, GgafCore::GgafStatus* prm_pStat) :
        DefaultMeshSetActor(prm_name, prm_model, prm_pStat) {
    _pSeTxer->set(SE_DAMAGED  , "yume_shototsu", GgafRepeatSeq::nextVal("CH_yume_shototsu"));
    _pSeTxer->set(SE_EXPLOSION, "bomb1"        , GgafRepeatSeq::nextVal("CH_bomb1"));     //����
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

    if (UTIL::calcEnemyStamina(this, pOther) <= 0) {
        //�j��
        setHitAble(false);
        UTIL::activateExplosionEffectOf(this);
        _pSeTxer->play3D(SE_EXPLOSION);
        sayonara();
        //���ʃN���X�̌X�̏���
        processStaminaEnd(pOther);
    } else {
        //��j��
        effectFlush(2); //�t���b�V��
        _pSeTxer->play3D(SE_DAMAGED);
    }

}

void EnemyMassaliaBase::appearFragment(const char* prm_dp_name) {
    //�f�Џo��
    DepositoryConnection* pCon = connectToDepositoryManager(prm_dp_name, this);
    GgafActorDepository* pDepo = pCon->fetch();
    for (int i = 0; i < RR_EnemyMassalia_ShotWay(_RANK_); i++) {
        EnemyMassaliaBase* pFragment = (EnemyMassaliaBase*)(pDepo->dispatch());
        if (pFragment) {
            pFragment->locateWith(this);
            pFragment->_pKurokoA->followMvFrom(this->_pKurokoA);
            pFragment->_pKurokoA->setMvVelo(pFragment->_pKurokoA->_veloMv/2); //�����̃X�s�[�h��
            pFragment->_pKurokoA->addRyMvAng(RND(D_ANG(-45), D_ANG(+45)));
            pFragment->_pKurokoA->addRzMvAng(RND(D_ANG(-45), D_ANG(+45)));
        }
    }
    pCon->close();
}
void EnemyMassaliaBase::onInactive() {
    sayonara();
}


EnemyMassaliaBase::~EnemyMassaliaBase() {
}