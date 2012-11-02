#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

FormationIris002::FormationIris002(const char* prm_name) :
        TreeFormation(prm_name, 30*60) { //30*60���sayonara()����B�����J����������� Depository �̐ڑ����؂�邽�߁B
    _class_name = "FormationIris002";
    num_Iris_        = RR_FormationIris002_Num(_RANK_);    //�ґ���
    interval_frames_ = RR_FormationIris002_LaunchInterval(_RANK_);   //�C���X�̊Ԋu(frame)
    velo_mv_         = RR_FormationIris002_MvVelo(_RANK_); //���x
    //�X�v���C���ړ��̒�`
    pSplLineCon_ = connectToSplineLineManager("SpConn_00202_");
    pDepoCon_ = connectToDepositoryManager("Conn_Shot002", NULL);
    //�C���X�ґ��쐬
    papIris_ = NEW EnemyIris*[num_Iris_];
    for (int i = 0; i < num_Iris_; i++) {
        papIris_[i] = NEW EnemyIris("Iris01");
        //�X�v���C���ړ��v���O�����ݒ�
        SplineSequence* pProgram = NEW FixedVelocitySplineSequence(papIris_[i]->_pKurokoA, pSplLineCon_->fetch(), 10000); //�ړ����x�Œ�
        papIris_[i]->config(pProgram, pDepoCon_->fetch(), NULL);
        papIris_[i]->inactivateImmed();
        addSubLast(papIris_[i]);
    }
}

void FormationIris002::initialize() {

}

void FormationIris002::onActive() {
    for (int i = 0; i < num_Iris_; i++) {
        papIris_[i]->locate(MyShip::lim_behaind_ - 500000, 0, MyShip::lim_zright_ * 0.8);
        papIris_[i]->_pKurokoA->setMvVelo(velo_mv_);
        papIris_[i]->activateDelay(i*interval_frames_ + 1);//interval_frames_�Ԋu��Active�ɂ���B
    }
}

void FormationIris002::onDestroyedAll(GgafCore::GgafActor* prm_pActor_LastDestroyed) {
    GgafDxGeometricActor* pActor_LastDestroyed = (GgafDxGeometricActor*)prm_pActor_LastDestroyed;
    //�ґ��S�Ŏ��G�t�F�N�g�o���i�X�R�A���Z���s����j
    UTIL::activateFormationDestroyedEffectOf(pActor_LastDestroyed);
    //�ґ��S�ŃA�C�e���o��
    UTIL::activateFormationDestroyedItemOf(pActor_LastDestroyed);
}

FormationIris002::~FormationIris002() {
    pSplLineCon_->close();
    pDepoCon_->close();
    DELETEARR_IMPOSSIBLE_NULL(papIris_);
}
