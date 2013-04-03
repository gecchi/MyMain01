#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;


EnemyThisbeLaserChip002::EnemyThisbeLaserChip002(const char* prm_name) :
        RefractionLaserChip(prm_name, "ThisbeLaserChip002", STATUS(EnemyThisbeLaserChip002)) {
    _class_name = "EnemyThisbeLaserChip002";
    pSplManufConnection_ = connectToSplineManufactureManager("EnemyThisbeLaserChip002"); //�q���x���g�Ȑ�
    pSplSeq_ = pSplManufConnection_->peek()->createSplineSequence(_pKurokoA);
    pSplSeq_->adjustCoordOffset(PX_C(100), 0, 0);
    end_active_frame_ = 0;
    pNearestScrollingScene_ = nullptr;
}

void EnemyThisbeLaserChip002::initialize() {
    registHitAreaCube_AutoGenMidColli(20000);
    setHitAble(true, false);
    setScaleR(5.0);
    setAlpha(0.9);
    pNearestScrollingScene_ = ((DefaultScene*)getPlatformScene())->getNearestScrollingScene();
}

void EnemyThisbeLaserChip002::onActive() {
    RefractionLaserChip::onActive();
    //�X�e�[�^�X���Z�b�g
    _pStatus->reset();
    _pKurokoA->relateMvFaceAng(true);
    end_active_frame_ = (_frame_standstill_refraction * _num_refraction     ) +
                        (_frame_between_refraction    * (_num_refraction-1) ) +
                        1; //

}

void EnemyThisbeLaserChip002::executeHitChk_MeAnd(GgafActor* prm_pOtherActor) {
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

void EnemyThisbeLaserChip002::onRefractionBegin(int prm_num_refraction)  {

}

void EnemyThisbeLaserChip002::onRefractionFinish(int prm_num_refraction)  {
    if (prm_num_refraction == 0) {
        pSplSeq_->exec(SplineSequence::RELATIVE_DIRECTION); //���Ă�����ɃX�v���C�����W�����[���h�ϊ�
        //prm_num_refraction = 0 �́A���ˌ���pSplSeq_->_point_index = 0 �̓_�ւ̈ړ����O����
    }
    if (pSplSeq_->isExecuting()) {
        _pKurokoA->setMvVelo(pSplSeq_->getSegmentDistance(prm_num_refraction));
    } else {
        //�Ō�̃��t���N�V�����������ꍇ
        _pKurokoA->setMvVelo(0); //������� sayonara() �܂őҋ@
    }
    //pSplSeq_->behave(); ������ pKurokoA->_veloMv ���Q�Ƃ����t���[�������肵�Ă�̂ŁA
    //�P�t���[���Ŏ��̓_�ɓ��B����ׂ��ApSplSeq_->behave(); �̑O�� pKurokoA->setMvVelo() �Őݒ肵�Ȃ���΂����Ȃ��B
    pSplSeq_->behave();
    _pKurokoA->behave();
}

void EnemyThisbeLaserChip002::processBehavior() {
    if (pNearestScrollingScene_->_pFuncScrolling == WalledScene::scrollX) {
        pSplSeq_->_X_begin -= pNearestScrollingScene_->getScrollSpeed();
    }

    RefractionLaserChip::processBehavior();
    if (getActivePartFrame() == end_active_frame_+5) {
        sayonara();
    }
}

void EnemyThisbeLaserChip002::processJudgement() {
    // ���end_active_frame_ +5 �� sayonara �����Ŕ���s�v�B
//    if (isOutOfUniverse()) {
//        if (_X >= GgafDxUniverse::_X_gone_right) {
//            //WALL������
//        } else {
//            sayonara();
//        }
//    }
}

void EnemyThisbeLaserChip002::onHit(GgafActor* prm_pOtherActor) {
//    GgafDxGeometricActor* pOther = (GgafDxGeometricActor*)prm_pOtherActor;
//    //�q�b�g��
//
//    //�̗͌v�Z
//    if (UTIL::calcEnemyStamina(this, pOther) <= 0) {
//        //�q�b�g���ď��Ŏ�
//        sayonara();
//    } else {
//        //�q�b�g���Đ�����
//    }
}

EnemyThisbeLaserChip002::~EnemyThisbeLaserChip002() {
    GGAF_DELETE(pSplSeq_);
    pSplManufConnection_->close();
}


