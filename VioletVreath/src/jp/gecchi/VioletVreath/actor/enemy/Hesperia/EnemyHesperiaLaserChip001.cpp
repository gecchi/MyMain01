
#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;


EnemyHesperiaLaserChip001::EnemyHesperiaLaserChip001(const char* prm_name) :
        HomingLaserChip(prm_name, "HesperiaLaserChip001", STATUS(EnemyHesperiaLaserChip001)) {
    _class_name = "EnemyHesperiaLaserChip001";
    tX_ = tY_ = tZ_ = 0;
}

void EnemyHesperiaLaserChip001::initialize() {
    registHitAreaCube(3000);
    setHitAble(true, false);
    setScaleR(5.0);
    setAlpha(0.9);
    useProgress(PROG_NOTHING);
}

void EnemyHesperiaLaserChip001::onActive() {
    HomingLaserChip::onActive();
    //ステータスリセット
    _pStatus->reset();
    _pKurokoA->relateFaceAngWithMvAng(true);
    _pProg->set(PROG_MOVE_UP);
    _pKurokoA->setMvVelo(20000);
    _pKurokoA->setMvAcce(0);
    //[メモ] tX_ , tY_ , tZ_  は EnemyHesperia により設定されている。
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

void EnemyHesperiaLaserChip001::processBehaviorHeadChip() {
    MyShip* pMyShip = P_MYSHIP;
    switch (_pProg->get()) {
        case PROG_MOVE_UP: {
            if (_pProg->isJustChanged()) {
                _TRACE_("PROG_MOVE_UP _pProg->isJustChanged()");
            }
            //frame f = _pProg->getFrameInProgress();
            //if ((f > 3 && pMyShip->_Y < _Y) || f > 10) {
            if (_pProg->getFrameInProgress() > 120) {
                _pProg->changeNext();
            }
            break;
        }

        case PROG_TURN: {
//            if (_pProg->isJustChanged()) {
//                _pKurokoA->execTurnMvAngSequence(
//                            tX_ , tY_ , tZ_,
//                            D_ANG(20), 0,
//                            TURN_CLOSE_TO, true);
//            }
//            if (!_pKurokoA->isRunnigTurnMvAngSequence()) {
//                _pProg->changeNext();
//            }
            _pKurokoA->execTurnMvAngSequence(
                        tX_ , tY_ , tZ_,
                        D_ANG(20), 0,
                        TURN_CLOSE_TO, true);
            if (_pProg->getFrameInProgress() > 120 || !_pKurokoA->isRunnigTurnMvAngSequence()) {
                _pProg->changeNext();
            }
            break;
        }

        case PROG_INTO_MYSHIP: {
            if (_pProg->isJustChanged()) {
                _pKurokoA->setMvVelo(70000);
                _pKurokoA->setMvAcce(100);
            }

            if (!_pKurokoA->isRunnigTurnMvAngSequence()) {
                _pKurokoA->execTurnMvAngSequence(
                            tX_ , tY_ , tZ_,
                            100, 0,
                            TURN_CLOSE_TO, false);
            }
            break;
        }
        case PROG_NOTHING: {
            break;
        }
    }

//
//    if (frame_of_behaving_from_onActive_ == 35) {
//        _pKurokoA->execTurnMvAngSequence(
//                    P_MYSHIP,
//                    20000, TURN_ANTICLOSE_TO);
//    }

    _pKurokoA->behave();
}

void EnemyHesperiaLaserChip001::onHit(GgafActor* prm_pOtherActor) {
    GgafDxGeometricActor* pOther = (GgafDxGeometricActor*)prm_pOtherActor;
    //ヒット時
    //体力計算
    int sta = UTIL::calcEnemyStamina(this, pOther);
    if (sta <= 0) {
        //ヒットして消滅時
        sayonara();
    } else {
        //ヒットして生存時
    }
}

EnemyHesperiaLaserChip001::~EnemyHesperiaLaserChip001() {

}

