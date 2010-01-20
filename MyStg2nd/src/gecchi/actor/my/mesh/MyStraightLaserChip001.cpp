#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;


MyStraightLaserChip001::MyStraightLaserChip001(const char* prm_name) : StraightLaserChip(prm_name, "12/laser_chip") {
    _class_name = "MyStraightLaserChip001";
    MyStgUtil::resetMyStraightLaserChip001Status(_pStatus);
    _veloMove = 100000;
}

void MyStraightLaserChip001::initialize() {
    _pMover->setMoveVelocity(0);
    _pMover->setMoveVeloAcceleration(300);
    _pMover->setRzRyMoveAngle(0,0);
    registHitAreaCube(30000);
    setBumpable(true);
    _SX = _SY = _SZ = 80*1000;
    _fAlpha = 0.99;
    _max_radius = 20.0;
}

void MyStraightLaserChip001::onActive() {
    StraightLaserChip::onActive();
    MyStgUtil::resetMyStraightLaserChip001Status(_pStatus);
}

void MyStraightLaserChip001::processOnHit(GgafActor* prm_pOtherActor) {
    GgafDx9GeometricActor* pOther = (GgafDx9GeometricActor*)prm_pOtherActor;
    //・・・ココにヒットされたエフェクト
    //playSe1();
    if (MyStgUtil::calcMyStamina(_pStatus, getKind(), pOther->_pStatus, pOther->getKind()) <= 0) {
        //破壊された場合
        //・・・ココに破壊されたエフェクト
        inactivate();
    }

}


MyStraightLaserChip001::~MyStraightLaserChip001() {
}

