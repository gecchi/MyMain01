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
        DefaultMassMeshActor(prm_name, prm_model, prm_pStat) {
    GgafDxSeTransmitterForActor* pSeTx = getSeTransmitter();
    pSeTx->set(SE_DAMAGED  , "WAVE_ENEMY_DAMAGED_001");
    pSeTx->set(SE_EXPLOSION, "WAVE_EXPLOSION_001");     //爆発
}
void EnemyEmiliaBase::onDispatched(EnemyEmiliaBase* prm_pOrg, FormationEmilia* prm_pFormationEmilia) {
    pOrg_ = prm_pOrg;
    pFormationEmilia_ = prm_pFormationEmilia;
}
void EnemyEmiliaBase::updateRankParameter() {
     R_mv_velo_           = RF_FormationEmilia_MvVelo(G_RANK);         //速度
}
void EnemyEmiliaBase::onCreateModel() {
}


void EnemyEmiliaBase::processBehavior() {
    updateRankParameter();
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
    bool was_destroyed = UTIL::performEnemyHit(this, pOtherActor);
    if (was_destroyed) {
        //破壊された時(スタミナ <= 0)
        getSeTransmitter()->play3D(SE_EXPLOSION);
        //下位クラスの個々の処理
        processStaminaEnd(pOtherActor);
        sayonara();
    } else {
        //破壊されなかった時(スタミナ > 0)
        getSeTransmitter()->play3D(SE_DAMAGED);
    }
}

void EnemyEmiliaBase::onInactive() {
    sayonara();
}

EnemyEmiliaBase::~EnemyEmiliaBase() {
}

