#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;


EnemyStraightLaserChip001::EnemyStraightLaserChip001(const char* prm_name) :
        StraightLaserChip(prm_name, "EnemyCurveLaserChip001") {
    _class_name = "EnemyStraightLaserChip001";
    MyStgUtil::resetEnemyStraightLaserChip001Status(_pStatus);
    _veloMv = 100000;
}

void EnemyStraightLaserChip001::initialize() {
    _pKuroko->setRzRyMvAng(0,0);
    registHitAreaCube(100000);
    setHitAble(true);
    _SX = _SY = _SZ = 5 * 1000;
    _fAlpha = 0.99;
    _fBoundingSphereRadius = 20.0;
}

void EnemyStraightLaserChip001::onActive() {
    StraightLaserChip::onActive();
    _pKuroko->setMvVelo(100000);
    _pKuroko->setMvAcce(300);
    MyStgUtil::resetEnemyStraightLaserChip001Status(_pStatus);
}

void EnemyStraightLaserChip001::onHit(GgafActor* prm_pOtherActor) {
    GgafDx9GeometricActor* pOther = (GgafDx9GeometricActor*)prm_pOtherActor;
    //・・・ココにヒットされたエフェクト
    //playSe3D1();
    if (MyStgUtil::calcEnemyStatus(_pStatus, getKind(), pOther->_pStatus, pOther->getKind()) <= 0) {
        //破壊された場合
        //・・・ココに破壊されたエフェクト
        sayonara();
    }

}


EnemyStraightLaserChip001::~EnemyStraightLaserChip001() {
}

