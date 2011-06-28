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

    _pTailEffectStore = NEW LaserChipStore("DP_TailEffect");
    _pTailEffectStore->config(_length_TailEffect, 0, NULL);
    for (int i = 0; i < _length_TailEffect; i++) {
        stringstream name;
        name <<  "MYOPTION"<<(_pMyOptionTorpedoController->_pMyOption->_no)<<"'s Torpedo's TailEffect["<<i<<"]";
        MyTorpedoTail* pChip = NEW MyTorpedoTail(name.str().c_str(), this);

        pChip->inactivateImmediately();
        _pTailEffectStore->addSubLast(pChip);
    }
    addSubGroup(_pTailEffectStore);
    changeEffectTechnique("DestBlendOne"); //加算合成するTechnique指定
    setZEnable(true);        //Zバッファは考慮有り
    setZWriteEnable(false);  //Zバッファは書き込み無し
    _pTarget = NULL;
    useProgress(10);
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
    _pKurokoA->setFaceAngVelo(AXIS_X, 3*1000);
    _pKurokoA->setFaceAngVelo(AXIS_Y, 5*1000);
    _pKurokoA->setFaceAngVelo(AXIS_Z, 7*1000);
    _pKurokoA->setMvVelo(20000);
    _pKurokoA->setMvAcce(-1000);
    _pKurokoA->setRzMvAngVelo(0);
    _pKurokoA->setRyMvAngVelo(0);
    _pKurokoA->setRzMvAngAcce(0);
    _pKurokoA->setRyMvAngAcce(0);
    _pKurokoA->forceMvVeloRange(200, 80000);
    _pKurokoA->forceRzMvAngVeloRange(-40000, 40000);
    _pKurokoA->forceRyMvAngVeloRange(-40000, 40000);
    _pKurokoA->stopTurnMvAngSequence();
    _begin_X = _X;
    _begin_Y = _Y;
    _begin_Z = _Z;
    setHitAble(true);
    _pProg->set(MyTorpedo_IN_FIRE);
    _move_section = 0;
}

void MyTorpedo::processBehavior() {
    if (_pProg->get() == MyTorpedo_RELEASE) {
        if (_pTailEffectStore->_num_chip_active == 0) {
            //軌跡エフェクトが全て非活動になった場合
            inactivate(); //自身を最後にinactivate()
        } else {
            addAlpha(-0.05);
        }
    }

    if (_pProg->get() == MyTorpedo_IN_FIRE) {
        //尾っぽエフェクト追加処理
        if (_pTailEffectStore->_num_chip_active < _length_TailEffect) {
            MyTorpedoTail* pTailEffect = (MyTorpedoTail*)_pTailEffectStore->dispatch();
            if (pTailEffect) {
                pTailEffect->locate(_begin_X,_begin_Y,_begin_Z);
            }
        }
        //魚雷のムーブ
        if (_move_section == 0) {
            if (_pKurokoA->_veloMv == _pKurokoA->_veloBottomMv) {
                //減速終了
                _pKurokoA->setMvAcce(500);
                if (_pTarget) {
                    _pKurokoA->execTurnMvAngSequence(
                                _pTarget,
                                2000, 200,
                                TURN_CLOSE_TO, false);
                } else {
                    _pKurokoA->execTurnMvAngSequence(
                                GgafDx9Universe::_X_goneRight, P_MYSHIP->_Y, P_MYSHIP->_Z,
                                2000, 200,
                                TURN_CLOSE_TO, false);
                }
                _move_section++;
            }
        }

        //ムーブ１
        if (_move_section == 1) {
            if (_pKurokoA->isTurningMvAng()) {
                //ターゲット完了を待つ
            } else {
                //ターゲット完了
                _move_section++;
            }

        }
        //ムーブ２
        if (_move_section == 2) {
            if (getActivePartFrame() < 120) {
                if (getActivePartFrame() % 10 == 0) {
                    if (_pTarget) {
                        if (_pTarget->isActiveActor())  {
                            _pKurokoA->execTurnMvAngSequence(
                                        _pTarget,
                                        1000, 200,
                                        TURN_CLOSE_TO, false);
                        } else {
                            //まっすぐ
                            _pKurokoA->setRzMvAngVelo(0);
                            _pKurokoA->setRyMvAngVelo(0);
                            _pKurokoA->setRzMvAngAcce(0);
                            _pKurokoA->setRyMvAngAcce(0);
                        }
                    } else {
                            _pKurokoA->execTurnMvAngSequence(
                                        GgafDx9Universe::_X_goneRight, _Y, _Z,
                                        1000, 200,
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
                        if (_pTarget->isActiveActor())  {
                            _pKurokoA->execTurnMvAngSequence(
                                        _pTarget,
                                        300, 0,
                                        TURN_CLOSE_TO, false);
                        } else {
                            //まっすぐ
                            _pKurokoA->setRzMvAngVelo(0);
                            _pKurokoA->setRyMvAngVelo(0);
                            _pKurokoA->setRzMvAngAcce(0);
                            _pKurokoA->setRyMvAngAcce(0);
                        }
                    } else {
                            _pKurokoA->execTurnMvAngSequence(
                                        GgafDx9Universe::_X_goneRight, _Y, _Z,
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
            _pKurokoA->setRzMvAngVelo(0);
            _pKurokoA->setRyMvAngVelo(0);
            _pKurokoA->setRzMvAngAcce(0);
            _pKurokoA->setRyMvAngAcce(0);
        }

        _pKurokoA->behave();
        _pScaler->behave();
    }
}

void MyTorpedo::processJudgement() {
    if (isOutOfUniverse() && _pProg->get() == MyTorpedo_IN_FIRE) {
        setHitAble(false);
        _pProg->change(MyTorpedo_RELEASE);
        GgafMainActor* pTailEffect = _pTailEffectStore->getSubFirst();
        for (int i = 0; i < _length_TailEffect; i++) {
            pTailEffect->inactivateDelay(i+1); //軌跡エフェクトが順々に消えるように予約
            pTailEffect = pTailEffect->getNext();
        }
        _pKurokoA->setMvVelo(0);
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
    _pProg->change(MyTorpedo_RELEASE);
    GgafMainActor* pTailEffect = _pTailEffectStore->getSubFirst();
    for (int i = 0; i < _length_TailEffect; i++) {
        pTailEffect->inactivateDelay(i+1); //軌跡エフェクトが順々に消えるように予約
        pTailEffect = pTailEffect->getNext();
    }
    _pKurokoA->setMvVelo(0);
    //自身のinactive()はprocessBehavior()で行われ
    //魚雷の移動エフェクトが全てinactive()になった際に自身もinactive()する

    //爆風発生
    MyTorpedoBlast* pBlast = (MyTorpedoBlast*)_pMyOptionTorpedoController->_pStore_TorpedoBlast->dispatch();
    if (pBlast) {
        pBlast->locateAs(this);
        pBlast->reset();
    }

}

MyTorpedo::~MyTorpedo() {
}
