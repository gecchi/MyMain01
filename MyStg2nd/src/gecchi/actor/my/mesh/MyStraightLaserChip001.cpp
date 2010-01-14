#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;


MyStraightLaserChip001::MyStraightLaserChip001(const char* prm_name) : StraightLaserChip(prm_name, "12/laser_chip") {
    _class_name = "MyStraightLaserChip001";
    MyStgUtil::resetMyStraightLaserChip001Status(this);
    _veloMove = 100000;
}

void MyStraightLaserChip001::initialize() {
    _pMover->setMoveVelocity(0);
    _pMover->setMoveVeloAcceleration(300);
    _pMover->setRzRyMoveAngle(0,0);
    _pStgChecker->useHitAreaBoxNum(1);
    _pStgChecker->setHitAreaBox(0, -30000, -30000, -30000, 30000, 30000, 30000);
    setBumpable(true);
    _SX = _SY = _SZ = 80*1000;
    _fAlpha = 0.99;
    _max_radius = 20.0;
}

void MyStraightLaserChip001::onActive() {
    StraightLaserChip::onActive();
    MyStgUtil::resetMyStraightLaserChip001Status(this);
}

void MyStraightLaserChip001::processOnHit(GgafActor* prm_pOtherActor) {
    //ここにMyのヒットエフェクト
    if (MyStgUtil::calMyStamina(this, prm_pOtherActor) <= 0) {
        //ここにMyの消滅エフェクト
        inactivate();
    } else {

    }

}


MyStraightLaserChip001::~MyStraightLaserChip001() {
}

