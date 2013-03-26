#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;


EnemyThisbeLaserChip001::EnemyThisbeLaserChip001(const char* prm_name) :
        HomingLaserChip(prm_name, "ThisbeLaserChip001", STATUS(EnemyThisbeLaserChip001)) {
    _class_name = "EnemyThisbeLaserChip001";
    pSplManufCon_ = connectToSplineManufactureManager("EnemyThisbeLaserChip002"); //�q���x���g�Ȑ�
    pSplSeq_ = pSplManufCon_->fetch()->createSplineSequence(_pKurokoA);
}

void EnemyThisbeLaserChip001::initialize() {
//    registHitAreaCube_AutoGenMidColli(20000);
    setScaleR(5.0);
    setAlpha(0.9);
}
void EnemyThisbeLaserChip001::onActive() {
    HomingLaserChip::onActive();
    //�X�e�[�^�X���Z�b�g
    _pStatus->reset();
    _pKurokoA->setMvVelo(30000);
    _pKurokoA->relateMvFaceAng(true);
    //�ʒu�ƌ�����EnemyThisbe���ݒ�
    pSplSeq_->stop();
}

void EnemyThisbeLaserChip001::executeHitChk_MeAnd(GgafActor* prm_pOtherActor) {
    if (((GgafMainActor*)prm_pOtherActor)->getKind() & KIND_CHIKEI) {
        if (_chip_kind != 2 || _can_chikei_hit) {
            GgafDxDrawableActor::executeHitChk_MeAnd(prm_pOtherActor);
        } else {
            return;
        }
    } else {
        GgafDxDrawableActor::executeHitChk_MeAnd(prm_pOtherActor);
    }
}

void EnemyThisbeLaserChip001::processBehaviorHeadChip() {
    pSplSeq_->_X_begin -= 5000;
    //TODO:��������ǂ���邩�E�E�E�E

    if (getActivePartFrame() == 2) {
        pSplSeq_->exec(SplineSequence::RELATIVE_DIRECTION); //�����������Ƀ��[���h�ϊ�
    }
    pSplSeq_->behave();
    _pKurokoA->behave();
}

//void EnemyThisbeLaserChip001::processBehavior() {
//    HomingLaserChip::processBehavior();
//}
void EnemyThisbeLaserChip001::processJudgement() {
    if (isOutOfUniverse()) {
        if (_X >= GgafDxUniverse::_X_gone_right) {
            //WALL������
        } else {
            sayonara();
        }
    }
}

void EnemyThisbeLaserChip001::onHit(GgafActor* prm_pOtherActor) {
    GgafDxGeometricActor* pOther = (GgafDxGeometricActor*)prm_pOtherActor;
    //�q�b�g��
    //�̗͌v�Z
    int sta = UTIL::calcEnemyStamina(this, pOther);
    if (sta <= 0) {
        //�q�b�g���ď��Ŏ�
        sayonara();
    } else {
        //�q�b�g���Đ�����
    }
}

EnemyThisbeLaserChip001::~EnemyThisbeLaserChip001() {
    GGAF_DELETE(pSplSeq_);
    pSplManufCon_->close();
}

