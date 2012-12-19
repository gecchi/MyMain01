#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

MyTorpedo::MyTorpedo(const char* prm_name, MyTorpedoController* prm_pOptionTorpedoController)
               : DefaultMeshSetActor(prm_name, "EffectLaserRefraction001", STATUS(MyTorpedo)) {
    _class_name = "MyTorpedo";
    pOptionTorpedoCtrler_ = prm_pOptionTorpedoController;
    length_TailEffect_ = 4;
    begin_X_ = _X;
    begin_Y_ = _Y;
    begin_Z_ = _Z;

    pTailEffectDepository_ = NEW LaserChipDepository("DP_TailEffect");
    pTailEffectDepository_->config(length_TailEffect_, 0, nullptr);
    for (int i = 0; i < length_TailEffect_; i++) {
        std::string name = std::string(pOptionTorpedoCtrler_->getName())+"'s Tail("+ITOS(i)+")";
        MyTorpedoTail* pChip = NEW MyTorpedoTail(name.c_str(), this);

        pChip->inactivateImmed();
        pTailEffectDepository_->addSubLast(pChip);
    }
    move_section_ = 0;
    addSubGroup(pTailEffectDepository_);
    effectBlendOne(); //加算合成するTechnique指定
    setZEnable(true);        //Zバッファは考慮有り
    setZWriteEnable(false);  //Zバッファは書き込み無し
    pTarget_ = nullptr;
    useProgress(10);
}

void MyTorpedo::initialize() {
    _pColliChecker->makeCollision(1);
    _pColliChecker->setColliAAB_Cube(0, 70000);
}

void MyTorpedo::onReset() {
    pTarget_ = nullptr;
}

void MyTorpedo::onActive() {
    GgafDxKurokoA* pKurokoA = _pKurokoA;
    _pStatus->reset();
    setAlpha(0.3);
    _SX = _SY = _SZ = 100;
    _pScaler->setScale(100);
    _pScaler->intoTargetScaleLinerStep(7000, 500);
    pKurokoA->setFaceAngVelo(AXIS_X, D_ANG(3));
    pKurokoA->setFaceAngVelo(AXIS_Y, D_ANG(5));
    pKurokoA->setFaceAngVelo(AXIS_Z, D_ANG(7));
    pKurokoA->setMvVelo(20000);
    pKurokoA->setMvAcce(-500); //最初減速
    pKurokoA->setRzMvAngVelo(0);
    pKurokoA->setRyMvAngVelo(0);
    pKurokoA->setRzMvAngAcce(0);
    pKurokoA->setRyMvAngAcce(0);
    pKurokoA->forceMvVeloRange(4000, 80000);
    pKurokoA->forceRzMvAngVeloRange(-40000, 40000);
    pKurokoA->forceRyMvAngVeloRange(-40000, 40000);
    pKurokoA->stopTurnMvAngSequence();
    begin_X_ = _X;
    begin_Y_ = _Y;
    begin_Z_ = _Z;
    setHitAble(true);
    _pProg->set(MyTorpedo_IN_FIRE);
    move_section_ = 0;
}

void MyTorpedo::processBehavior() {
    GgafDxKurokoA* pKurokoA = _pKurokoA;
    if (_pProg->get() == MyTorpedo_RELEASE) {
        if (pTailEffectDepository_->_num_chip_active == 0) {
            //軌跡エフェクトが全て非活動になった場合
            inactivate(); //自身を最後にinactivate()
        } else {
            addAlpha(-0.05);
        }
    }

    if (_pProg->get() == MyTorpedo_IN_FIRE) {
        //尾っぽエフェクト追加処理
        if (pTailEffectDepository_->_num_chip_active < length_TailEffect_) {
            MyTorpedoTail* pTailEffect = (MyTorpedoTail*)pTailEffectDepository_->dispatch();
            if (pTailEffect) {
                pTailEffect->locate(begin_X_,begin_Y_,begin_Z_);
            }
        }
        //魚雷のムーブ
        if (move_section_ == 0) {
            if (pKurokoA->_veloMv == pKurokoA->_veloBottomMv) { //減速終了
                pKurokoA->setMvAcce(500);
                if (pTarget_) {
                    pKurokoA->execTurnRzRyMvAngSequenceTwd(
                                pTarget_,
                                2000, 200,
                                TURN_ANTICLOSE_TO, false);
                } else {
                    pKurokoA->execTurnRzRyMvAngSequence(
                                pOptionTorpedoCtrler_->pOrg_->_RZ, pOptionTorpedoCtrler_->pOrg_->_RY,
                                1000, 100,
                                TURN_CLOSE_TO, false);

//                    pKurokoA->execTurnRzRyMvAngSequenceTwd(
//                                GgafDxUniverse::_X_goneRight, P_MYSHIP->_Y, P_MYSHIP->_Z,
//                                2000, 200,
//                                TURN_ANTICLOSE_TO, false);
                }
                move_section_++;
            }
        }

        //ムーブ１
        if (move_section_ == 1) {
            if (pKurokoA->isRunnigTurnMvAngSequence()) {
                //TURN_ANTICLOSE_TOターゲット完了を待つ
            } else {
                //TURN_ANTICLOSE_TOターゲット完了
                move_section_++;
            }
        }
        //ムーブ２
        if (move_section_ == 2) {
            if (getActivePartFrame() < 120) {
                if (getActivePartFrame() % 10 == 0) {
                    if (pTarget_) {
                        if (pTarget_->isActiveInTheTree())  {
                            pKurokoA->execTurnRzRyMvAngSequenceTwd(
                                        pTarget_,
                                        1000, 200,
                                        TURN_CLOSE_TO, false);
                        } else {
                            //まっすぐ
                            pKurokoA->setRzMvAngVelo(0);
                            pKurokoA->setRyMvAngVelo(0);
                            pKurokoA->setRzMvAngAcce(0);
                            pKurokoA->setRyMvAngAcce(0);
                        }
                    } else {
                        pKurokoA->execTurnRzRyMvAngSequence(
                                    pOptionTorpedoCtrler_->pOrg_->_RZ, pOptionTorpedoCtrler_->pOrg_->_RY,
                                    1000, 200,
                                    TURN_CLOSE_TO, false);
//                            _pKurokoA->execTurnRzRyMvAngSequenceTwd(
//                                        GgafDxUniverse::_X_goneRight, _Y, _Z,
//                                        1000, 200,
//                                        TURN_CLOSE_TO, false);
                    }
                } else {
                   //
                }
            } else {
                move_section_++;
            }
        }
        //ムーブ３
        if (move_section_ == 3) {
            if (getActivePartFrame() < 300) {
                if (getActivePartFrame() % 20 == 0) {
                    if (pTarget_) {
                        if (pTarget_->isActiveInTheTree())  {
                            pKurokoA->execTurnRzRyMvAngSequenceTwd(
                                        pTarget_,
                                        300, 0,
                                        TURN_CLOSE_TO, false);
                        } else {
                            //まっすぐ
                            pKurokoA->setRzMvAngVelo(0);
                            pKurokoA->setRyMvAngVelo(0);
                            pKurokoA->setRzMvAngAcce(0);
                            pKurokoA->setRyMvAngAcce(0);
                        }
                    } else {
                        pKurokoA->execTurnRzRyMvAngSequence(
                                    pOptionTorpedoCtrler_->pOrg_->_RZ, pOptionTorpedoCtrler_->pOrg_->_RY,
                                    300, 0,
                                    TURN_CLOSE_TO, false);

                    }
                } else {
                   //
                }
            } else {
                move_section_++;
            }
        }
        //ムーブ４
        if (move_section_ == 4) {
            pKurokoA->setRzMvAngVelo(0);
            pKurokoA->setRyMvAngVelo(0);
            pKurokoA->setRzMvAngAcce(0);
            pKurokoA->setRyMvAngAcce(0);
        }

        pKurokoA->behave();
        _pScaler->behave();
    }
}

void MyTorpedo::processJudgement() {
    if (isOutOfUniverse() && _pProg->get() == MyTorpedo_IN_FIRE) {
        setHitAble(false);
        _pProg->change(MyTorpedo_RELEASE);
        GgafMainActor* pTailEffect = pTailEffectDepository_->getSubFirst();
        for (int i = 0; i < length_TailEffect_; i++) {
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
    GgafDxGeometricActor* pOther = (GgafDxGeometricActor*)prm_pOtherActor;
    //ヒット時通貫はしません
    int sta = UTIL::calcMyStamina(this, pOther);
    setHitAble(false);
    _pProg->change(MyTorpedo_RELEASE);
    GgafMainActor* pTailEffect = pTailEffectDepository_->getSubFirst();
    for (int i = 0; i < length_TailEffect_; i++) {
        pTailEffect->inactivateDelay(i+1); //軌跡エフェクトが順々に消えるように予約
        pTailEffect = pTailEffect->getNext();
    }
    _pKurokoA->setMvVelo(0);
    //自身のinactive()はprocessBehavior()で行われ
    //魚雷の移動エフェクトが全てinactive()になった際に自身もinactive()する

    //爆風発生
    MyTorpedoBlast* pBlast = (MyTorpedoBlast*)pOptionTorpedoCtrler_->pDepo_TorpedoBlast_->dispatch();
    if (pBlast) {
        pBlast->locateWith(this);
        pBlast->reset();
    }

}

MyTorpedo::~MyTorpedo() {
}
