#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;


EnemyAstraeaLaserChip002::EnemyAstraeaLaserChip002(const char* prm_name) :
        RefractionLaserChip(prm_name, "AstraeaLaserChip001") {
    _class_name = "EnemyAstraeaLaserChip002";
    MyStgUtil::resetEnemyAstraeaLaserChip002Status(_pStatus);

    //屈折レーザー設定
    _pDispatcherCon_RefractionEffect = (DispatcherConnection*)(pGOD->_pDispatcherManager->getConnection("DpCon_EffRefraction001"));
    config(50, 10, 5, _pDispatcherCon_RefractionEffect->refer());
}

void EnemyAstraeaLaserChip002::initialize() {
    registHitAreaCube(10000);
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

void EnemyAstraeaLaserChip002::onRefractionBegin(int prm_num_refraction)  {

}

void EnemyAstraeaLaserChip002::onRefractionFinish(int prm_num_refraction)  {
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
        _pMover->addRzMvAng(sgn(out_d_angRz)*10000);
        _pMover->addRyMvAng(sgn(out_d_angRy)*10000);
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
    if (_pDispatcherCon_RefractionEffect) {
        _pDispatcherCon_RefractionEffect->close();
    }

}

