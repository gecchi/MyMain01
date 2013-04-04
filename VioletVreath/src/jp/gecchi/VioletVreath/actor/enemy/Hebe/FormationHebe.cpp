#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

FormationHebe::FormationHebe(const char* prm_name, const char* prm_spl_id)
   : DepositoryFormation(prm_name, 20*60) {
    _class_name = "FormationHebe";

    pConnection_HebeDepo_ = connectToDepositoryManager("EnemyHebe4Formation");
    setFormationMemberDepo(pConnection_HebeDepo_->peek());

    //�X�v���C����`�t�@�C����ǂݍ���
    pSplManufConnection_ = connectToSplineManufactureManager("FormationHebe001");
    //pConnection_ShotDepo_ = connectToDepositoryManager("Shot004"); //Hebe�̒e;
    pConnection_ShotDepo_ = nullptr;
    updateRankParameter();
}

void FormationHebe::updateRankParameter() {
    rr_num_formation_     = RR_FormationHebe_Num(_RANK_);            //�ґ���
    rr_interval_frames_   = RR_FormationHebe_LaunchInterval(_RANK_); //�w�[�x�̊Ԋu(frame)
    rr_mv_velo_           = RR_FormationHebe_MvVelo(_RANK_);         //���x
}

void FormationHebe::initialize() {
}

void FormationHebe::onActive() {
    updateRankParameter();
}

void FormationHebe::processBehavior() {
    if (canCallUp() && (getActivePartFrame() % rr_interval_frames_ == 0)) {
        EnemyHebe* pHebe = (EnemyHebe*)callUpMember(rr_num_formation_);
        if (pHebe) {
            SplineKurokoStepper* pKurokoStepper = pSplManufConnection_->peek()->
                                          createSplineKurokoStepper(pHebe->_pKurokoA);
            GgafActorDepository* pDepo_Shot = pConnection_ShotDepo_ ? pConnection_ShotDepo_->peek() : nullptr;
            pHebe->config(pKurokoStepper, pDepo_Shot, nullptr);
            pHebe->_pKurokoA->setMvVelo(rr_mv_velo_);
            onCallUpHebe(pHebe); //���ʃt�H�[���[�V�����N���X�ʎ����̏���
        }
    }
}

void FormationHebe::onDestroyAll(GgafActor* prm_pActor_last_destroyed) {
    GgafDxGeometricActor* pActor_last_destroyed = (GgafDxGeometricActor*)prm_pActor_last_destroyed;
    //�ґ��S�Ŏ��G�t�F�N�g�o���i���{�[�i�X�X�R�A���Z���s����j
    UTIL::activateFormationDestroyedEffectOf(pActor_last_destroyed);
    //�ґ��S�ŃA�C�e���o��
    UTIL::activateFormationDestroyedItemOf(pActor_last_destroyed);
}

FormationHebe::~FormationHebe() {
    pConnection_HebeDepo_->close();
    pSplManufConnection_->close();
    if (pConnection_ShotDepo_) {
        pConnection_ShotDepo_->close();
    }
}

