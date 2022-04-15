#include "MyTorpedo.h"

#include "jp/ggaf/dx/actor/supporter/SeTransmitterForActor.h"
#include "jp/ggaf/dx/actor/supporter/VecVehicle.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/ggaf/lib/actor/laserchip/LaserChipDepository.h"
#include "jp/ggaf/lib/util/CollisionChecker.h"
#include "jp/ggaf/dx/actor/supporter/Scaler.h"
#include "jp/ggaf/dx/actor/GeometricActor.h"
#include "MyTorpedoBlast.h"
#include "jp/gecchi/VioletVreath/actor/my/MyTorpedoController.h"
#include "MyTorpedoTail.h"



using namespace GgafLib;
using namespace VioletVreath;

enum {
    SE_EXPLOSION,
};

MyTorpedo::MyTorpedo(const char* prm_name, MyTorpedoController* prm_pTorpedoController)
               : VvMyActor<DefaultMeshSetActor>(prm_name, "EffectLaserRefraction001", StatusReset(MyTorpedo)) {
    _class_name = "MyTorpedo";
    pTorpedoCtrler_ = prm_pTorpedoController;
    length_TailEffect_ = 5;
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
    appendGroupChild(pTailEffectDepository_);
    effectBlendOne(); //加算合成するTechnique指定
    setZEnableDraw(true);        //描画時、Zバッファ値は考慮される
    setZWriteEnable(false);  //自身のZバッファを書き込みしない
    pTarget_ = nullptr;
    trz_ = try_ = 0;
    GgafDx::SeTransmitterForActor* pSeTx = getSeTransmitter();
    pSeTx->set(SE_EXPLOSION, "SE_EXPLOSION_TORPEDO");
}

void MyTorpedo::initialize() {
    CollisionChecker* pChecker = getCollisionChecker();
    pChecker->createCollisionArea(1);
    pChecker->setColliAACube(0, 70000);
}

void MyTorpedo::onReset() {
    pTarget_ = nullptr;
}

void MyTorpedo::onActive() {
    getStatus()->reset();
    setAlpha(0.3);
    _sx = _sy = _sz = 100;
    setScale(100);
    getScaler()->transitionLinearStep(7000, 500);
    GgafDx::VecVehicle* const pVecVehicle = getVecVehicle();
    pVecVehicle->setRollPitchYawFaceAngVelo(D_ANG(3), D_ANG(5), D_ANG(7));
    if (pTarget_) {
        pVecVehicle->forceMvVeloRange(4000, 100000);
        pVecVehicle->setMvVelo(20000);
        pVecVehicle->setMvAcce(-600); //最初減速
    } else {
        pVecVehicle->forceMvVeloRange(4000, 70000);
        pVecVehicle->setMvVelo(10000);
        pVecVehicle->setMvAcce(-500); //最初減速
    }

    pVecVehicle->forceRzRyMvAngVeloRange(-40000, 40000);
    pVecVehicle->setRzRyMvAngVelo(0,0);
    pVecVehicle->setRzRyMvAngAcce(0,0);
    pVecVehicle->stopTurningMvAng();
    begin_x_ = _x;
    begin_y_ = _y;
    begin_z_ = _z;
    setHitAble(true);
    getProgress()->reset(MyTorpedo_IN_FIRE);
    move_section_ = 0;
    //非ターゲット時の方向、オプションの向いてる方向に飛ばす
    trz_ = pTorpedoCtrler_->pOrg_->_rz;
    try_ = pTorpedoCtrler_->pOrg_->_ry;
}

void MyTorpedo::processBehavior() {
    GgafDx::VecVehicle* const pVecVehicle = getVecVehicle();
    GgafCore::Progress* const pProg = getProgress();
    if (pProg->get() == MyTorpedo_RELEASE) {
        if (pTailEffectDepository_->_num_chip_active == 0) {
            //軌跡エフェクトが全て非活動になった場合
            inactivate(); //自身を最後にinactivate()
        } else {
            addAlpha(-0.05);
        }
    }

    if (pProg->get() == MyTorpedo_IN_FIRE) {
        //尾っぽエフェクト追加処理
        if (pTailEffectDepository_->_num_chip_active < length_TailEffect_) {
            MyTorpedoTail* pTailEffect = (MyTorpedoTail*)pTailEffectDepository_->dispatch();
            if (pTailEffect) {
                pTailEffect->setPosition(begin_x_,begin_y_,begin_z_);
            }
        }
        //魚雷のムーブ
        if (move_section_ == 0) { //発射開始〜減速完了まで
            if (pVecVehicle->_velo_mv == pVecVehicle->_bottom_velo_mv) { //減速終了時

                if (pTarget_) {
                    //ターゲッティング時は、TURN_CLOSE_TO で動きを見せてターゲット
                    pVecVehicle->setMvAcce(600);
                    pVecVehicle->turnMvAngTwd(pTarget_,
                                          1000, 100,
                                          TURN_CLOSE_TO, false);
                } else {
                    //ノーターゲッティング時は、TURN_ANTICLOSE_TO で動きを真っ直ぐ
                    pVecVehicle->setMvAcce(500);
                    pVecVehicle->turnRzRyMvAngTo(
                                trz_, try_,
                                2000, 200,
                                TURN_ANTICLOSE_TO, false);
                }
                move_section_++;
            }
        }

        //ムーブ１ 減速完了〜方向転換完了
        if (move_section_ == 1) {
            if (pVecVehicle->isTurningMvAng()) {
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
                            pVecVehicle->turnMvAngTwd(pTarget_,
                                                  1000, 200,
                                                  TURN_CLOSE_TO, false);

                        } else {
                            //ターゲット消失時、そのまままっすぐ
                            pVecVehicle->setRzRyMvAngVelo(0, 0);
                            pVecVehicle->setRzRyMvAngAcce(0, 0);
                        }
                    } else {
                        //ターゲット無し（オプションの向いている方向へ）
                        pVecVehicle->turnRzRyMvAngTo(
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
                            pVecVehicle->turnMvAngTwd(pTarget_,
                                                  500, 0,
                                                  TURN_CLOSE_TO, false);
                        } else {
                            //ターゲット消失時、そのまままっすぐ
                            pVecVehicle->setRzRyMvAngVelo(0,0);
                            pVecVehicle->setRzRyMvAngAcce(0,0);
                        }
                    } else {
                        //ターゲット無し（オプションの向いている方向へ）
                        pVecVehicle->turnRzRyMvAngTo(
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
            pVecVehicle->setRzRyMvAngVelo(0,0);
            pVecVehicle->setRzRyMvAngAcce(0,0);
        }
        pVecVehicle->behave();
        getScaler()->behave();
    }
}

void MyTorpedo::processJudgement() {
    GgafCore::Progress* const pProg = getProgress();
    if (isOutOfSpacetime() && pProg->get() == MyTorpedo_IN_FIRE) {
        setHitAble(false);
        pProg->change(MyTorpedo_RELEASE);
        GgafCore::MainActor* pTailEffect = (GgafCore::MainActor*)pTailEffectDepository_->getChildFirst();
        for (int i = 0; i < length_TailEffect_; i++) {
            pTailEffect->inactivateDelay(i+1); //軌跡エフェクトが順々に消えるように予約
            pTailEffect = pTailEffect->getNext();
        }
        getVecVehicle()->setMvVelo(0);
        //自身のinactive()はprocessBehavior()で行われ
        //魚雷の移動エフェクトが全てinactive()になった際に自身もinactive()する
    }

}

void MyTorpedo::onInactive() {
}

void MyTorpedo::onHit(const GgafCore::Actor* prm_pOtherActor) {
    GgafDx::GeometricActor* pOther = (GgafDx::GeometricActor*)prm_pOtherActor;
    //ヒット時通貫はしません
    int sta = UTIL::calcMyStamina(this, pOther);
    setHitAble(false);

    GgafCore::Progress* const pProg = getProgress();
    pProg->change(MyTorpedo_RELEASE);
    GgafCore::MainActor* pTailEffect = (GgafCore::MainActor*)pTailEffectDepository_->getChildFirst();
    for (int i = 0; i < length_TailEffect_; i++) {
        pTailEffect->inactivateDelay(i+1); //軌跡エフェクトが順々に消えるように予約
        pTailEffect = pTailEffect->getNext();
    }
    getVecVehicle()->setMvVelo(0);
    //自身のinactive()はprocessBehavior()で行われ
    //魚雷の移動エフェクトが全てinactive()になった際に自身もinactive()する

    //爆風発生
    MyTorpedoBlast* pBlast = (MyTorpedoBlast*)(pTorpedoCtrler_->pDepo_TorpedoBlast_->dispatchForce());
    getSeTransmitter()->play3D(SE_EXPLOSION);
    pBlast->reset();
    pBlast->setPositionAt(this);
}

MyTorpedo::~MyTorpedo() {
}
