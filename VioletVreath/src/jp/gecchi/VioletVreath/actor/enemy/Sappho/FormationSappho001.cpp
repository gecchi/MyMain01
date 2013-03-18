#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

FormationSappho001::FormationSappho001(const char* prm_name) :
        TreeFormation(prm_name, 30*60) {
    _class_name = "FormationSappho001";
    num_Sappho_      = RR_FormationSappho001_Num(_RANK_);    //�ґ���
    interval_frames_ = RR_FormationSappho001_LaunchInterval(_RANK_);  //�p���X�̊Ԋu(frame)
    velo_mv_         = RR_FormationSappho001_MvVelo(_RANK_); //���x
    pDepoCon_ = nullptr;
    SplineSequence* pSplSeq;
    for (int i = 0; i < num_Sappho_; i++) {
        EnemySappho* pSappho = NEW EnemySappho("Sappho01");
        pSappho->inactivateImmed();
        addSubLast(pSappho);
    }
    can_fetch_ = true;
}
void FormationSappho001::initialize() {
}

void FormationSappho001::onActive() {
}

void FormationSappho001::processBehavior() {
    if (can_fetch_ && getActivePartFrame() % interval_frames_ == 0) {
        EnemySappho* pSappho = (EnemySappho*)fetchSub();
        if (pSappho) {
            pSappho->activate();
            onActiveSappho(pSappho);  //�R�[���o�b�N
        } else {
            can_fetch_ = false;
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
