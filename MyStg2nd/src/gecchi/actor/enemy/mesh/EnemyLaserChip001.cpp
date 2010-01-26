#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;


EnemyLaserChip001::EnemyLaserChip001(const char* prm_name) : HomingLaserChip(prm_name, "12/laser_chip") {
    _class_name = "EnemyLaserChip001";
}

void EnemyLaserChip001::initialize() {
    _pMover->setMoveVelocity(1000);
    _pCollisionChecker->makeCollision(1);
    _pCollisionChecker->setColliBox(0, -10000, -10000, -10000, 10000, 10000, 10000);
    setHitAble(true);
    _SX = _SY = _SZ = 80*1000;
    _fAlpha = 0.9f;
    _max_radius = 5.0f;
    _paD3DMaterial9[0].Diffuse = D3DXCOLOR(1.0, 0.0, 0.0, 1.0);
}

void EnemyLaserChip001::onActive() {
    HomingLaserChip::onActive();
    _pMover->setMoveVelocity(3000);
    _pMover->setMoveVeloAcceleration(300);
}


void EnemyLaserChip001::processBehaviorHeadChip() {


    if (_dwActiveFrame == 30) {
        _pMover->executeTagettingMoveAngleSequence(
                    GameGlobal::_pMyShip,
                    7000, 0,
                    TURN_ANTICLOSE_TO);
    }


//    if (_dwActiveFrame == 50) {
//        _pMover->executeTagettingMoveAngleSequence(
//                    GameGlobal::_pMyShip,
//                    8000, TURN_CLOSE_TO);
//    }
//
//    if (_dwActiveFrame == 35) {
//        _pMover->executeTagettingMoveAngleSequence(
//                    GameGlobal::_pMyShip,
//                    20000, TURN_ANTICLOSE_TO);
//    }

    _pMover->behave();
}



void EnemyLaserChip001::onHit(GgafActor* prm_pOtherActor) {
}


EnemyLaserChip001::~EnemyLaserChip001() {

}

