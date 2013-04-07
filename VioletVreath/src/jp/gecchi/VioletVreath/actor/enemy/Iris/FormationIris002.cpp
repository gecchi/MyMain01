#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

FormationIris002::FormationIris002(const char* prm_name) :
        TreeFormation(prm_name) {
    _class_name = "FormationIris002";
    num_Iris_        = RR_FormationIris002_Num(_RANK_);    //�ґ���
    interval_frames_ = RR_FormationIris002_LaunchInterval(_RANK_);   //�C���X�̊Ԋu(frame)
    velo_mv_         = RR_FormationIris002_MvVelo(_RANK_); //���x
    //�X�v���C���ړ��̒�`
    pSplLineConnection_ = connectToSplineLineManager("Spl_00202_");
    pDepoConnection_ = connectToDepositoryManager("Shot002");
    //�C���X�ґ��쐬
    for (int i = 0; i < num_Iris_; i++) {
        EnemyIris* pIris = NEW EnemyIris("Iris01");
        //�X�v���C���ړ��v���O�����ݒ�
        SplineKurokoStepper* pProgram = NEW FixedVelocitySplineKurokoStepper(
                                         pIris->_pKurokoA, pSplLineConnection_->peek(), 10000); //�ړ����x�Œ�
        pIris->config(pProgram, pDepoConnection_->peek(), nullptr);
        addFormationMember(pIris);
    }
}

void FormationIris002::initialize() {
}

void FormationIris002::onActive() {
}

void FormationIris002::processBehavior() {
    if (canCallUp() && (getActiveFrame()-1) % interval_frames_ == 0) {
        EnemyIris* pIris = (EnemyIris*)callUpMember();
        if (pIris) {
            pIris->locate(MyShip::lim_behaind_ - 500000, 0, MyShip::lim_zright_ * 0.8);
            pIris->_pKurokoA->setMvVelo(velo_mv_);
        }
    }
}

void FormationIris002::onDestroyAll(GgafCore::GgafActor* prm_pActor_last_destroyed) {
    GgafDxGeometricActor* pActor_last_destroyed = (GgafDxGeometricActor*)prm_pActor_last_destroyed;
    //�ґ��S�Ŏ��G�t�F�N�g�o���i���{�[�i�X�X�R�A���Z���s����j
    UTIL::activateFormationDestroyedEffectOf(pActor_last_destroyed);
    //�ґ��S�ŃA�C�e���o��
    UTIL::activateFormationDestroyedItemOf(pActor_last_destroyed);
}

FormationIris002::~FormationIris002() {
    pSplLineConnection_->close();
    pDepoConnection_->close();
}
