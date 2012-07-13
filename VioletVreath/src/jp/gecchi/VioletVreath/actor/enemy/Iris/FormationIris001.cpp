#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

FormationIris001::FormationIris001(const char* prm_name) : TreeFormation(prm_name, 30*60) {
    _class_name = "FormationIris001";
    num_Iris_        = RR_FormationIris001_Num(_RANK_);    //�ґ���
    interval_frames_ = RR_FormationIris001_LaunchInterval(_RANK_);   //�C���X�̊Ԋu(frame)
    velo_mv_         = RR_FormationIris001_MvVelo(_RANK_); //���x
    //�C���X�ґ��쐬
    pSplLineCon_   = connectToSplineLineManager("SpCon_00201_"); //�X�v���C����`
    pDepoCon_ = connectToDepositoryManager("DpCon_Shot001", NULL);
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

void FormationIris001::initialize() {
    //�ґ��쐬��onActive()�ōs�키���ƁB
    //FormationTableScene �� active �ɂ����^�C�~���O�͕ϓ����邽��
}

void FormationIris001::onActive() {
    for (int i = 0; i < num_Iris_; i++) {
        papIris_[i]->locate(MyShip::lim_behaind_ - 500000, 0, MyShip::lim_zleft_ * 0.8);
        papIris_[i]->_pKurokoA->setMvVelo(velo_mv_);
        papIris_[i]->activateDelay(i*interval_frames_ + 1);//interval_frames_�Ԋu��Active�ɂ���B
    }
}

FormationIris001::~FormationIris001() {
    pSplLineCon_->close();
    pDepoCon_->close();
    DELETEARR_IMPOSSIBLE_NULL(papIris_);
}
