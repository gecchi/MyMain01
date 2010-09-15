
#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;


MyTorpedoChip::MyTorpedoChip(const char* prm_name) :
        HomingLaserChip(prm_name, "AstraeaLaserChip001") {
    _class_name = "MyTorpedoChip";
    MyStgUtil::resetMyTorpedoChipStatus(_pStatus);
}

void MyTorpedoChip::initialize() {
    registHitAreaCube(15000);
    setHitAble(true);
    _SX = _SY = _SZ = 5*1000;
    _fAlpha = 0.9f;
    _fBoundingSphereRadius = 5.0f;
    _paD3DMaterial9[0].Diffuse = D3DXCOLOR(1.0, 0.0, 0.0, 1.0);

}

void MyTorpedoChip::onActive() {
    HomingLaserChip::onActive();
    //ステータスリセット
    MyStgUtil::resetMyTorpedoChipStatus(_pStatus);

    _pMover->setMvVelo(10000);
    _pMover->setMvAcce(400);
    _pMover->relateRzRyFaceAngToMvAng(true);
}

void MyTorpedoChip::processBehaviorHeadChip() {
    if (getActivePartFrame() == 40) {
        _pMover->execTagettingMvAngSequence(
                    GameGlobal::_pMyShip,
                    7000, 0,
                    TURN_ANTICLOSE_TO, false);
    }


    if (_pMover->_mv_ang_ry_target_flg == false && _pMover->_mv_ang_rz_target_flg == false) {
        _pMover->execTagettingMvAngSequence(
                    GameGlobal::_pMyShip,
                    100, 0,
                    TURN_CLOSE_TO, false);
    }
//
//    if (_frame_of_behaving_from_onActive == 35) {
//        _pMover->execTagettingMvAngSequence(
//                    GameGlobal::_pMyShip,
//                    20000, TURN_ANTICLOSE_TO);
//    }

    _pMover->behave();
}

void MyTorpedoChip::onHit(GgafActor* prm_pOtherActor) {
    GgafDx9GeometricActor* pOther = (GgafDx9GeometricActor*)prm_pOtherActor;
    //ヒット時
    //体力計算
    int sta = MyStgUtil::calcEnemyStatus(_pStatus, getKind(), pOther->_pStatus, pOther->getKind());
    if (sta <= 0) {
        //ヒットして消滅時
        sayonara();
    } else {
        //ヒットして生存時
    }
}

MyTorpedoChip::~MyTorpedoChip() {

}

