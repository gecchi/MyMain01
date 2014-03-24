#include "stdafx.h"
#include "EnemyEmiliaBase.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxSeTransmitterForActor.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

EnemyEmiliaBase::EnemyEmiliaBase(const char* prm_name, const char* prm_model, GgafCore::GgafStatus* prm_pStat) :
        DefaultMeshSetActor(prm_name, prm_model, prm_pStat) {
    GgafDxSeTransmitterForActor* pSeTx = getSeTx();
    pSeTx->set(SE_DAMAGED  , "WAVE_ENEMY_DAMAGED_001");
    pSeTx->set(SE_EXPLOSION, "WAVE_EXPLOSION_001");     //����
}

void EnemyEmiliaBase::onCreateModel() {
}

void EnemyEmiliaBase::processBehavior() {
    //���Z�����N�|�C���g������
    UTIL::updateEnemyRankPoint(this);
    getKuroko()->behave();
}

void EnemyEmiliaBase::processJudgement() {
    if (isOutOfUniverse()) {
        sayonara();
    }
}

void EnemyEmiliaBase::onHit(GgafActor* prm_pOtherActor) {
    GgafDxGeometricActor* pOther = (GgafDxGeometricActor*)prm_pOtherActor;
    bool was_destroyed = UTIL::proceedEnemyHit(this, pOther);
    if (was_destroyed) {
        //�j��
        getSeTx()->play3D(SE_EXPLOSION);
        //���ʃN���X�̌X�̏���
        processStaminaEnd(pOther);
    } else {
        //��j��
        getSeTx()->play3D(SE_DAMAGED);
    }
}

void EnemyEmiliaBase::appearFragment(const char* prm_dp_name) {
    //�f�Џo��
    DepositoryConnection* pDepoConn = connect_DepositoryManager(prm_dp_name);
    for (int i = 0; i < RF_EnemyEmilia_ShotWay(G_RANK); i++) {
        EnemyEmiliaBase* pFragment = (EnemyEmiliaBase*)(pDepoConn->peek()->dispatch());
        if (pFragment) {
            pFragment->positionAs(this);
            GgafDxKuroko* pFragment_pKuroko = pFragment->getKuroko();
            pFragment_pKuroko->takeoverMvFrom(this->getKuroko());
            pFragment_pKuroko->setMvVelo(pFragment_pKuroko->_veloMv/2); //�����̃X�s�[�h��
            pFragment_pKuroko->addRyMvAng(RND(D_ANG(-45), D_ANG(+45)));
            pFragment_pKuroko->addRzMvAng(RND(D_ANG(-45), D_ANG(+45)));
        }
    }
    pDepoConn->close();
}
void EnemyEmiliaBase::onInactive() {
    sayonara();
}


EnemyEmiliaBase::~EnemyEmiliaBase() {
}