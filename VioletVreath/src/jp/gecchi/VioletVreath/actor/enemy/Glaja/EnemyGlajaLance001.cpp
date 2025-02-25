#include "EnemyGlajaLance001.h"

#include "jp/ggaf/dx/actor/supporter/LocusVehicle.h"
#include "jp/ggaf/dx/actor/supporter/SeTransmitterForActor.h"
#include "jp/ggaf/lib/util/WorldCollisionChecker.h"
#include "jp/gecchi/VioletVreath/actor/effect/EffectExplosion001.h"
#include "jp/gecchi/VioletVreath/Caretaker.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/CommonScene.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/MyShipScene.h"
#include "jp/ggaf/dx/actor/supporter/Scaler.h"
#include "jp/ggaf/dx/actor/supporter/LocusVehicleFaceAngAssistant.h"

using namespace GgafLib;
using namespace VioletVreath;

enum {
    PHASE_INIT   ,
    PHASE_MOVE01 ,
    PHASE_AIM_ANIME01 ,
    PHASE_AIM_ANIME02 ,
    PHASE_MOVE02 ,
    PHASE_MOVE03 ,
    PHASE_LEAVE ,
    PHASE_BANPEI,
};

EnemyGlajaLance001::EnemyGlajaLance001(const char* prm_name) :
        VvEnemyActor<DefaultMeshSetActor>(prm_name, "GlajaLance001", StatusReset(EnemyGlajaLance001)) {
    _class_name = "EnemyGlajaLance001";
    effectBlendOne(); //加算合成
    useZBufferDrawing(true);
    setZBufferWriteEnable(false);
}

void EnemyGlajaLance001::initialize() {
    setHitAble(false);
    WorldCollisionChecker* pChecker = getWorldCollisionChecker();
    pChecker->addCollisionArea(1);
    pChecker->setColliAACube(0, PX_C(20));

    pChecker->addCollisionArea(3);
    pChecker->setColliAACube(0, PX_C(20));
    pChecker->setColliAACube(1, -PX_C(80), 0, 0,
                                        PX_C(10),
                                        true, true, true);
    pChecker->setColliAACube(2, PX_C(80), 0, 0,
                                        PX_C(10),
                                        true, true, true);

}
void EnemyGlajaLance001::onReset() {

}

void EnemyGlajaLance001::onActive() {
    GgafDx::LocusVehicle* pLocusVehicle = getLocusVehicle();
    pLocusVehicle->setMvAcce(0);
    pLocusVehicle->setMvVelo(PX_C(3));
    setRollPitchYawFaceAng(0, RND(D_ANG(0), D_ANG(360)),
                              RND(D_ANG(0), D_ANG(360)) );
    pLocusVehicle->setRollPitchYawFaceAngVelo(D_ANG(0), D_ANG(20), D_ANG(15));
    pLocusVehicle->linkFaceAngByMvAng(true);
    WorldCollisionChecker* pChecker = getWorldCollisionChecker();
    pChecker->changeCollisionArea(0);
//    pChecker->disable(1);
//    pChecker->disable(2);
    setScale(R_SC(1));
    GgafDx::Scaler* const pScaler = getScaler();
    pScaler->reset();
    pScaler->behave();
    getStatus()->reset();
    setCullingDraw(false);
    getPhase()->reset(PHASE_INIT);
}

void EnemyGlajaLance001::processBehavior() {
    MyShip* pMyShip = pMYSHIP;
    GgafDx::LocusVehicle* pLocusVehicle = getLocusVehicle();
    GgafDx::Scaler* const pScaler = getScaler();
    GgafCore::Phase* pPhase = getPhase();
    switch (pPhase->getCurrent()) {
        case PHASE_INIT: {
            setHitAble(true, false);
            //_pLocusVehicle->setMvAngTwd(&turning_pos_);
            pPhase->changeNext();
            break;
        }
        case PHASE_MOVE01: {
            if (pPhase->hasJustChanged()) {

            }
            if (pPhase->hasArrivedFrameAt(120)) {
                pPhase->changeNext();
            }
            break;
        }
        case PHASE_AIM_ANIME01: {
            if (pPhase->hasJustChanged()) {
                //シャキーンと槍になる！（伸びる！）
                pLocusVehicle->stop();
                pLocusVehicle->setRollPitchYawFaceAngVelo(0, 0, 0);
                pScaler->transitionAcceUntil(AXIS_X, R_SC(30), R_SC(1), R_SC(0.1));
                pScaler->transitionAcceUntil(AXIS_Y, R_SC(2), R_SC(1), R_SC(0.1));
                pScaler->transitionAcceUntil(AXIS_Z, R_SC(2), R_SC(1), R_SC(0.1));
            }
            if (!pScaler->isTransitioning()) {
                //槍の両端当たり判定出現
                WorldCollisionChecker* pChecker = getWorldCollisionChecker();
                pChecker->changeCollisionArea(1);
//                pChecker->enable(1);
//                pChecker->enable(2);
                pPhase->changeNext();
             }

             break;
        }
        case PHASE_AIM_ANIME02: {
            if (pPhase->hasJustChanged()) {
                //自機にグルンと向く
                pLocusVehicle->asstFaceAng()->turnByDtTwd(pMyShip, TURN_ANTICLOSE_TO, false,
                                                        60, 0.2, 0.4, 0, true );
            }
            if (!pLocusVehicle->isTurningFaceAng()) {
                pPhase->changeNext();
            }
            break;
        }
        case PHASE_MOVE02: {
            if (pPhase->hasJustChanged()) {
                pLocusVehicle->setMvAngByFaceAng(); //今向いてる方向にこれから移動する
                pLocusVehicle->setMvVelo(-PX_C(3)); //ちょっとバックして貯めを表現
                pLocusVehicle->setRollFaceAngVelo(D_ANG(1)); //スピンスピン
                pLocusVehicle->setRollFaceAngAcce(100); //スピンスピン
            }
            if (pPhase->getFrame() >= 60) {
                pPhase->changeNext();
            }
            break;
        }
        case PHASE_MOVE03: {
            if (pPhase->hasJustChanged()) {
                //ズキューーンと移動
                pLocusVehicle->setMvVelo(PX_C(50));
            }
            //画面外 or HIT まで待機
            break;
        }

        case PHASE_LEAVE: {
            if (pPhase->hasJustChanged()) {
                //HIT後消えるまで
            }
            addAlpha(-1.0/SEC_F(1.5)); //sayonara(SEC_F(1.5));だから
            break;
        }
    }
    //座標に反映
    pScaler->behave();
    pLocusVehicle->behave();
}

void EnemyGlajaLance001::processJudgement() {
    if (isOutOfView()) {
        if (getActiveFrame() > 180) {
            sayonara();
        }
    }
    if (isOutOfSpacetime()) {
        sayonara();
    }
}

void EnemyGlajaLance001::onHit(const GgafCore::Checker* prm_pThisHitChecker, const GgafCore::Checker* prm_pOppHitChecker) {
    bool is_stamina_zero = performEnemyHit(prm_pOppHitChecker);
    if (is_stamina_zero) {
        //破壊された時(スタミナ <= 0)
        getLocusVehicle()->stop();
        sayonara(SEC_F(1.5));
        getPhase()->change(PHASE_LEAVE); //矢がフェードアウトする
    } else {
        //破壊されなかった時(スタミナ > 0)
    }
}

EnemyGlajaLance001::~EnemyGlajaLance001() {
}
