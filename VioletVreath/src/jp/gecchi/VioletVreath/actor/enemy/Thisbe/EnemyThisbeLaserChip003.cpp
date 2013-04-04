#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;


EnemyThisbeLaserChip003::EnemyThisbeLaserChip003(const char* prm_name) :
        WateringLaserChip(prm_name, "ThisbeLaserChip003", STATUS(EnemyThisbeLaserChip003)) {
    _class_name = "EnemyThisbeLaserChip003";
    pSplManufConnection_ = connectToSplineManufactureManager("EnemyThisbeLaserChip003"); //�S�X�p�[�Ȑ�
    pKurokoStepper_ = pSplManufConnection_->peek()->createSplineKurokoStepper(_pKurokoA);
    pKurokoStepper_->adjustCoordOffset(PX_C(100), 0, 0);
    sp_index_ = 0;
    pNearestScrollingScene_ = nullptr;
}

void EnemyThisbeLaserChip003::initialize() {
    registHitAreaCube_AutoGenMidColli(20000);
    setHitAble(true, false);
    setScaleR(5.0);
    setAlpha(0.9);

    _pKurokoA->relateMvFaceAng(true);
    sp_index_ = 0;
    pNearestScrollingScene_ = ((DefaultScene*)getPlatformScene())->getNearestScrollingScene();
}

void EnemyThisbeLaserChip003::onActive() {
    WateringLaserChip::onActive();
    //�X�e�[�^�X���Z�b�g
    _pStatus->reset();
    pKurokoStepper_->start(SplineKurokoStepper::RELATIVE_DIRECTION); //���Ă�����ɃX�v���C�����W�����[���h�ϊ�
    sp_index_ = 0;
}

void EnemyThisbeLaserChip003::processBehavior() {
    if (pNearestScrollingScene_->_pFuncScrolling == WalledScene::scrollX) {
        pKurokoStepper_->_X_begin -= pNearestScrollingScene_->getScrollSpeed();
    }

    if (pKurokoStepper_->isStepping()) {
        _pKurokoA->setMvVelo(pKurokoStepper_->getSegmentDistance(sp_index_));
        sp_index_++;
    } else {
        sayonara();
    }
    //pKurokoStepper_->behave(); ������ pKurokoA->_veloMv ���Q�Ƃ����t���[�������肵�Ă�̂ŁA
    //�P�t���[���Ŏ��̓_�ɓ��B����ׂ��ApKurokoStepper_->behave(); �̑O�� pKurokoA->setMvVelo() �Őݒ肵�Ȃ���΂����Ȃ��B
    pKurokoStepper_->behave();
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
    GGAF_DELETE(pKurokoStepper_);
    pSplManufConnection_->close();
}

