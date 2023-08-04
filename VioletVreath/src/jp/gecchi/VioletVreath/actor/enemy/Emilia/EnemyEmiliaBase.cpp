#include "EnemyEmiliaBase.h"

#include "jp/ggaf/dx/actor/supporter/LocoVehicle.h"
#include "jp/ggaf/dx/actor/supporter/SeTransmitterForActor.h"
#include "jp/gecchi/VioletVreath/Caretaker.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"



using namespace GgafLib;
using namespace VioletVreath;

enum {
    SE_DAMAGED   ,
    SE_EXPLOSION ,
};

EnemyEmiliaBase::EnemyEmiliaBase(const char* prm_name, const char* prm_model, void* prm_pFuncStatusReset) :
        VvEnemyActor<DefaultMassMeshActor>(prm_name, prm_model, prm_pFuncStatusReset) {
    pFormationEmilia_ = nullptr;
    pOrg_ = nullptr;
    R_mv_velo_ = 0;
    GgafDx::SeTransmitterForActor* pSeXmtr = getSeXmtr();
    pSeXmtr->set(SE_DAMAGED  , "SE_ENEMY_DAMAGED_001");
    pSeXmtr->set(SE_EXPLOSION, "SE_EXPLOSION_001");     //����
}
void EnemyEmiliaBase::onDispatched(EnemyEmiliaBase* prm_pOrg, FormationEmilia* prm_pFormationEmilia) {
    pOrg_ = prm_pOrg;
    pFormationEmilia_ = prm_pFormationEmilia;
}
void EnemyEmiliaBase::updateRankParameter() {
     R_mv_velo_           = RF_FormationEmilia_MvVelo(G_RANK);         //���x
}
void EnemyEmiliaBase::onCreateModel() {
}


void EnemyEmiliaBase::processBehavior() {
    updateRankParameter();
    getLocoVehicle()->behave();
}

void EnemyEmiliaBase::processJudgement() {
    if (isOutOfSpacetime()) {
        sayonara();
    }
}

void EnemyEmiliaBase::onHit(const GgafCore::Actor* prm_pOtherActor) {
//	if (getActiveFrame() < 5) {
//		return;
//	}
    const GgafDx::GeometricActor* pOtherActor = (const GgafDx::GeometricActor*)prm_pOtherActor;
    bool is_stamina_zero = performEnemyHit(pOtherActor);
    if (is_stamina_zero) {
        //�j�󂳂ꂽ��(�X�^�~�i <= 0)
        getSeXmtr()->play3D(SE_EXPLOSION);
        //���ʃN���X�̌X�̏���
        processStaminaEnd(pOtherActor);
        sayonara();
    } else {
        //�j�󂳂�Ȃ�������(�X�^�~�i > 0)
        getSeXmtr()->play3D(SE_DAMAGED);
    }
}

void EnemyEmiliaBase::onInactive() {
    sayonara();
}

EnemyEmiliaBase::~EnemyEmiliaBase() {
}

