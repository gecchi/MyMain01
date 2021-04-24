#include "EnemyGlajaLance001.h"

#include "jp/ggaf/dx/actor/supporter/VecDriver.h"
#include "jp/ggaf/dx/actor/supporter/SeTransmitterForActor.h"
#include "jp/ggaf/lib/util/CollisionChecker.h"
#include "jp/gecchi/VioletVreath/actor/effect/EffectExplosion001.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/CommonScene.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/MyShipScene.h"
#include "jp/ggaf/dx/actor/supporter/Scaler.h"
#include "jp/ggaf/dx/actor/supporter/VecDriverFaceAngAssistant.h"

using namespace GgafLib;
using namespace VioletVreath;

enum {
    PROG_INIT   ,
    PROG_MOVE01 ,
    PROG_AIM_ANIME01 ,
    PROG_AIM_ANIME02 ,
    PROG_MOVE02 ,
    PROG_MOVE03 ,
    PROG_LEAVE ,
    PROG_BANPEI,
};

EnemyGlajaLance001::EnemyGlajaLance001(const char* prm_name) :
        VvEnemyActor<DefaultMeshSetActor>(prm_name, "GlajaLance001", StatusReset(EnemyGlajaLance001)) {
    _class_name = "EnemyGlajaLance001";
    effectBlendOne(); //加算合成
    setZEnableDraw(true);
    setZWriteEnable(false);
}

void EnemyGlajaLance001::initialize() {
    setHitAble(false);
    CollisionChecker* pChecker = getCollisionChecker();
    pChecker->createCollisionArea(3);
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
    GgafDx::VecDriver* const pVecDriver = getVecDriver();
    pVecDriver->setMvAcce(0);
    pVecDriver->setMvVelo(PX_C(3));
    setRollPitchYawFaceAng(0, RND(D_ANG(0), D_ANG(360)),
                              RND(D_ANG(0), D_ANG(360)) );
    pVecDriver->setRollPitchYawFaceAngVelo(D_ANG(0), D_ANG(20), D_ANG(15));
    pVecDriver->linkFaceAngByMvAng(true);
    CollisionChecker* pChecker = getCollisionChecker();
    pChecker->disable(1);
    pChecker->disable(2);
    setScale(R_SC(1));
    GgafDx::Scaler* const pScaler = getScaler();
    pScaler->reset();
    pScaler->behave();
    getStatus()->reset();
    setCullingDraw(false);
    getProgress()->reset(PROG_INIT);
}

void EnemyGlajaLance001::processBehavior() {
    MyShip* pMyShip = pMYSHIP;
    GgafDx::VecDriver* const pVecDriver = getVecDriver();
    GgafDx::Scaler* const pScaler = getScaler();
    GgafCore::Progress* const pProg = getProgress();
    switch (pProg->get()) {
        case PROG_INIT: {
            setHitAble(true, false);
            //_pVecDriver->setMvAngTwd(&turning_pos_);
            pProg->changeNext();
            break;
        }
        case PROG_MOVE01: {
            if (pProg->hasJustChanged()) {

            }
            if (pProg->hasArrivedAt(120)) {
                pProg->changeNext();
            }
            break;
        }
        case PROG_AIM_ANIME01: {
            if (pProg->hasJustChanged()) {
                //シャキーンと槍になる！（伸びる！）
                pVecDriver->stopMv();
                pVecDriver->setRollPitchYawFaceAngVelo(0, 0, 0);
                pScaler->transitionAcceUntil(AXIS_X, R_SC(30), R_SC(1), R_SC(0.1));
                pScaler->transitionAcceUntil(AXIS_Y, R_SC(2), R_SC(1), R_SC(0.1));
                pScaler->transitionAcceUntil(AXIS_Z, R_SC(2), R_SC(1), R_SC(0.1));
            }
            if (!pScaler->isTransitioning()) {
                //槍の両端当たり判定出現
                CollisionChecker* pChecker = getCollisionChecker();
                pChecker->enable(1);
                pChecker->enable(2);
                pProg->changeNext();
             }

             break;
        }
        case PROG_AIM_ANIME02: {
            if (pProg->hasJustChanged()) {
                //自機にグルンと向く
                pVecDriver->asstFaceAng()->turnByDtTwd(pMyShip, TURN_ANTICLOSE_TO, false,
                                                        60, 0.2, 0.4, 0, true );
            }
            if (!pVecDriver->isTurningFaceAng()) {
                pProg->changeNext();
            }
            break;
        }
        case PROG_MOVE02: {
            if (pProg->hasJustChanged()) {
                pVecDriver->setMvAngByFaceAng(); //今向いてる方向にこれから移動する
                pVecDriver->setMvVelo(-PX_C(3)); //ちょっとバックして貯めを表現
                pVecDriver->setRollFaceAngVelo(D_ANG(1)); //スピンスピン
                pVecDriver->setRollFaceAngAcce(100); //スピンスピン
            }
            if (pProg->getFrame() >= 60) {
                pProg->changeNext();
            }
            break;
        }
        case PROG_MOVE03: {
            if (pProg->hasJustChanged()) {
                //ズキューーンと移動
                pVecDriver->setMvVelo(PX_C(50));
            }
            //画面外 or HIT まで待機
            break;
        }

        case PROG_LEAVE: {
            if (pProg->hasJustChanged()) {
                //HIT後消えるまで
            }
            addAlpha(-1.0/90.0); //sayonara(90);だから
            break;
        }
    }
    //座標に反映
    pScaler->behave();
    pVecDriver->behave();
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

void EnemyGlajaLance001::onHit(const GgafCore::Actor* prm_pOtherActor) {
    bool was_destroyed = UTIL::performEnemyHit(this, (const GgafDx::GeometricActor*)prm_pOtherActor);
    if (was_destroyed) {
        //破壊された時(スタミナ <= 0)
        getVecDriver()->stopMv();
        sayonara(90);
        getProgress()->change(PROG_LEAVE); //矢がフェードアウトする
    } else {
        //破壊されなかった時(スタミナ > 0)
    }
}

EnemyGlajaLance001::~EnemyGlajaLance001() {
}
