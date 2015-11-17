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
    pSeTx->set(SE_EXPLOSION, "WAVE_EXPLOSION_001");     //爆発
}

void EnemyEmiliaBase::onCreateModel() {
}

void EnemyEmiliaBase::processBehavior() {
    getKuroko()->behave();
}

void EnemyEmiliaBase::processJudgement() {
    if (isOutOfSpacetime()) {
        sayonara();
    }
}

void EnemyEmiliaBase::onHit(const GgafActor* prm_pOtherActor) {
//	if (getActiveFrame() < 5) {
//		return;
//	}
    const GgafDxGeometricActor* pOtherActor = (const GgafDxGeometricActor*)prm_pOtherActor;
    bool was_destroyed = UTIL::transactEnemyHit(this, pOtherActor);
    if (was_destroyed) {
        //破壊された時(スタミナ <= 0)
        getSeTx()->play3D(SE_EXPLOSION);
        sayonara();
        //下位クラスの個々の処理
//        processStaminaEnd(pOtherActor);
    } else {
        //破壊されなかった時(スタミナ > 0)
        getSeTx()->play3D(SE_DAMAGED);
    }
}

void EnemyEmiliaBase::appearFragment(const char* prm_dp_name) {
    //断片出現
    DepositoryConnection* pConn_depo = getConnection_DepositoryManager(prm_dp_name);
    for (int i = 0; i < RF_EnemyEmilia_ShotWay(G_RANK); i++) {
        EnemyEmiliaBase* pFragment = (EnemyEmiliaBase*)(pConn_depo->peek()->dispatch());
        if (pFragment) {
            pFragment->positionAs(this);
            GgafDxKuroko* pFragment_pKuroko = pFragment->getKuroko();
            pFragment_pKuroko->takeoverMvFrom(this->getKuroko());
            pFragment_pKuroko->setMvVelo(pFragment_pKuroko->_velo_mv/2); //半分のスピードへ
            pFragment_pKuroko->addRyMvAng(RND(D_ANG(-90), D_ANG(+90)));
            pFragment_pKuroko->addRzMvAng(RND(D_ANG(-90), D_ANG(+90)));
        }
    }
    pConn_depo->close();
}

void EnemyEmiliaBase::onInactive() {
    sayonara();
}

EnemyEmiliaBase::~EnemyEmiliaBase() {
}

