#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

FormationPallas001::FormationPallas001(const char* prm_name) :
        TreeFormation(prm_name) {
    _class_name = "FormationPallas001";
    num_Pallas_      = RR_FormationPallas001_Num(_RANK_);    //�ґ���
    interval_frames_ = RR_FormationPallas001_LaunchInterval(_RANK_);  //�p���X�̊Ԋu(frame)
    velo_mv_         = RR_FormationPallas001_MvVelo(_RANK_); //���x
    //�p���X�ґ��쐬
    pSplManufConnection_ = connectToSplineManufactureManager("Pallas01");
    pDepoConnection_ = nullptr;
    for (int i = 0; i < num_Pallas_; i++) {
        EnemyPallas* pPallas= NEW EnemyPallas("Pallas01");
        SplineKurokoLeader* pKurokoLeader = pSplManufConnection_->peek()->createKurokoLeader(pPallas->_pKurokoA);
        pPallas->config(pKurokoLeader, nullptr, nullptr);
        addFormationMember(pPallas);
    }
}

void FormationPallas001::initialize() {
}

void FormationPallas001::onActive() {
    for (int n = 0; canCallUp(); n++) {
        EnemyPallas* pPallas = (EnemyPallas*)callUpMember();
        if (pPallas) {
            onCallUpPallas(pPallas); //�R�[���o�b�N
            pPallas->activateDelay(n*interval_frames_ + 1); //�����\��t���[���㏑��
            n++;
        }
    }
    //FormationTableScene �ɒǉ�����ґ��̏ꍇ�A
    //�ґ����r���ł����؂�鎖��h�����߂ɁA���̂悤��
    //onActive()���ŁA��C�ɑS�Ă̕ґ��v���� callUpMember() ���邱�Ƃɂ����B
}

void FormationPallas001::processBehavior() {
}

void FormationPallas001::onDestroyAll(GgafActor* prm_pActor_last_destroyed) {
    UTIL::proceedFormationDestroyAll((GgafDxDrawableActor*)prm_pActor_last_destroyed);
}

FormationPallas001::~FormationPallas001() {
    pSplManufConnection_->close();
    if (pDepoConnection_) {
        pDepoConnection_->close();
    }
}
