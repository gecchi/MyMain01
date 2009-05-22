#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;


MyLaserChip001::MyLaserChip001(const char* prm_name) : LaserChip(prm_name, "X/laser_chip") {
    _class_name = "MyLaserChip001";
}

void MyLaserChip001::initialize() {

    _pMover->setMoveVelocity(40000);
    _pStgChecker->useHitAreaBoxNum(1);
    _pStgChecker->setHitAreaBox(0, -30000, -30000, -30000, 30000, 30000, 30000);
    setBumpable(true);
    _SX = _SY = _SZ = 40*1000;
    _fAlpha = 0.9;
}

void MyLaserChip001::processBehavior() {
	LaserChip::processBehavior();
}

void MyLaserChip001::processJudgement() {
    LaserChip::processJudgement();
}


void MyLaserChip001::processOnHit(GgafActor* prm_pActor_Opponent) {
}


MyLaserChip001::~MyLaserChip001() {
}

