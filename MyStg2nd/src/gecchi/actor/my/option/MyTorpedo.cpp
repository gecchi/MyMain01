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
    _length_TailEffect = 4;

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
    chengeEffectTechnique("DestBlendOne"); //加算合成するTechnique指定
    setZEnable(true);        //Zバッファは考慮有り
    setZWriteEnable(false);  //Zバッファは書き込み無し
    _pTarget = NULL;
}

void MyTorpedo::initialize() {
    _pCollisionChecker->makeCollision(1);
    _pCollisionChecker->setColliAAB_Cube(0, 70000);
}

void MyTorpedo::onActive() {
    MyStgUtil::resetMyTorpedoStatus(_pStatus);
    setAlpha(0.3);
    _SX = _SY = _SZ = 100;
    _pScaler->setScale(100);
    _pScaler->intoTargetScaleLinerStep(7000, 500);
    _pMover->setFaceAngVelo(AXIS_X, 3*1000);
    _pMover->setFaceAngVelo(AXIS_Y, 5*1000);
    _pMover->setFaceAngVelo(AXIS_Z, 7*1000);
    _pMover->setMvVelo(6000);
    _pMover->setMvAcce(-200);
    _pMover->setRzMvAngVelo(0);
    _pMover->setRyMvAngVelo(0);
    _pMover->setRzMvAngAcce(0);
    _pMover->setRyMvAngAcce(0);
    _pMover->forceMvVeloRange(200, 80000);
    _pMover->forceRzMvAngVeloRange(-40000, 40000);
    _pMover->forceRyMvAngVeloRange(-40000, 40000);
    _pMover->stopTagettingMvAngSequence();
    _begin_X = _X;
    _begin_Y = _Y;
    _begin_Z = _Z;
    setHitAble(true);
    setProgress(MyTorpedo_IN_FIRE);
    _move_section = 0;
}

void MyTorpedo::processBehavior() {
    if (getProgress() == MyTorpedo_RELEASE) {
        if (_pTailEffectDispatcher->_num_chip_active == 0) {
            //軌跡エフェクトが全て非活動になった場合
            inactivate(); //自身を最後にinactivate()
        } else {
            addAlpha(-0.05);
        }
    }

    if (getProgress() == MyTorpedo_IN_FIRE) {
        //尾っぽエフェクト追加処理
        if (_pTailEffectDispatcher->_num_chip_active < _length_TailEffect) {
            MyTorpedoTail* pTailEffect = (MyTorpedoTail*)_pTailEffectDispatcher->employ();
            if (pTailEffect) {
                pTailEffect->setGeometry(_begin_X,_begin_Y,_begin_Z);
                pTailEffect->activate();
            }
        }
        //魚雷のムーブ
        if (_move_section == 0) {
            if (_pMover->_veloMv == _pMover->_veloBottomMv) {
                //減速終了
                _pMover->setMvAcce(500);
                if (_pTarget) {
                    _pMover->execTagettingMvAngSequence(
                                _pTarget,
                                2000, 100,
                                TURN_ANTICLOSE_TO, false);
                } else {
                    _pMover->execTagettingMvAngSequence(
                                GgafDx9Universe::_X_goneRight, pMYSHIP->_Y, pMYSHIP->_Z,
                                2000, 100,
                                TURN_ANTICLOSE_TO, false);
                }
                _move_section++;
            }
        }

        //ムーブ１
        if (_move_section == 1) {
            if (_pMover->isTagettingMvAng()) {
                //そのまま
            } else {
                _move_section++;
            }

        }
        //ムーブ２
        if (_move_section == 2) {
            if (getActivePartFrame() < 120) {
                if (getActivePartFrame() % 10 == 0) {
                    if (_pTarget) {
                        if (_pTarget->isActive())  {
                            _pMover->execTagettingMvAngSequence(
                                        _pTarget,
                                        2000, 500,
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
                                        2000, 500,
                                        TURN_CLOSE_TO, false);
                    }
                } else {
                   //
                }
            } else {
                _move_section++;
            }
        }
        //ムーブ３
        if (_move_section == 3) {
            if (getActivePartFrame() < 300) {
                if (getActivePartFrame() % 20 == 0) {
                    if (_pTarget) {
                        if (_pTarget->isActive())  {
                            _pMover->execTagettingMvAngSequence(
                                        _pTarget,
                                        300, 0,
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
                                        300, 0,
                                        TURN_CLOSE_TO, false);
                    }
                } else {
                   //
                }
            } else {
                _move_section++;
            }
        }
        //ムーブ４
        if (_move_section == 4) {
            _pMover->setRzMvAngVelo(0);
            _pMover->setRyMvAngVelo(0);
            _pMover->setRzMvAngAcce(0);
            _pMover->setRyMvAngAcce(0);
        }

        _pMover->behave();
        _pScaler->behave();
    }
}

void MyTorpedo::processJudgement() {
    if (isOutOfUniverse() && getProgress() == MyTorpedo_IN_FIRE) {
        setHitAble(false);
        setProgress(MyTorpedo_RELEASE);
        GgafMainActor* pTailEffect = _pTailEffectDispatcher->getSubFirst();
        for (int i = 0; i < _length_TailEffect; i++) {
            pTailEffect->inactivateDelay(i+1); //軌跡エフェクトが順々に消えるように予約
            pTailEffect = pTailEffect->getNext();
        }
        _pMover->setMvVelo(0);
        //自身のinactive()はprocessBehavior()で行われ
        //魚雷の移動エフェクトが全てinactive()になった際に自身もinactive()する
    }

}

void MyTorpedo::onInactive() {
}


void MyTorpedo::onHit(GgafActor* prm_pOtherActor) {
    GgafDx9GeometricActor* pOther = (GgafDx9GeometricActor*)prm_pOtherActor;
    //ヒット時通貫はしません
    int sta = MyStgUtil::calcMyStatus(_pStatus, getKind(), pOther->_pStatus, pOther->getKind());
    setHitAble(false);
    setProgress(MyTorpedo_RELEASE);
    GgafMainActor* pTailEffect = _pTailEffectDispatcher->getSubFirst();
    for (int i = 0; i < _length_TailEffect; i++) {
        pTailEffect->inactivateDelay(i+1); //軌跡エフェクトが順々に消えるように予約
        pTailEffect = pTailEffect->getNext();
    }
    _pMover->setMvVelo(0);
    //自身のinactive()はprocessBehavior()で行われ
    //魚雷の移動エフェクトが全てinactive()になった際に自身もinactive()する

    //爆風発生
    MyTorpedoBlast* pBlast = (MyTorpedoBlast*)_pMyOptionTorpedoController->_pDispatcher_TorpedoBlast->employ();
    if (pBlast) {
        pBlast->setGeometry(this);
        pBlast->activate();
    }

}

MyTorpedo::~MyTorpedo() {
}
