
#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;


EnemyAstraeaLaserChip001::EnemyAstraeaLaserChip001(const char* prm_name) : HomingLaserChip(prm_name, "12/laser_chip_red") {
    _class_name = "EnemyAstraeaLaserChip001";
    MyStgUtil::resetEnemyAstraeaLaserChip001Status(_pStatus);
}

void EnemyAstraeaLaserChip001::initialize() {
    _pStgChecker->useHitAreaBoxNum(1);
    _pStgChecker->setHitAreaBox(0, -10000, -10000, -10000, 10000, 10000, 10000);
    setBumpable(true);
    _SX = _SY = _SZ = 80*1000;
    _fAlpha = 0.9f;
    _max_radius = 5.0f;
    _paD3DMaterial9[0].Diffuse = D3DXCOLOR(1.0, 0.0, 0.0, 1.0);

}

void EnemyAstraeaLaserChip001::onActive() {
    HomingLaserChip::onActive();
    //ステータスリセット
    MyStgUtil::resetEnemyAstraeaLaserChip001Status(_pStatus);

    _pMover->setMoveVelocity(5000);
    _pMover->setMoveVeloAcceleration(300);
    _pMover->relateRzRyFaceAngleToMoveAngle(true);
}

void EnemyAstraeaLaserChip001::processBehavior() {
    HomingLaserChip::processBehavior();
}

void EnemyAstraeaLaserChip001::processBehaviorHeadChip() {
    if (_dwActiveFrame == 40) {
        _pMover->executeTagettingMoveAngleSequence(
                    GameGlobal::_pMyShip,
                    8000, TURN_ANTICLOSE_TO);
    }


    if (_pMover->_move_angle_ry_target_flg == false && _pMover->_move_angle_rz_target_flg == false) {
        _pMover->executeTagettingMoveAngleSequence(
                    GameGlobal::_pMyShip,
                    100, TURN_CLOSE_TO);
    }
//
//    if (_dwActiveFrame == 35) {
//        _pMover->executeTagettingMoveAngleSequence(
//                    GameGlobal::_pMyShip,
//                    20000, TURN_ANTICLOSE_TO);
//    }

    _pMover->behave();
}

void EnemyAstraeaLaserChip001::processJudgement() {
    HomingLaserChip::processJudgement();
}

void EnemyAstraeaLaserChip001::processOnHit(GgafActor* prm_pOtherActor) {
//    GgafDx9GeometricActor* pOther = (GgafDx9GeometricActor*)prm_pOtherActor;
//    //ヒット時
//
//    //体力計算
//    if (MyStgUtil::calcEnemyStamina(_pStatus, getKind(), pOther->_pStatus, pOther->getKind()) <= 0) {
//        //ヒットして消滅時
//        inactivate();
//    } else {
//        //ヒットして生存時
//    }
}
void EnemyAstraeaLaserChip001::onInactive() {
    HomingLaserChip::onInactive();

}

EnemyAstraeaLaserChip001::~EnemyAstraeaLaserChip001() {

}

