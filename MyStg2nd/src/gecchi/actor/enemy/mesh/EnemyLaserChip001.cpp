#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;


EnemyLaserChip001::EnemyLaserChip001(const char* prm_name) : LaserChip(prm_name, "X/laser_chip") {
    _class_name = "EnemyLaserChip001";
    _TRACE_("EnemyLaserChip001::EnemyLaserChip001->");

}

void EnemyLaserChip001::initialize() {
    _TRACE_("EnemyLaserChip001::initialize()->");

    _pGeoMover->setMoveVelocity(30000);
    _pChecker->useHitAreaBoxNum(2);
    _pChecker->setHitAreaBox(0, -10000, -10000, -10000, 10000, 10000, 10000);
    _pChecker->setHitAreaBox(1, -10000, -10000, -10000, 10000, 10000, 10000);
    setBumpable(true);
    _SX=40*1000; _SY=40*1000; _SZ=40*1000;
    _fAlpha = 0.9;
    _TRACE_("<-EnemyLaserChip001::initialize()");
}

void EnemyLaserChip001::processBehavior() {

    //_pGeoMover->setRotAngle(AXIS_X,_pGeoMover->_angRzMove);


    //座標に反映
    _pGeoMover->behave();

    //中間地点にも当たり判定
    static int centerX, centerY, centerZ;
    if (_pChip_front != NULL) {
      centerX = (_X - _pChip_front->_X) / 2;
      centerY = (_Y - _pChip_front->_Y) / 2;
      centerZ = (_Z - _pChip_front->_Z) / 2;
      _pChecker->setHitAreaBox(
                      1,
                      centerX - 10000,
                      centerY - 10000,
                      centerZ - 10000,
                      centerX + 10000,
                      centerY + 10000,
                      centerZ + 10000
                 ); //中間の当たり判定
      _pChecker->getHitAreaBoxs()->enable(1);
    } else {
      _pChecker->getHitAreaBoxs()->disable(1);
    }

}

void EnemyLaserChip001::processJudgement() {
    if (isOffScreen()) {
        inactivateTree();
    }
}


void EnemyLaserChip001::processOnHit(GgafActor* prm_pActor_Opponent) {
}


EnemyLaserChip001::~EnemyLaserChip001() {

}

