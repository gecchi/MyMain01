
#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;


EnemyAstraeaLaserChip002::EnemyAstraeaLaserChip002(const char* prm_name) : RefractionLaserChip(prm_name, "12/laser_chip_red") {
    _class_name = "EnemyAstraeaLaserChip002";
    MyStgUtil::resetEnemyAstraeaLaserChip002Status(_pStatus);
    setParam(5, 15, 30);
}

void EnemyAstraeaLaserChip002::initialize() {
    registHitAreaCube(2000);
    setBumpable(true);
    _SX = _SY = _SZ = 80*1000;
    _fAlpha = 0.9f;
    _max_radius = 5.0f;
    _paD3DMaterial9[0].Diffuse = D3DXCOLOR(1.0, 0.0, 0.0, 1.0);

}

void EnemyAstraeaLaserChip002::onActive() {
    RefractionLaserChip::onActive();
    //ステータスリセット
    MyStgUtil::resetEnemyAstraeaLaserChip002Status(_pStatus);

    _pMover->setMoveVelocity(10000);
    _pMover->setMoveVeloAcceleration(300);
    _pMover->relateRzRyFaceAngleToMoveAngle(true);
}

void EnemyAstraeaLaserChip002::processOnRefraction(int prm_num_refraction)  {
    if (prm_num_refraction == 0) {

    } else {
//        angle out_angRz_Target;
//        angle out_angRy_Target;
//        GgafDx9Util::getRzRyAngle(pMYSIP->_X - _X,
//                                  pMYSIP->_Y - _Y,
//                                  pMYSIP->_Z - _Z,
//                                  out_angRz_Target,
//                                  out_angRy_Target);

        _pMover->setMoveAngle(pMYSHIP);
    }


}

void EnemyAstraeaLaserChip002::processOnHit(GgafActor* prm_pOtherActor) {
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

EnemyAstraeaLaserChip002::~EnemyAstraeaLaserChip002() {

}

