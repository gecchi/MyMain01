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
}
void FormationSappho001::initialize() {
}

void FormationSappho001::onActive() {
}

void FormationSappho001::processBehavior() {
    if (canCallUp() && getActivePartFrame() % interval_frames_ == 0) {
        EnemySappho* p = (EnemySappho*)callUp();
        if (p) {
            p->activate();
            onCallUpSappho(p);  //�R�[���o�b�N
        }
    }
}

void FormationSappho001::onDestroyAll(GgafActor* prm_pActor_last_destroyed) {
    GgafDxGeometricActor* pActor_last_destroyed = (GgafDxGeometricActor*)prm_pActor_last_destroyed;
    //�ґ��S�Ŏ��G�t�F�N�g�o���i�X�R�A���Z���s����j
    UTIL::activateFormationDestroyedEffectOf(pActor_last_destroyed);
    //�ґ��S�ŃA�C�e���o��
    UTIL::activateFormationDestroyedItemOf(pActor_last_destroyed);
}



FormationSappho001::~FormationSappho001() {
}
