
#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;


EnemyAstraeaLaserChip001::EnemyAstraeaLaserChip001(const char* prm_name) : HomingLaserChip(prm_name, "12/laser_chip_red") {
    _class_name = "EnemyAstraeaLaserChip001";
    MyStgUtil::resetEnemyAstraeaLaserChip001Status(_pStatus);
}

void EnemyAstraeaLaserChip001::initialize() {
    registHitAreaCube(2000);
    setHitAble(true);
    _SX = _SY = _SZ = 100*1000;
    _fAlpha = 0.9f;
    _max_radius = 5.0f;
    _paD3DMaterial9[0].Diffuse = D3DXCOLOR(1.0, 0.0, 0.0, 1.0);

}

void EnemyAstraeaLaserChip001::onActive() {
    HomingLaserChip::onActive();
    //ステータスリセット
    MyStgUtil::resetEnemyAstraeaLaserChip001Status(_pStatus);

    _pMover->setMvVelo(5000);
    _pMover->setMvAcce(300);
    _pMover->relateRzRyFaceAngToMvAng(true);
}

void EnemyAstraeaLaserChip001::processBehaviorHeadChip() {
    if (_dwActiveFrame == 40) {
        _pMover->execTagettingMvAngSequence(
                    GameGlobal::_pMyShip,
                    8000, 0,
                    TURN_ANTICLOSE_TO);
    }


    if (_pMover->_mv_ang_ry_target_flg == false && _pMover->_mv_ang_rz_target_flg == false) {
        _pMover->execTagettingMvAngSequence(
                    GameGlobal::_pMyShip,
                    100, 0,
                    TURN_CLOSE_TO);
    }
//
//    if (_dwActiveFrame == 35) {
//        _pMover->execTagettingMvAngSequence(
//                    GameGlobal::_pMyShip,
//                    20000, TURN_ANTICLOSE_TO);
//    }

    _pMover->behave();
}

void EnemyAstraeaLaserChip001::onHit(GgafActor* prm_pOtherActor) {
//    GgafDx9GeometricActor* pOther = (GgafDx9GeometricActor*)prm_pOtherActor;
//    //ヒット時
//
//    //体力計算
//    if (MyStgUtil::calcEnemyStamina(_pStatus, getKind(), pOther->_pStatus, pOther->getKind()) <= 0) {
//        //ヒットして消滅時
//        inactivate();
//    } else {
//        //ヒットして生存時
//    }
}

EnemyAstraeaLaserChip001::~EnemyAstraeaLaserChip001() {

}

