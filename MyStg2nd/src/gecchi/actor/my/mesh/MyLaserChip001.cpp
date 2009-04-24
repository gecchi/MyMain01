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
    _SY=50*1000; _SZ=50*1000;
    _fAlpha = 0.9;
}

void MyLaserChip001::processJudgement() {
    if (isOffScreen()) {
        inactivateTree();
    }
}


void MyLaserChip001::processOnHit(GgafActor* prm_pActor_Opponent) {
}


bool MyLaserChip001::isOffScreen() {
    if (_X < _X_OffScreenLeft*2) {
        return true;
    } else {
        if (_X > _X_OffScreenRight*2) {
            return true;
        } else {
            if (_Y > _Y_OffScreenTop*2) {
                return true;
            } else {
                if (_Y < _Y_OffScreenBottom*2) {
                    return true;
                } else {
                    if (_Z < GgafDx9God::_dCamZ * LEN_UNIT * PX_UNIT * 10) {
                        return true;
                    } else {
                        if (_Z > -1 * GgafDx9God::_dCamZ * LEN_UNIT * PX_UNIT *  30) {
                            return true;
                        } else {
                            return false;
                        }
                    }
                }
            }
        }
    }
}

MyLaserChip001::~MyLaserChip001() {

}

