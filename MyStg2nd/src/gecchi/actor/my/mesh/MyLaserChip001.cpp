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

    _pGeoMover->setMoveVelocity(30000);
    _pChecker->useHitAreaBoxNum(2);
    _pChecker->setHitAreaBox(0, -10000, -10000, -10000, 10000, 10000, 10000);
    _pChecker->setHitAreaBox(1, -10000, -10000, -10000, 10000, 10000, 10000);
    setBumpable(true);
    _SX=40*1000; _SY=40*1000; _SZ=40*1000;
    _fAlpha = 0.9;
}

void MyLaserChip001::processBehavior() {

    //_pGeoMover->setRotAngle(AXIS_X,_pGeoMover->_angRzMove);


    //À•W‚É”½‰f
    _pGeoMover->behave();

    //’†ŠÔ’n“_‚É‚à“–‚½‚è”»’è
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
                 ); //’†ŠÔ‚Ì“–‚½‚è”»’è
      _pChecker->getHitAreaBoxs()->enable(1);
    } else {
      _pChecker->getHitAreaBoxs()->disable(1);
    }

}

void MyLaserChip001::processJudgement() {
    LaserChip::processJudgement();
}


void MyLaserChip001::processOnHit(GgafActor* prm_pActor_Opponent) {
}


MyLaserChip001::~MyLaserChip001() {

}

