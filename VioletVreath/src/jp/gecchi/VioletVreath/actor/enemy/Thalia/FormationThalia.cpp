#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

FormationThalia::FormationThalia(const char* prm_name) :
        TreeFormation(prm_name, 30*60) {
    _class_name = "FormationThalia";
    num_Thalia_      = RR_FormationThalia_Num(_RANK_);         //�ґ��̃^���A�̐�
    interval_frames_ = RR_FormationThalia_LaunchInterval(_RANK_);    //�e�^���A�̏o���Ԋu(frame)
    velo_mv_         = RR_FormationThalia_MvVelo(_RANK_); //�e�^���A�̈ړ����x

    pDpcon_ = connectToDepositoryManager("Conn_Shot004", NULL);
    //�ґ��쐬
    papThalia_ = NEW EnemyThalia*[num_Thalia_];
    for (int i = 0; i < num_Thalia_; i++) {
        papThalia_[i] = NEW EnemyThalia("Thalia01");
        //�X�v���C���ړ��v���O�����ݒ�
        papThalia_[i]->setSplineSequence(NULL);
        papThalia_[i]->setDepository_Shot(pDpcon_->fetch()); //�e�ݒ�
        papThalia_[i]->inactivateImmed();
        addSubLast(papThalia_[i]);
    }
}

void FormationThalia::initialize() {

}

void FormationThalia::onActive() {
    for (int i = 0; i < num_Thalia_; i++) {
        papThalia_[i]->locate(MyShip::lim_behaind_, -2000000 + (i * 400000), 0);
        papThalia_[i]->_pKurokoA->setRzRyMvAng(0,0);
        papThalia_[i]->_pKurokoA->setMvVelo(80000);
        papThalia_[i]->activateDelay(i*interval_frames_ + 1);//interval_frames_�Ԋu��Active�ɂ���B
    }
}

FormationThalia::~FormationThalia() {
    pDpcon_->close();
    DELETEARR_IMPOSSIBLE_NULL(papThalia_);
}
