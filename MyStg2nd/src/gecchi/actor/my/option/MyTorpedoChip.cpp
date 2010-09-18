
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
    registHitAreaCube(80000);
    setHitAble(true);
    _SX = _SY = _SZ = 6*1000;
    _fAlpha = 0.9f;
    _fBoundingSphereRadius = 5.0f;
    _paD3DMaterial9[0].Diffuse = D3DXCOLOR(1.0, 0.0, 0.0, 1.0);

}

void MyTorpedoChip::onActive() {
    HomingLaserChip::onActive();
    //ステータスリセット
    MyStgUtil::resetMyTorpedoChipStatus(_pStatus);

    _pMover->setMvVelo(100000);
    _pMover->setMvAcce(1000);
    _pMover->setRzMvAngVelo(0);
    _pMover->setRyMvAngVelo(0);
    _pMover->setRzMvAngAcce(0);
    _pMover->setRyMvAngAcce(0);
    _pMover->forceRzMvAngVeloRange(-10000, 10000);
    _pMover->forceRyMvAngVeloRange(-10000, 10000);
    _pMover->stopTagettingMvAngSequence();
}

void MyTorpedoChip::processBehaviorHeadChip() {
    if (getActivePartFrame() <= 120 && getActivePartFrame() % 5 == 0) {
        if (_pTarget) {
            if (_pTarget->isActive())  {
                _pMover->execTagettingMvAngSequence(
                            _pTarget,
                            3000, 100,
                            TURN_CLOSE_TO, false);
            } else {
                //まっすぐ
                _pMover->setRzMvAngVelo(0);
                _pMover->setRyMvAngVelo(0);
                _pMover->setRzMvAngAcce(0);
                _pMover->setRyMvAngAcce(0);
            }
        } else {
                _pMover->execTagettingMvAngSequence(
                            GgafDx9Universe::_X_goneRight, pMYSHIP->_Y, pMYSHIP->_Z,
                            3000, 100,
                            TURN_CLOSE_TO, false);
        }
    }

    if ( getActivePartFrame() == 300) {
        _pMover->setRzMvAngVelo(0);
        _pMover->setRyMvAngVelo(0);
        _pMover->setRzMvAngAcce(0);
        _pMover->setRyMvAngAcce(0);
    } else if ( getActivePartFrame() > 120 && getActivePartFrame() % 5 == 0)  {
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
        } else {
            _pMover->setRzMvAngVelo(0);
            _pMover->setRyMvAngVelo(0);
            _pMover->setRzMvAngAcce(0);
            _pMover->setRyMvAngAcce(0);
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

