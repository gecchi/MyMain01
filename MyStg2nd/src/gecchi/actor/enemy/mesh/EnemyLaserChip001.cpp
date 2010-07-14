#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;


EnemyLaserChip001::EnemyLaserChip001(const char* prm_name) : HomingLaserChip(prm_name, "11/LaserChip_red") {
    _class_name = "EnemyLaserChip001";
}

void EnemyLaserChip001::initialize() {
    _pMover->setMvVelo(1000);
    _pCollisionChecker->makeCollision(1);
    _pCollisionChecker->setColliAAB(0, -10000, -10000, -10000, 10000, 10000, 10000);
    setHitAble(true);
    _SX = _SY = _SZ = 80*1000;
    _fAlpha = 0.9f;
    _fBoundingSphereRadius = 5.0f;
    _paD3DMaterial9[0].Diffuse = D3DXCOLOR(1.0, 0.0, 0.0, 1.0);
}

void EnemyLaserChip001::onActive() {
    HomingLaserChip::onActive();
    _pMover->setMvVelo(3000);
    _pMover->setMvAcce(300);
}


void EnemyLaserChip001::processBehaviorHeadChip() {


    if (getPartFrame() == 30) {
        _pMover->execTagettingMvAngSequence(
                    GameGlobal::_pMyShip,
                    7000, 0,
                    TURN_ANTICLOSE_TO);
    }


//    if (_frame_of_behaving_from_onActive == 50) {
//        _pMover->execTagettingMvAngSequence(
//                    GameGlobal::_pMyShip,
//                    8000, TURN_CLOSE_TO);
//    }
//
//    if (_frame_of_behaving_from_onActive == 35) {
//        _pMover->execTagettingMvAngSequence(
//                    GameGlobal::_pMyShip,
//                    20000, TURN_ANTICLOSE_TO);
//    }

    _pMover->behave();
}



void EnemyLaserChip001::onHit(GgafActor* prm_pOtherActor) {
}


EnemyLaserChip001::~EnemyLaserChip001() {

}

