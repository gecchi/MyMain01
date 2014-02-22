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
    pScaler_ = NEW GgafDxScaler(this);
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
    trz_ = try_ = 0;
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
    setScale(100);
    pScaler_->transitionLinerStep(7000, 500);
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
    pKuroko->setRzRyMvAngVelo(0,0);
    pKuroko->setRzRyMvAngAcce(0,0);
    pKuroko->stopTurnMvAng();
    begin_x_ = _x;
    begin_y_ = _y;
    begin_z_ = _z;
    setHitAble(true);
    _pProg->reset(MyTorpedo_IN_FIRE);
    move_section_ = 0;
    //非ターゲット時の方向、オプションの向いてる方向に飛ばす
    trz_ = pOptionTorpedoCtrler_->pOrg_->_rz;
    try_ = pOptionTorpedoCtrler_->pOrg_->_ry;
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
        if (move_section_ == 0) { //発射開始〜減速完了まで
            if (pKuroko->_veloMv == pKuroko->_veloBottomMv) { //減速終了時
                pKuroko->setMvAcce(500);
                if (pTarget_) {
                    //ターゲッティング時は、TURN_ANTICLOSE_TO で動きを見せてターゲット
                    pKuroko->turnMvAngTwd(pTarget_,
                                           2000, 200,
                                           TURN_ANTICLOSE_TO, false);
                } else {
                    pKuroko->turnRzRyMvAngTo(
                                trz_, try_,
                                1000, 100,
                                TURN_CLOSE_TO, false);
                }
                move_section_++;
            }
        }

        //ムーブ１ 減速完了〜方向転換完了
        if (move_section_ == 1) {
            if (pKuroko->isTurningMvAng()) {
                //TURN_ANTICLOSE_TOターゲット完了を待つ
            } else {
                //TURN_ANTICLOSE_TOターゲット完了
                move_section_++;
            }
        }
        //ムーブ２ 方向転換完了〜120フレーム間はやや強い角速度でターゲット補正
        if (move_section_ == 2) {
            if (getActiveFrame() < 120) {
                if (getActiveFrame() % 16U == 0) {
                    if (pTarget_) {
                        if (pTarget_->isActiveInTheTree())  {
                            //ターゲット有り
                            pKuroko->turnMvAngTwd(pTarget_,
                                                   1000, 200,
                                                   TURN_CLOSE_TO, false);

                        } else {
                            //ターゲット消失時、そのまままっすぐ
                            pKuroko->setRzRyMvAngVelo(0,0);
                            pKuroko->setRzRyMvAngAcce(0,0);
                        }
                    } else {
                        //ターゲット無し（オプションの向いている方向へ）
                        pKuroko->turnRzRyMvAngTo(
                                    trz_, try_,
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
        //ムーブ３ 〜300フレーム間は緩やかな角速度でターゲット補正
        if (move_section_ == 3) {
            if (getActiveFrame() < 300) {
                if (getActiveFrame() % 16U == 0) {
                    if (pTarget_) {
                        if (pTarget_->isActiveInTheTree())  {
                            //ターゲット有り
                            pKuroko->turnMvAngTwd(pTarget_,
                                                  500, 0,
                                                  TURN_CLOSE_TO, false);
                        } else {
                            //ターゲット消失時、そのまままっすぐ
                            pKuroko->setRzRyMvAngVelo(0,0);
                            pKuroko->setRzRyMvAngAcce(0,0);
                        }
                    } else {
                        //ターゲット無し（オプションの向いている方向へ）
                        pKuroko->turnRzRyMvAngTo(
                                    trz_, try_,
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
            pKuroko->setRzRyMvAngVelo(0,0);
            pKuroko->setRzRyMvAngAcce(0,0);
        }
        pKuroko->behave();
        pScaler_->behave();
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
    GGAF_DELETE(pScaler_);
}
