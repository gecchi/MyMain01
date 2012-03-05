#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

FormationIris002::FormationIris002(const char* prm_name) :
        TreeFormation(prm_name, 30*60) { //30*60���end()����B�����J����������� Depository �̐ڑ����؂�邽�߁B
    _class_name = "FormationIris002";
    num_Iris_        = R_FormationIris002_Num;    //�ґ���
    interval_frames_ = R_FormationIris002_LaunchInterval;   //�C���X�̊Ԋu(frame)
    velo_mv_         = R_FormationIris002_MvVelo; //���x
    //�X�v���C���ړ��̒�`
    pSplLineCon_ = connectToSplineLineManager("SpCon_00202_");
    pDepoCon_ = connectToDepositoryManager("DpCon_Shot002", NULL);
    //�C���X�ґ��쐬
    papIris_ = NEW EnemyIris*[num_Iris_];
    for (int i = 0; i < num_Iris_; i++) {
        papIris_[i] = NEW EnemyIris("Iris01");
        //�X�v���C���ړ��v���O�����ݒ�
        SplineSequence* pProgram = NEW FixedVelocitySplineSequence(papIris_[i]->_pKurokoA, pSplLineCon_->use(), 10000); //�ړ����x�Œ�
        papIris_[i]->config(pProgram, pDepoCon_->use(), NULL);
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

FormationIris002::~FormationIris002() {
    pSplLineCon_->close();
    pDepoCon_->close();
    DELETEARR_IMPOSSIBLE_NULL(papIris_);
}
