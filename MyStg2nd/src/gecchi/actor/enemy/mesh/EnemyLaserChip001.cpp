#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;


EnemyLaserChip001::EnemyLaserChip001(const char* prm_name) : CurveLaserChip(prm_name, "laser_chip") {
    _class_name = "EnemyLaserChip001";
}

void EnemyLaserChip001::initialize() {
    _pMover->setMoveVelocity(60000);
    _pStgChecker->useHitAreaBoxNum(1);
    _pStgChecker->setHitAreaBox(0, -10000, -10000, -10000, 10000, 10000, 10000);
    setBumpable(true);
    _SX = _SY = _SZ = 80*1000;
    _fAlpha = 0.9;
    _max_radius = 5.0;
}

void EnemyLaserChip001::processOnHit(GgafActor* prm_pActor_Opponent) {
}


EnemyLaserChip001::~EnemyLaserChip001() {

}

