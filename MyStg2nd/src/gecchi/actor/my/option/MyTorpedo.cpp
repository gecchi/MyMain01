#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

MyTorpedo::MyTorpedo(const char* prm_name,MyOptionTorpedoController* prm_pMyOptionTorpedoController)
               : DefaultMeshSetActor(prm_name, "EffectLaserRefraction001") {
    _class_name = "MyTorpedo";
    MyStgUtil::resetMyTorpedoStatus(_pStatus);
    _pMyOptionTorpedoController = prm_pMyOptionTorpedoController;
    _length_TailEffect = 20;

    _pTailEffectDispatcher = NEW LaserChipDispatcher("DP_TailEffect");
    _pTailEffectDispatcher->config(_length_TailEffect, 0, NULL);
    for (int i = 0; i < _length_TailEffect; i++) {
        stringstream name;
        name <<  "MYOPTION"<<(_pMyOptionTorpedoController->_pMyOption->_no)<<"'s Torpedo's TailEffect["<<i<<"]";
        MyTorpedoTail* pChip = NEW MyTorpedoTail(name.str().c_str(), this);

        pChip->inactivateImmediately();
        _pTailEffectDispatcher->addSubLast(pChip);
    }
    addSubGroup(_pTailEffectDispatcher);

//    _pMyTorpedoTailChip_Head = NULL;
    chengeEffectTechnique("DestBlendOne"); //加算合成するTechnique指定
    setZEnable(true);        //Zバッファは考慮有り
    setZWriteEnable(false);  //Zバッファは書き込み無し
    _pTarget = NULL;
}

void MyTorpedo::initialize() {
//    _pUvFlipper->forcePtnNoRange(0, 63);
    setHitAble(true);
    _pCollisionChecker->makeCollision(1);
    _pCollisionChecker->setColliAAB_Cube(0, 70000);
}

void MyTorpedo::onActive() {
    MyStgUtil::resetMyTorpedoStatus(_pStatus);
    //_pUvFlipper->setPtnNoToTop();
    //_pUvFlipper->setFlipMethod(FLIP_ORDER_LOOP, 1); //パラパラアニメ無し
    setAlpha(0.7);
    _pScaler->setScale(7*1000);
    _pMover->setFaceAngVelo(AXIS_X, 3*1000);
    _pMover->setFaceAngVelo(AXIS_Y, 5*1000);
    _pMover->setFaceAngVelo(AXIS_Z, 7*1000);
    _pMover->setMvVelo(5000);
    _pMover->setMvAcce(1000);
    _pMover->setRzMvAngVelo(0);
    _pMover->setRyMvAngVelo(0);
    _pMover->setRzMvAngAcce(0);
    _pMover->setRyMvAngAcce(0);
    _pMover->forceMvVeloRange(1000, 80000);
    _pMover->forceRzMvAngVeloRange(-40000, 40000);
    _pMover->forceRyMvAngVeloRange(-40000, 40000);
    _pMover->stopTagettingMvAngSequence();
    _begin_X = _X;
    _begin_Y = _Y;
    _begin_Z = _Z;
    setProgress(MyTorpedo_IN_FIRE);
}

void MyTorpedo::processBehavior() {
    if (getProgress() == MyTorpedo_RELEASE) {
        if (_pTailEffectDispatcher->_num_chip_active == 0) {
            inactivate();
        }
    } else if (getProgress() == MyTorpedo_IN_FIRE) {
        if (_pTailEffectDispatcher->_num_chip_active < _length_TailEffect) {
            MyTorpedoTail* pTailEffect = (MyTorpedoTail*)_pTailEffectDispatcher->employ();
            if (pTailEffect) {
                pTailEffect->setGeometry(_begin_X,_begin_Y,_begin_Z);
                pTailEffect->activate();
            }
        }
        if (getActivePartFrame() <= 120 && getActivePartFrame() % 5 == 0) {
            if (_pTarget) {
                if (_pTarget->isActive())  {
                    _pMover->execTagettingMvAngSequence(
                                _pTarget,
                                3000, 300,
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
                                3000, 300,
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
                                    200, 0,
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
        _pScaler->behave();
    }






}

void MyTorpedo::processJudgement() {
    if (isOutOfGameSpace()) {
        setProgress(MyTorpedo_RELEASE);
        GgafMainActor* pTailEffect = _pTailEffectDispatcher->getSubFirst();
        for (int i = 0; i < _length_TailEffect; i++) {
            pTailEffect->inactivateDelay(i+1);
            pTailEffect = pTailEffect->getNext();
        }
        _pMover->setMvVelo(0);
    }

}

void MyTorpedo::onInactive() {
//    GgafMainActor* pTailEffect = _pTailEffectDispatcher->getSubFirst();
//    for (int i = 0; i < _length_TailEffect; i++) {
//        pTailEffect->inactivateImmediately();
//        pTailEffect = pTailEffect->getNext();
//    }

//    if (_pMyTorpedoTailChip_Head) {
//        _pMyTorpedoTailChip_Head->inactivate(); //これにてズルズルっと消える
//    }
}


void MyTorpedo::onHit(GgafActor* prm_pOtherActor) {
    GgafDx9GeometricActor* pOther = (GgafDx9GeometricActor*)prm_pOtherActor;
    //ヒット時
    //体力計算
    int sta = MyStgUtil::calcMyStatus(_pStatus, getKind(), pOther->_pStatus, pOther->getKind());

    setProgress(MyTorpedo_RELEASE);
    GgafMainActor* pTailEffect = _pTailEffectDispatcher->getSubFirst();
    for (int i = 0; i < _length_TailEffect; i++) {
        pTailEffect->inactivateDelay(i+1);
        pTailEffect = pTailEffect->getNext();
    }
    _pMover->setMvVelo(0);

//    if (_pMyTorpedoTailChip_Head) {
//        _pMyTorpedoTailChip_Head->inactivate(); //これにてズルズルっと消える
//    }
////
//    if (sta <= 0) {
//        //ヒットして消滅時
//        inactivate();
//
//    } else {
//        //ヒットして生存時
//    }
}

MyTorpedo::~MyTorpedo() {
}
