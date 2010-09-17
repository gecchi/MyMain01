
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
    _pTarget = NULL;
}

void MyTorpedoChip::initialize() {
    registHitAreaCube(30000);
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

    _pMover->setMvVelo(40000);
    _pMover->setMvAcce(1000);
    _pMover->relateRzRyFaceAngToMvAng(true);
    _pMover->stopTagettingMvAngSequence();
}

void MyTorpedoChip::processBehaviorHeadChip() {
    if (getActivePartFrame() < 120) {
        if (_pTarget) {
            if (_pTarget->isActive())  {
                if (_pMover->isTagettingMvAng()) {

                } else {
                    _pMover->execTagettingMvAngSequence(
                                _pTarget,
                                2000, 0,
                                TURN_CLOSE_TO, false);
                }
            } else {
                //まっすぐ
            }
        } else {
            if (_pMover->isTagettingMvAng()) {

            } else {
                _pMover->execTagettingMvAngSequence(
                            GgafDx9Universe::_X_goneRight, pMYSHIP->_Y, pMYSHIP->_Z,
                            2000, 0,
                            TURN_CLOSE_TO, false);
            }
        }
    }

    if ( getActivePartFrame() >= 120)  {
        if (_pTarget) {
            if (_pTarget->isActive())  {
                if (_pMover->isTagettingMvAng()) {

                } else {
                    _pMover->execTagettingMvAngSequence(
                                _pTarget,
                                90, 0,
                                TURN_CLOSE_TO, false);
                }
            }
        }
    }


    _pMover->behave();
}

void MyTorpedoChip::onHit(GgafActor* prm_pOtherActor) {
    GgafDx9GeometricActor* pOther = (GgafDx9GeometricActor*)prm_pOtherActor;
    //ヒット時
    //体力計算
    int sta = MyStgUtil::calcMyStatus(_pStatus, getKind(), pOther->_pStatus, pOther->getKind());
    if (sta <= 0) {
        //ヒットして消滅時
        sayonara();
    } else {
        //ヒットして生存時
    }
}

MyTorpedoChip::~MyTorpedoChip() {

}

