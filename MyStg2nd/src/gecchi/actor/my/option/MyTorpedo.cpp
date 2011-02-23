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
    _pKuroko->setFaceAngVelo(AXIS_X, 3*1000);
    _pKuroko->setFaceAngVelo(AXIS_Y, 5*1000);
    _pKuroko->setFaceAngVelo(AXIS_Z, 7*1000);
    _pKuroko->setMvVelo(20000);
    _pKuroko->setMvAcce(-1000);
    _pKuroko->setRzMvAngVelo(0);
    _pKuroko->setRyMvAngVelo(0);
    _pKuroko->setRzMvAngAcce(0);
    _pKuroko->setRyMvAngAcce(0);
    _pKuroko->forceMvVeloRange(200, 80000);
    _pKuroko->forceRzMvAngVeloRange(-40000, 40000);
    _pKuroko->forceRyMvAngVeloRange(-40000, 40000);
    _pKuroko->stopTagettingMvAngSequence();
    _begin_X = _X;
    _begin_Y = _Y;
    _begin_Z = _Z;
    setHitAble(true);
    _pProgress->change(MyTorpedo_IN_FIRE);
    _move_section = 0;
}

void MyTorpedo::processBehavior() {
    if (_pProgress->get() == MyTorpedo_RELEASE) {
        if (_pTailEffectDispatcher->_num_chip_active == 0) {
            //軌跡エフェクトが全て非活動になった場合
            inactivate(); //自身を最後にinactivate()
        } else {
            addAlpha(-0.05);
        }
    }

    if (_pProgress->get() == MyTorpedo_IN_FIRE) {
        //尾っぽエフェクト追加処理
        if (_pTailEffectDispatcher->_num_chip_active < _length_TailEffect) {
            MyTorpedoTail* pTailEffect = (MyTorpedoTail*)_pTailEffectDispatcher->employ();
            if (pTailEffect) {
                pTailEffect->setCoordinate(_begin_X,_begin_Y,_begin_Z);
                pTailEffect->activate();
            }
        }
        //魚雷のムーブ
        if (_move_section == 0) {
            if (_pKuroko->_veloMv == _pKuroko->_veloBottomMv) {
                //減速終了
                _pKuroko->setMvAcce(500);
                if (_pTarget) {
                    _pKuroko->execTagettingMvAngSequence(
                                _pTarget,
                                2000, 200,
                                TURN_CLOSE_TO, false);
                } else {
                    _pKuroko->execTagettingMvAngSequence(
                                GgafDx9Universe::_X_goneRight, P_MYSHIP->_Y, P_MYSHIP->_Z,
                                2000, 200,
                                TURN_CLOSE_TO, false);
                }
                _move_section++;
            }
        }

        //ムーブ１
        if (_move_section == 1) {
            if (_pKuroko->isTagettingMvAng()) {
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
                            _pKuroko->execTagettingMvAngSequence(
                                        _pTarget,
                                        1000, 200,
                                        TURN_CLOSE_TO, false);
                        } else {
                            //まっすぐ
                            _pKuroko->setRzMvAngVelo(0);
                            _pKuroko->setRyMvAngVelo(0);
                            _pKuroko->setRzMvAngAcce(0);
                            _pKuroko->setRyMvAngAcce(0);
                        }
                    } else {
                            _pKuroko->execTagettingMvAngSequence(
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
                            _pKuroko->execTagettingMvAngSequence(
                                        _pTarget,
                                        300, 0,
                                        TURN_CLOSE_TO, false);
                        } else {
                            //まっすぐ
                            _pKuroko->setRzMvAngVelo(0);
                            _pKuroko->setRyMvAngVelo(0);
                            _pKuroko->setRzMvAngAcce(0);
                            _pKuroko->setRyMvAngAcce(0);
                        }
                    } else {
                            _pKuroko->execTagettingMvAngSequence(
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
            _pKuroko->setRzMvAngVelo(0);
            _pKuroko->setRyMvAngVelo(0);
            _pKuroko->setRzMvAngAcce(0);
            _pKuroko->setRyMvAngAcce(0);
        }

        _pKuroko->behave();
        _pScaler->behave();
    }
}

void MyTorpedo::processJudgement() {
    if (isOutOfUniverse() && _pProgress->get() == MyTorpedo_IN_FIRE) {
        setHitAble(false);
        _pProgress->change(MyTorpedo_RELEASE);
        GgafMainActor* pTailEffect = _pTailEffectDispatcher->getSubFirst();
        for (int i = 0; i < _length_TailEffect; i++) {
            pTailEffect->inactivateDelay(i+1); //軌跡エフェクトが順々に消えるように予約
            pTailEffect = pTailEffect->getNext();
        }
        _pKuroko->setMvVelo(0);
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
    _pProgress->change(MyTorpedo_RELEASE);
    GgafMainActor* pTailEffect = _pTailEffectDispatcher->getSubFirst();
    for (int i = 0; i < _length_TailEffect; i++) {
        pTailEffect->inactivateDelay(i+1); //軌跡エフェクトが順々に消えるように予約
        pTailEffect = pTailEffect->getNext();
    }
    _pKuroko->setMvVelo(0);
    //自身のinactive()はprocessBehavior()で行われ
    //魚雷の移動エフェクトが全てinactive()になった際に自身もinactive()する

    //爆風発生
    MyTorpedoBlast* pBlast = (MyTorpedoBlast*)_pMyOptionTorpedoController->_pDispatcher_TorpedoBlast->employ();
    if (pBlast) {
        pBlast->setCoordinateBy(this);
        pBlast->activate();
    }

}

MyTorpedo::~MyTorpedo() {
}
