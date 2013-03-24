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
    pSplManufCon_ = connectToSplineManufactureManager("Pallas01");
    pDepoCon_ = nullptr;
    for (int i = 0; i < num_Pallas_; i++) {
        EnemyPallas* pPallas= NEW EnemyPallas("Pallas01");
        SplineSequence* pSplSeq = pSplManufCon_->fetch()->createSplineSequence(pPallas->_pKurokoA);
        pPallas->config(pSplSeq, nullptr, nullptr);
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
            pPallas->activateDelay(n*interval_frames_ + 1);
            n++;
        }
    }
    //FormationTableScene �ɒǉ�����ґ��̏ꍇ�A
    //�ґ����r���ł����؂�鎖��h�����߂ɁA���̂悤��
    //onActive()�ŁA��C�ɑS�Ă̕ґ��v���� callUpMember() & activate() ���Ă������B
}

void FormationPallas001::processBehavior() {
}

void FormationPallas001::onDestroyAll(GgafActor* prm_pActor_last_destroyed) {
    GgafDxGeometricActor* pActor_last_destroyed = (GgafDxGeometricActor*)prm_pActor_last_destroyed;
    //�ґ��S�Ŏ��G�t�F�N�g�o���i�X�R�A���Z���s����j
    UTIL::activateFormationDestroyedEffectOf(pActor_last_destroyed);
    //�ґ��S�ŃA�C�e���o��
    UTIL::activateFormationDestroyedItemOf(pActor_last_destroyed);
}

FormationPallas001::~FormationPallas001() {
    pSplManufCon_->close();
    if (pDepoCon_) {
        pDepoCon_->close();
    }
}
