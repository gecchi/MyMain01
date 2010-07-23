#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;


EnemyAstraeaLaserChip002::EnemyAstraeaLaserChip002(const char* prm_name) :
        RefractionLaserChip(prm_name, "11/AstraeaLaserChip001") { //LaserChip系は最大12セット
    _class_name = "EnemyAstraeaLaserChip002";
    MyStgUtil::resetEnemyAstraeaLaserChip002Status(_pStatus);
    setRefractionParam(20, 2, 1);
}

void EnemyAstraeaLaserChip002::initialize() {
    registHitAreaCube(2000);
    setHitAble(true);
    _SX = _SY = _SZ = 5*1000;
    _fAlpha = 0.9f;
    _fBoundingSphereRadius = 5.0f;
    _paD3DMaterial9[0].Diffuse = D3DXCOLOR(1.0, 0.0, 0.0, 1.0);

}

void EnemyAstraeaLaserChip002::onActive() {
    RefractionLaserChip::onActive();
    //ステータスリセット
    MyStgUtil::resetEnemyAstraeaLaserChip002Status(_pStatus);

    _pMover->setMvVelo(60000);
    //_pMover->setMvAcce(300);
    //_pMover->forceRyMvAngVeloRange(-90000, 90000);
    _pMover->relateRzRyFaceAngToMvAng(true);
}

void EnemyAstraeaLaserChip002::onRefraction(int prm_num_refraction)  {
    if (prm_num_refraction == 0) {

    } else {
        angle out_angRz_Target;
        angle out_angRy_Target;
        angle out_d_angRz;
        angle out_d_angRy;
        GgafDx9Util::getRzRyAng(pMYSHIP->_X - _X,
                                pMYSHIP->_Y - _Y,
                                pMYSHIP->_Z - _Z,
                                out_angRz_Target,
                                out_angRy_Target);
        out_d_angRz = _pMover->getRzMvAngDistance(out_angRz_Target, TURN_CLOSE_TO);
        out_d_angRy = _pMover->getRyMvAngDistance(out_angRy_Target, TURN_CLOSE_TO);
        _pMover->addRzMvAng(sgn(out_d_angRz)*45000);
        _pMover->addRyMvAng(sgn(out_d_angRy)*90000);
//        _pMover->execTagettingMvAngSequence(
//                        GameGlobal::_pMyShip,
//                        90000, 0,
//                        TURN_CLOSE_TO, false);

//        _pMover->setMvAng(pMYSHIP);
    }


}

void EnemyAstraeaLaserChip002::onHit(GgafActor* prm_pOtherActor) {
//    GgafDx9GeometricActor* pOther = (GgafDx9GeometricActor*)prm_pOtherActor;
//    //ヒット時
//
//    //体力計算
//    if (MyStgUtil::calcEnemyStatus(_pStatus, getKind(), pOther->_pStatus, pOther->getKind()) <= 0) {
//        //ヒットして消滅時
//        sayonara();
//    } else {
//        //ヒットして生存時
//    }
}

EnemyAstraeaLaserChip002::~EnemyAstraeaLaserChip002() {

}

