#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

FormationHebe::FormationHebe(const char* prm_name, const char* prm_spl_id)
   : DepositoryFormation(prm_name, 20*60) {
    _class_name = "FormationHebe";

    pCon_HebeDepo_ = connectToDepositoryManager("DpCon_EnemyHebe4Formation", this);
    setFormationAbleActorDepository(pCon_HebeDepo_->fetch());

    //�X�v���C����`�t�@�C����ǂݍ���
    pSplManufCon_ = connectToSplineManufactureManager("FormationHebe001");
    //pCon_ShotDepo_ = connectToDepositoryManager("DpCon_Shot004", NULL); //Hebe�̒e;
    pCon_ShotDepo_ = NULL;
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

void FormationHebe::onDestroyedAll(GgafActor* prm_pActor_LastDestroyed) {
    //�ґ����Ŏ��̎���
    EffectTurbo002* pTurbo002 = employFromCommon(EffectTurbo002);
    if (pTurbo002) {
        pTurbo002->locateWith((GgafDxGeometricActor*)prm_pActor_LastDestroyed);
    }
    //�ґ��S�ŃA�C�e���o��
    Item* pItem = employFromCommon(MagicPointItem002);
    if (pItem) {
        pItem->locateWith((GgafDxGeometricActor*)prm_pActor_LastDestroyed);
    }
}

void FormationHebe::processBehavior() {
    if (! isAllCalledUp() && (getActivePartFrame() % rr_interval_frames_ == 0)) {
        EnemyHebe* pHebe = (EnemyHebe*)callUpUntil(rr_num_formation_);
        if (pHebe) {
            SplineSequence* pSplSeq = pSplManufCon_->fetch()->
                                          createSplineSequence(pHebe->_pKurokoA);
            GgafActorDepository* pDepo_Shot = pCon_ShotDepo_ ? pCon_ShotDepo_->fetch() : NULL;
            pHebe->config(pSplSeq, pDepo_Shot, NULL);
            pHebe->_pKurokoA->setMvVelo(rr_mv_velo_);
            processOnActiveHebe(pHebe); //���ʃt�H�[���[�V�����N���X�ʎ����̏���
        }
    }
}

FormationHebe::~FormationHebe() {
    pCon_HebeDepo_->close();
    pSplManufCon_->close();
    if (pCon_ShotDepo_) {
        pCon_ShotDepo_->close();
    }
}

