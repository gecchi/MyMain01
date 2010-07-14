#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;


MyStraightLaserChip001::MyStraightLaserChip001(const char* prm_name) :
        StraightLaserChip(prm_name, "11/MyCurveLaserChip001") { //LaserChip�n�͍ő�11�Z�b�g
    _class_name = "MyStraightLaserChip001";
    MyStgUtil::resetMyStraightLaserChip001Status(_pStatus);
    _veloMv = 100000;
}

void MyStraightLaserChip001::initialize() {
    _pMover->setRzRyMvAng(0,0);
    registHitAreaCube(60000);
    setHitAble(true);
    _SX = _SY = _SZ = 100 * 1000;
    _fAlpha = 0.99;
    _fBoundingSphereRadius = 20.0;
}

void MyStraightLaserChip001::onActive() {
    StraightLaserChip::onActive();
    _pMover->setMvVelo(60000);
    _pMover->setMvAcce(300);
    MyStgUtil::resetMyStraightLaserChip001Status(_pStatus);
}

void MyStraightLaserChip001::onHit(GgafActor* prm_pOtherActor) {
    GgafDx9GeometricActor* pOther = (GgafDx9GeometricActor*)prm_pOtherActor;
    //�E�E�E�R�R�Ƀq�b�g���ꂽ�G�t�F�N�g
    //playSe3D1();
    if (MyStgUtil::calcMyStatus(_pStatus, getKind(), pOther->_pStatus, pOther->getKind()) <= 0) {
        //�j�󂳂ꂽ�ꍇ
        //�E�E�E�R�R�ɔj�󂳂ꂽ�G�t�F�N�g
        sayonara();
    }

}


MyStraightLaserChip001::~MyStraightLaserChip001() {
}

