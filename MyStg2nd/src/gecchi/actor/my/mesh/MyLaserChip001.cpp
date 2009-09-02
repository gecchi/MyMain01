#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;


MyLaserChip001::MyLaserChip001(const char* prm_name) : CurveLaserChip(prm_name, "laser_chip") {
    _class_name = "MyLaserChip001";
}

void MyLaserChip001::initialize() {
    _pMover->setMoveVelocity(100000);
    _pStgChecker->useHitAreaBoxNum(1);
    _pStgChecker->setHitAreaBox(0, -30000, -30000, -30000, 30000, 30000, 30000);
    setBumpable(true);
    _SX = _SY = _SZ = 40*1000;
    _fAlpha = 0.9f;
    _max_radius = 10.0f;
}

void MyLaserChip001::processOnHit(GgafActor* prm_pActor_Opponent) {
}


MyLaserChip001::~MyLaserChip001() {
}

