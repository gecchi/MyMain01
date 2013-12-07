#include "stdafx.h"
#include "MyTorpedo.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxSeTransmitterForActor.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/ggaf/lib/actor/laserchip/LaserChipDepository.h"
#include "jp/ggaf/lib/util/CollisionChecker3D.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxScaler.h"
#include "jp/ggaf/dxcore/actor/GgafDxGeometricActor.h"
#include "MyTorpedoBlast.h"
#include "jp/gecchi/VioletVreath/actor/my/MyTorpedoController.h"
#include "MyTorpedoTail.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

MyTorpedo::MyTorpedo(const char* prm_name, MyTorpedoController* prm_pOptionTorpedoController)
               : DefaultMeshSetActor(prm_name, "EffectLaserRefraction001", STATUS(MyTorpedo)) {
    _class_name = "MyTorpedo";
    pOptionTorpedoCtrler_ = prm_pOptionTorpedoController;
    length_TailEffect_ = 8;
    begin_x_ = _x;
    begin_y_ = _y;
    begin_z_ = _z;

    pTailEffectDepository_ = NEW LaserChipDepository("Depo_TorpedoTailEffect");
    pTailEffectDepository_->config(length_TailEffect_, 0, nullptr);
    for (int i = 0; i < length_TailEffect_; i++) {
        std::string name = std::string(getName())+"'s Tail("+XTOS(i)+")";
        pTailEffectDepository_->put(NEW MyTorpedoTail(name.c_str(), this));
    }
    move_section_ = 0;
    addSubGroup(pTailEffectDepository_);
    effectBlendOne(); //加算合成するTechnique指定
    setZEnable(true);        //Zバッファは考慮有り
    setZWriteEnable(false);  //Zバッファは書き込み無し
    pTarget_ = nullptr;
    useProgress(10);

    _pSeTx->set(SE_EXPLOSION, "WAVE_EXPLOSION_TORPEDO");
}

void MyTorpedo::initialize() {
    _pColliChecker->makeCollision(1);
    _pColliChecker->setColliAAB_Cube(0, 70000);
}

void MyTorpedo::onReset() {
    pTarget_ = nullptr;
}

void MyTorpedo::onActive() {
    GgafDxKuroko* const pKuroko = _pKuroko;
    _pStatus->reset();
    setAlpha(0.3);
    _sx = _sy = _sz = 100;
    _pScaler->setScale(100);
    _pScaler->scaleLinerStep(7000, 500);
    pKuroko->setFaceAngVelo(D_ANG(3), D_ANG(5), D_ANG(7));
    if (pTarget_) {
        pKuroko->forceMvVeloRange(4000, 100000);
        pKuroko->setMvVelo(20000);
        pKuroko->setMvAcce(-600); //最初減速
    } else {
        pKuroko->forceMvVeloRange(4000, 70000);
        pKuroko->setMvVelo(10000);
        pKuroko->setMvAcce(-500); //最初減速
    }

    pKuroko->forceRzRyMvAngVeloRange(-40000, 40000);
    pKuroko->setRzRyMvAngVelo(0);
    pKuroko->setRzRyMvAngAcce(0);
    pKuroko->stopTurnMvAngSequence();
    begin_x_ = _x;
    begin_y_ = _y;
    begin_z_ = _z;
    setHitAble(true);
    _pProg->reset(MyTorpedo_IN_FIRE);
    move_section_ = 0;
}

void MyTorpedo::processBehavior() {
    GgafDxKuroko* const pKuroko = _pKuroko;
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
                pTailEffect->position(begin_x_,begin_y_,begin_z_);
            }
        }
        //魚雷のムーブ
        if (move_section_ == 0) {
            if (pKuroko->_veloMv == pKuroko->_veloBottomMv) { //減速終了
                pKuroko->setMvAcce(500);
                if (pTarget_) {
                    pKuroko->turnMvAngTwd(pTarget_,
                                           2000, 200,
                                           TURN_ANTICLOSE_TO, false);
                } else {
                    pKuroko->turnRzRyMvAngTo(
                                pOptionTorpedoCtrler_->pOrg_->_rz, pOptionTorpedoCtrler_->pOrg_->_ry,
                                1000, 100,
                                TURN_CLOSE_TO, false);

//                    pKuroko->turnMvAngTwd(
//                                GgafDxUniverse::_x_gone_right, P_MYSHIP->_y, P_MYSHIP->_z,
//                                2000, 200,
//                                TURN_ANTICLOSE_TO, false);
                }
                move_section_++;
            }
        }

        //ムーブ１
        if (move_section_ == 1) {
            if (pKuroko->isTurningMvAng()) {
                //TURN_ANTICLOSE_TOターゲット完了を待つ
            } else {
                //TURN_ANTICLOSE_TOターゲット完了
                move_section_++;
            }
        }
        //ムーブ２
        if (move_section_ == 2) {
            if (getActiveFrame() < 120) {
                if (getActiveFrame() % 16U == 0) {
                    if (pTarget_) {
                        if (pTarget_->isActiveInTheTree())  {

                            pKuroko->turnMvAngTwd(pTarget_,
                                                   1000, 200,
                                                   TURN_CLOSE_TO, false);

                        } else {
                            //まっすぐ
                            pKuroko->setRzRyMvAngVelo(0);
                            pKuroko->setRzRyMvAngAcce(0);
                        }
                    } else {
                        pKuroko->turnRzRyMvAngTo(
                                    pOptionTorpedoCtrler_->pOrg_->_rz, pOptionTorpedoCtrler_->pOrg_->_ry,
                                    1000, 200,
                                    TURN_CLOSE_TO, false);
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
            if (getActiveFrame() < 300) {
                if (getActiveFrame() % 16U == 0) {
                    if (pTarget_) {
                        if (pTarget_->isActiveInTheTree())  {

                            pKuroko->turnMvAngTwd(pTarget_,
                                                   500, 0,
                                                   TURN_CLOSE_TO, false);

//                            //カクカクっと反射っぽく
//                            angle out_angRz_Target;
//                            angle out_angRy_Target;
//                            angle out_d_angRz;
//                            angle out_d_angRy;
//                            UTIL::convVectorToRzRy(pTarget_->_x - _x,
//                                                   pTarget_->_y - _y,
//                                                   pTarget_->_z - _z,
//                                                   out_angRz_Target,
//                                                   out_angRy_Target);
//                            out_d_angRz = pKuroko->getRzMvAngDistance(out_angRz_Target, TURN_CLOSE_TO);
//                            out_d_angRy = pKuroko->getRyMvAngDistance(out_angRy_Target, TURN_CLOSE_TO);
//                            pKuroko->addRzMvAng(SGN(out_d_angRz)*30000);
//                            pKuroko->addRyMvAng(SGN(out_d_angRy)*30000);

                        } else {
                            //まっすぐ
                            pKuroko->setRzRyMvAngVelo(0);
                            pKuroko->setRzRyMvAngAcce(0);
                        }
                    } else {
                        pKuroko->turnRzRyMvAngTo(
                                    pOptionTorpedoCtrler_->pOrg_->_rz, pOptionTorpedoCtrler_->pOrg_->_ry,
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
            pKuroko->setRzRyMvAngVelo(0);
            pKuroko->setRzRyMvAngAcce(0);
        }

        pKuroko->behave();
        _pScaler->behave();
    }
}

void MyTorpedo::processJudgement() {
    if (isOutOfUniverse() && _pProg->get() == MyTorpedo_IN_FIRE) {
        setHitAble(false);
        _pProg->change(MyTorpedo_RELEASE);
        GgafMainActor* pTailEffect = (GgafMainActor*)pTailEffectDepository_->getSubFirst();
        for (int i = 0; i < length_TailEffect_; i++) {
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
    GgafDxGeometricActor* pOther = (GgafDxGeometricActor*)prm_pOtherActor;
    //ヒット時通貫はしません
    int sta = UTIL::calcMyStamina(this, pOther);
    setHitAble(false);
    _pProg->change(MyTorpedo_RELEASE);
    GgafMainActor* pTailEffect = (GgafMainActor*)pTailEffectDepository_->getSubFirst();
    for (int i = 0; i < length_TailEffect_; i++) {
        pTailEffect->inactivateDelay(i+1); //軌跡エフェクトが順々に消えるように予約
        pTailEffect = pTailEffect->getNext();
    }
    _pKuroko->setMvVelo(0);
    //自身のinactive()はprocessBehavior()で行われ
    //魚雷の移動エフェクトが全てinactive()になった際に自身もinactive()する

    //爆風発生
    MyTorpedoBlast* pBlast = (MyTorpedoBlast*)(pOptionTorpedoCtrler_->pDepo_TorpedoBlast_->dispatchForce());
    _pSeTx->play3D(SE_EXPLOSION);
    pBlast->reset();
    pBlast->positionAs(this);
}

MyTorpedo::~MyTorpedo() {
}
