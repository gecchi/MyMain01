#include "EnemyEmiliaBase.h"

#include "jp/ggaf/dx/actor/supporter/LocusVehicle.h"
#include "jp/ggaf/dx/actor/supporter/SeTransmitterForActor.h"
#include "jp/gecchi/VioletVreath/Caretaker.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"

using namespace GgafLib;
using namespace VioletVreath;

EnemyEmiliaBase::EnemyEmiliaBase(const char* prm_name, const char* prm_model, void* prm_pFuncStatusReset) :
        VvEnemyActor<DefaultMassMeshActor>(prm_name, prm_model, prm_pFuncStatusReset) {
    pFormationEmilia_ = nullptr;
    pOrg_ = nullptr;
    R_mv_velo_ = 0;
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
    getLocusVehicle()->behave();
}

void EnemyEmiliaBase::processJudgement() {
    if (isOutOfSpacetime()) {
        sayonara();
    }
}

void EnemyEmiliaBase::onHit(const GgafCore::Checker* prm_pThisHitChecker, const GgafCore::Checker* prm_pOppHitChecker) {
//	if (getActiveFrame() < 5) {
//		return;
//	}
    GgafDx::GeometricActor* pOther = (GgafDx::GeometricActor*)(prm_pOppHitChecker->_pActor);
    bool is_stamina_zero = performEnemyHit(prm_pOppHitChecker);
    if (is_stamina_zero) {
        //破壊された時(スタミナ <= 0)
        //下位クラスの個々の処理
        processStaminaEnd(pOther);
        sayonara();
    } else {
        //破壊されなかった時(スタミナ > 0)
    }
}

void EnemyEmiliaBase::onInactive() {
    sayonara();
}

EnemyEmiliaBase::~EnemyEmiliaBase() {
}

