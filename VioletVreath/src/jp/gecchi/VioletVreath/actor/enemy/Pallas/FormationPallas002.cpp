#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

FormationPallas002::FormationPallas002(const char* prm_name) :
        TreeFormation(prm_name, 30*60) {
    _class_name = "FormationPallas002";
    num_Pallas_      = R_FormationPallas002_Num;  //�ґ���
    interval_frames_ = R_FormationPallas002_LaunchInterval;  //�p���X�̊Ԋu(frame)
    velo_mv_         = R_FormationPallas002_MvVelo; //���x
    //�p���X�ґ��쐬
    pSplManufCon_ = connectSplineManufactureManager("Pallas02");
//    pSplLineCon_     = connectToSplineLineManager("SpCon_Pallas01"); //�X�v���C����`
    //pDepoCon_ = connectToDepositoryManager("DpCon_Shot002", NULL);
    pDepoCon_ = NULL;
    papPallas_ = NEW EnemyPallas*[num_Pallas_];
    for (int i = 0; i < num_Pallas_; i++) {
        papPallas_[i] = NEW EnemyPallas("Pallas01");
        //�X�v���C���ړ��v���O�����ݒ�
        SplineSequence* pProgram = pSplManufCon_->use()->createSplineSequence(papPallas_[i]->_pKurokoA); //�ړ����x�Œ�
        papPallas_[i]->config(pProgram, NULL, NULL);
        //papPallas_[i]->setDepository_Shot(pDepoCon_->use()); //�e�ݒ�
        papPallas_[i]->inactivateImmed();
        addSubLast(papPallas_[i]);
    }
}

void FormationPallas002::onActive() {
    for (int i = 0; i < num_Pallas_; i++) {
        papPallas_[i]->locate(MyShip::lim_behaind_ *2 , P_MYSHIP->_Y+300000,  P_MYSHIP->_Z);
        papPallas_[i]->_pKurokoA->setMvVelo(velo_mv_);
        papPallas_[i]->activateDelay(i*interval_frames_ + 1);//interval_frames_�Ԋu��Active�ɂ���B
    }
}

FormationPallas002::~FormationPallas002() {
    pSplManufCon_->close();
    if (pDepoCon_) {
        pDepoCon_->close();
    }
    DELETEARR_IMPOSSIBLE_NULL(papPallas_);
}
