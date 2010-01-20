#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;


MyCurveLaserChip001::MyCurveLaserChip001(const char* prm_name) : CurveLaserChip(prm_name, "12/laser_chip") {
    _class_name = "MyCurveLaserChip001";
    MyStgUtil::resetMyCurveLaserChip001Status(_pStatus);
}

void MyCurveLaserChip001::initialize() {
    _pMover->setMoveVelocity(100000);
    _pMover->setMoveVeloAcceleration(300);

    registHitAreaCube(20000);

    setBumpable(true);
    _SX = _SY = _SZ = 80*1000;
    _fAlpha = 0.99f;
    _max_radius = 20.0f;
}

void MyCurveLaserChip001::onActive() {
    CurveLaserChip::onActive();
    MyStgUtil::resetMyCurveLaserChip001Status(_pStatus);
}

void MyCurveLaserChip001:: processBehavior() {;
    CurveLaserChip::processBehavior();
}

void MyCurveLaserChip001::processOnHit(GgafActor* prm_pOtherActor) {
    GgafDx9GeometricActor* pOther = (GgafDx9GeometricActor*)prm_pOtherActor;
    //ここにMyのヒットエフェクト
    if (MyStgUtil::calcMyStamina(_pStatus, getKind(), pOther->_pStatus, pOther->getKind()) <= 0) {
        //ここにMyの消滅エフェクト
        inactivate();
    } else {

    }
}


MyCurveLaserChip001::~MyCurveLaserChip001() {
}

