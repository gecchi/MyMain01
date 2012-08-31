
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
    _pKurokoA->relateFaceAngWithMvAng(true);
    useProgress(PROG_NOTHING);
}

void EnemyHesperiaLaserChip001::onActive() {
    HomingLaserChip::onActive();
    //ステータスリセット
    _pStatus->reset();

    begin_Y_ = _Y;
    MyShip* pMyShip = P_MYSHIP;
    coord dX = ABS(_X - pMyShip->_X);
    coord dZ = ABS(_Z - pMyShip->_Z);
    turn_dY_ = EnemyHesperia::getTurnDY(this, pMyShip, (dX > dZ ? dX : dZ) );
    //↑turn_dY_ の式は  EnemyHesperia::processBehavior() の turn_dY と同期を取る事

    //[メモ]発射元のEnemyHesperiaにより、以下の設定が既に施されている
    //    //発射元座標
    //    pLaserChip->locate(_X+p->_X, _Y+p->_Y, _Z+p->_Z);
    //    //折り返す地点へ向ける
    //    pLaserChip->_pKurokoA->setMvAng(_X + paPos_Target_->_X,
    //                                    _Y + paPos_Target_->_Y + turn_dY,
    //                                    _Z + paPos_Target_->_Z);
    //    pLaserChip->_pKurokoA->setMvVelo(40000);
    //    pLaserChip->_pKurokoA->setMvAcce(100+(max_laser_way_-i)*100);
    //    //最終目標地点を設定
    //    pLaserChip->tX_ = pMyShip->_X + paPos_Target_[i]._X;
    //    pLaserChip->tY_ = pMyShip->_Y + paPos_Target_[i]._Y;
    //    pLaserChip->tZ_ = pMyShip->_Z + paPos_Target_[i]._Z;
    _pProg->set(PROG_MOVE_UP);
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
            if (_Y > begin_Y_+turn_dY_ || _pProg->getFrameInProgress() > 300) {
                _pProg->changeNext();
            }
            break;
        }

        case PROG_TURN1: {
            if (_pProg->isJustChanged()) {
                _pKurokoA->execTurnMvAngSequence(
                             tX_, tY_, tZ_,
                             D_ANG(20), 0,
                             TURN_CLOSE_TO, true);
            }
            if (!_pKurokoA->isRunnigTurnMvAngSequence()) {
                _pProg->changeNext();
            }
            break;
        }

        case PROG_TURN2: { //もう一回execTurnMvAngSequenceを実行して、精度を高める
            if (_pProg->isJustChanged()) {
                _pKurokoA->execTurnMvAngSequence(
                             tX_, tY_, tZ_,
                             D_ANG(20), 0,
                             TURN_CLOSE_TO, true);
            }
            if (!_pKurokoA->isRunnigTurnMvAngSequence()) {
                _pProg->changeNext();
            }
            break;
        }

        case PROG_INTO_MYSHIP: {
            if (_pProg->isJustChanged()) {
            }

            if (!_pKurokoA->isRunnigTurnMvAngSequence()) {
                _pKurokoA->execTurnMvAngSequence(
                             tX_, tY_, tZ_,
                             100, 0,
                             TURN_CLOSE_TO, true);
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

