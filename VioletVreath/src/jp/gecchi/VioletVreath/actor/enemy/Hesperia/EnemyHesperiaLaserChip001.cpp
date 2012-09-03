
#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;


EnemyHesperiaLaserChip001::EnemyHesperiaLaserChip001(const char* prm_name) :
        HomingLaserChip(prm_name, "HesperiaLaserChip001", STATUS(EnemyHesperiaLaserChip001)) {
    _class_name = "EnemyHesperiaLaserChip001";
    tX1_ = tY1_ = tZ1_ = 0;
    tX2_ = tY2_ = tZ2_ = 0;
    begin_Y_ = 0;
    turn_dY_ = 0;
}

void EnemyHesperiaLaserChip001::initialize() {
    registHitAreaCube(3000);
    setHitAble(true, false);
    setScaleR(5.0);
    setAlpha(0.9);
    _pKurokoA->relateFaceAngWithMvAng(true);
    useProgress(PROG_NOTHING);
}

void EnemyHesperiaLaserChip001::onActive() {
    HomingLaserChip::onActive();
    //�X�e�[�^�X���Z�b�g
    _pStatus->reset();
    begin_Y_ = _Y;
    _pKurokoA->stopTurnMvAngSequence();
    _pKurokoA->setRzMvAngVelo(0);
    _pKurokoA->setRyMvAngVelo(0);
    if (_pChip_front == NULL) {
        _pKurokoA->setMvAng(tX1_, tY1_, tZ1_);
        _pProg->set(PROG_MOVE_UP);
    } else {
        _pProg->set(PROG_NOTHING);
    }
    setAlpha(0.99);
    //���̃����o�[�� EnemyHesperia �ɂ��ݒ�ς݂��O��
    //turn_dY_;
    //tX1_, tY1_, tZ1_;
    //tX2_, tY2_, tZ2_;
}

void EnemyHesperiaLaserChip001::executeHitChk_MeAnd(GgafActor* prm_pOtherActor) {
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

void EnemyHesperiaLaserChip001::processBehavior() {
    HomingLaserChip::processBehavior();
    if (getActivePartFrame() > 180 && _alpha > 0) {
        _alpha -= 0.01;
    }
}
void EnemyHesperiaLaserChip001::processBehaviorHeadChip() {
    MyShip* pMyShip = P_MYSHIP;
    switch (_pProg->get()) {
        case PROG_MOVE_UP: {
            if (!_pKurokoA->isRunnigTurnMvAngSequence()) {
                _pKurokoA->execTurnMvAngSequence(
                             tX1_, tY1_, tZ1_,
                             D_ANG(5), 0,
                             TURN_CLOSE_TO, true);
            }

            if (_Y > begin_Y_+turn_dY_ || _pProg->getFrameInProgress() > 300) {
                _pProg->changeNext();
            }
            break;
        }

        case PROG_TURN1: {
            if (_pProg->isJustChanged()) {
                _pKurokoA->setMvVelo(_pKurokoA->_veloMv/3);
                _pKurokoA->execTurnMvAngSequence(
                             tX2_, tY2_, tZ2_,
                             D_ANG(20), 0,
                             TURN_CLOSE_TO, true);
            }
            if (!_pKurokoA->isRunnigTurnMvAngSequence()) {
                _pProg->changeNext();
            }
            break;
        }

//        case PROG_TURN2: { //�������execTurnMvAngSequence�����s���āA���x�����߂�
//            if (_pProg->isJustChanged()) {
//                _pKurokoA->execTurnMvAngSequence(
//                             tX2_, tY2_, tZ2_,
//                             D_ANG(4), 0,
//                             TURN_CLOSE_TO, true);
//            }
//            if (!_pKurokoA->isRunnigTurnMvAngSequence()) {
//                _pProg->changeNext();
//            }
//            break;
//        }
//
//        case PROG_TURN3: { //�������execTurnMvAngSequence�����s���āA���x�����߂�
//            if (_pProg->isJustChanged()) {
//                _pKurokoA->setMvVelo(_pKurokoA->_veloMv*2);
//                _pKurokoA->execTurnMvAngSequence(
//                             tX2_, tY2_, tZ2_,
//                             D_ANG(3), 0,
//                             TURN_CLOSE_TO, true);
//            }
//            if (!_pKurokoA->isRunnigTurnMvAngSequence()) {
//                _pProg->changeNext();
//            }
//            break;
//        }

        case PROG_INTO_MYSHIP: {
            if (_pProg->isJustChanged()) {
            }
            if (!_pKurokoA->isRunnigTurnMvAngSequence()) {
                _pKurokoA->execTurnMvAngSequence(
                             tX2_, tY2_, tZ2_,
                             200, 0,
                             TURN_CLOSE_TO, false);
            }
            if (_pProg->getFrameInProgress() > 90) {
                _pKurokoA->stopTurnMvAngSequence();
                _pKurokoA->setRzMvAngVelo(0);
                _pKurokoA->setRyMvAngVelo(0);
                _pProg->changeNext();
            }
            break;
        }
        case PROG_NOTHING: {
            break;
        }
    }
    _pKurokoA->behave();
}

void EnemyHesperiaLaserChip001::onHit(GgafActor* prm_pOtherActor) {
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

EnemyHesperiaLaserChip001::~EnemyHesperiaLaserChip001() {
}

