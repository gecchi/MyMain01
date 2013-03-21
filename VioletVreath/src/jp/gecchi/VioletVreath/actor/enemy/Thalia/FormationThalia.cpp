#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

FormationThalia::FormationThalia(const char* prm_name) :
        TreeFormation(prm_name) {
    _class_name = "FormationThalia";
    num_Thalia_      = RR_FormationThalia_Num(_RANK_);         //�ґ��̃^���A�̐�
    interval_frames_ = RR_FormationThalia_LaunchInterval(_RANK_);    //�e�^���A�̏o���Ԋu(frame)
    velo_mv_         = RR_FormationThalia_MvVelo(_RANK_); //�e�^���A�̈ړ����x

    pDpcon_ = connectToDepositoryManager("Conn_Shot004", nullptr);
    //�ґ��쐬
    papThalia_ = NEW EnemyThalia*[num_Thalia_];
    for (int i = 0; i < num_Thalia_; i++) {
        papThalia_[i] = NEW EnemyThalia("Thalia01");
        //�X�v���C���ړ��v���O�����ݒ�
        papThalia_[i]->setSplineSequence(nullptr);
        papThalia_[i]->setDepository_Shot(pDpcon_->fetch()); //�e�ݒ�
        addFormationMember(papThalia_[i]);
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

void FormationThalia::onDestroyAll(GgafActor* prm_pActor_last_destroyed) {
    GgafDxGeometricActor* pActor_last_destroyed = (GgafDxGeometricActor*)prm_pActor_last_destroyed;
    //�ґ��S�Ŏ��G�t�F�N�g�o���i�X�R�A���Z���s����j
    UTIL::activateFormationDestroyedEffectOf(pActor_last_destroyed);
    //�ґ��S�ŃA�C�e���o��
    UTIL::activateFormationDestroyedItemOf(pActor_last_destroyed);
}


FormationThalia::~FormationThalia() {
    pDpcon_->close();
    GGAF_DELETEARR(papThalia_);
}
