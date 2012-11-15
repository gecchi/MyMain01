#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;


EnemyThisbeLaserChip003::EnemyThisbeLaserChip003(const char* prm_name) :
        WateringLaserChip(prm_name, "ThisbeLaserChip003", STATUS(EnemyThisbeLaserChip003)) {
    _class_name = "EnemyThisbeLaserChip003";
    pSplManufCon_ = connectToSplineManufactureManager("EnemyThisbeLaserChip003"); //�q���x���g�Ȑ�
    pSplSeq_ = pSplManufCon_->fetch()->createSplineSequence(_pKurokoA);
    pSplSeq_->adjustCoordOffset(PX_C(100), 0, 0);
    setMiddleColliAble(true); //�`�b�v�ԓ����蔻�莩������
}

void EnemyThisbeLaserChip003::initialize() {
    registHitAreaCube(20000);
    setHitAble(true, false);
    setScaleR(5.0);
    setAlpha(0.9);

    _pKurokoA->relateFaceAngWithMvAng(true);
    sp_index_ = 0;
}

void EnemyThisbeLaserChip003::onActive() {
    WateringLaserChip::onActive();
    //�X�e�[�^�X���Z�b�g
    _pStatus->reset();
    pSplSeq_->exec(SplineSequence::RELATIVE_DIRECTION); //���Ă�����ɃX�v���C�����W�����[���h�ϊ�
    sp_index_ = 0;
}

void EnemyThisbeLaserChip003::processBehavior() {
    if (pSplSeq_->isExecuting()) {
        _pKurokoA->setMvVelo(pSplSeq_->getSegmentDistance(sp_index_));
        sp_index_++;
    } else {
        sayonara();
    }
    //pSplSeq_->behave(); ������ pKurokoA->_veloMv ���Q�Ƃ����t���[�������肵�Ă�̂ŁA
    //�P�t���[���Ŏ��̓_�ɓ��B����ׂ��ApSplSeq_->behave(); �̑O�� pKurokoA->setMvVelo() �Őݒ肵�Ȃ���΂����Ȃ��B
    pSplSeq_->behave();
    _pKurokoA->behave();
    WateringLaserChip::processBehavior();
}
void EnemyThisbeLaserChip003::processSettlementBehavior() {
    //�p���ۂ߂����Ȃ��̂ŃI�[�o�[���C�h
    if (_was_paused_flg) {
        GgafDxGeometricActor::processSettlementBehavior();
    } else {
        LaserChip::processSettlementBehavior();
    }
}

void EnemyThisbeLaserChip003::onHit(GgafActor* prm_pOtherActor) {
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
void EnemyThisbeLaserChip003::onInactive() {
    WateringLaserChip::onInactive();
}

EnemyThisbeLaserChip003::~EnemyThisbeLaserChip003() {
    DELETE_IMPOSSIBLE_NULL(pSplSeq_);
    pSplManufCon_->close();
}

