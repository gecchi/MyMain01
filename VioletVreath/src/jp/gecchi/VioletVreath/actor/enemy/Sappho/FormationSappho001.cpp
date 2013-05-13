#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

FormationSappho001::FormationSappho001(const char* prm_name) :
        TreeFormation(prm_name) {
    _class_name = "FormationSappho001";
    num_Sappho_      = RR_FormationSappho001_Num(_RANK_);    //�ґ���
    interval_frames_ = RR_FormationSappho001_LaunchInterval(_RANK_);  //�p���X�̊Ԋu(frame)
    for (int i = 0; i < num_Sappho_; i++) {
        std::string name = "Sappho("+XTOS(i)+")";
        addFormationMember(NEW EnemySappho(name.c_str()));
    }
    cnt_call_up_ = 0;
}
void FormationSappho001::initialize() {
}

void FormationSappho001::onActive() {
}

void FormationSappho001::processBehavior() {
    if (canCallUp() && getActiveFrame() % interval_frames_ == 0) {
        EnemySappho* pSappho = (EnemySappho*)callUpMember();
        if (pSappho) {
            onCallUpSappho(pSappho, cnt_call_up_);  //�R�[���o�b�N
            cnt_call_up_++;
        }
    }
}

void FormationSappho001::onDestroyAll(GgafActor* prm_pActor_last_destroyed) {
    UTIL::proceedFormationDestroyAll((GgafDxDrawableActor*)prm_pActor_last_destroyed);
}

FormationSappho001::~FormationSappho001() {
}
