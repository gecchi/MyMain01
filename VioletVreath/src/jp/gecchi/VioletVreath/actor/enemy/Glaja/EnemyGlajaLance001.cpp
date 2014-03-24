#include "stdafx.h"
#include "EnemyGlajaLance001.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxSeTransmitterForActor.h"
#include "jp/ggaf/lib/util/CollisionChecker3D.h"
#include "jp/gecchi/VioletVreath/actor/effect/EffectExplosion001.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/CommonScene.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/MyShipScene.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxScaler.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoHelperB.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

EnemyGlajaLance001::EnemyGlajaLance001(const char* prm_name) :
        DefaultMeshSetActor(prm_name, "GlajaLance001", STATUS(EnemyGlajaLance001)) {
    _class_name = "EnemyGlajaLance001";
    pScaler_ = NEW GgafDxScaler(this);
    effectBlendOne(); //加算合成
    setZEnable(true);
    setZWriteEnable(false);
    useProgress(PROG_BANPEI);
}

void EnemyGlajaLance001::initialize() {
    setHitAble(false);
    CollisionChecker3D* pColliChecker = getCollisionChecker();
    pColliChecker->makeCollision(3);
    pColliChecker->setColliAAB_Cube(0, PX_C(20));
    pColliChecker->setColliAAB_Cube(1, -PX_C(80), 0, 0,
                                        PX_C(10),
                                        true, true, true);
    pColliChecker->setColliAAB_Cube(2, PX_C(80), 0, 0,
                                        PX_C(10),
                                        true, true, true);

}
void EnemyGlajaLance001::onReset() {

}

void EnemyGlajaLance001::onActive() {
    GgafDxKuroko* pKuroko = getKuroko();
    pKuroko->setMvAcce(0);
    pKuroko->setMvVelo(PX_C(3));
    setFaceAng(0,
               RND(D_ANG(0), D_ANG(360)),
               RND(D_ANG(0), D_ANG(360)) );
    pKuroko->setFaceAngVelo(D_ANG(33), D_ANG(15), D_ANG(20));
    pKuroko->relateFaceWithMvAng(true);
    CollisionChecker3D* pColliChecker = getCollisionChecker();
    pColliChecker->disable(1);
    pColliChecker->disable(2);
    pScaler_->reset();
    pScaler_->behave();
    getStatus()->reset();
    setAlpha(0.99);
    getProgress()->reset(PROG_INIT);
}

void EnemyGlajaLance001::processBehavior() {
    MyShip* pMyShip = P_MYSHIP;
    GgafDxKuroko* pKuroko = getKuroko();
    GgafProgress* pProg = getProgress();
    switch (pProg->get()) {
        case PROG_INIT: {
            setHitAble(true, false);
            //_pKuroko->setMvAngTwd(&turning_pos_);
            pProg->changeNext();
            break;
        }
        case PROG_MOVE01: {
            if (pProg->isJustChanged()) {

            }
            if (pProg->getFrameInProgress() == 120) {
                pProg->changeNext();
            }
            break;
        }
        case PROG_AIM_ANIME01: {
            if (pProg->isJustChanged()) {
                //シャキーンと槍になる！（伸びる！）
                pKuroko->stopMv();
                pKuroko->setFaceAngVelo(0, 0, 0);
                pScaler_->transitionAcceStep(AXIS_X, R_SC(30), R_SC(1), R_SC(0.1));
            }
            if (!pScaler_->isTransitioning()) {
                //槍の両端当たり判定出現
                CollisionChecker3D* pColliChecker = getCollisionChecker();
                pColliChecker->enable(1);
                pColliChecker->enable(2);
                pProg->changeNext();
             }

             break;
        }
        case PROG_AIM_ANIME02: {
            if (pProg->isJustChanged()) {
                //自機にグルンと向く
                pKuroko->hlprB()->turnFaceAngByDtTwd(pMyShip, TURN_ANTICLOSE_TO, false,
                                                        30, 0.2, 0.4, 0, true );
            }
            if (!pKuroko->isTurningFaceAng()) {
                pProg->changeNext();
            }
            break;
        }
        case PROG_MOVE02: {
            if (pProg->isJustChanged()) {
                pKuroko->setMvAngByFaceAng(); //今向いてる方向にこれから移動する
                pKuroko->setMvVelo(-PX_C(2)); //ちょっとバックして貯めを表現
                setRzFaceAng(D_ANG(27)); //スピンスピン
            }
            if (pProg->getFrameInProgress() >= 10) {
                pProg->changeNext();
            }
            break;
        }
        case PROG_MOVE03: {
            if (pProg->isJustChanged()) {
                //ズキューーンと移動
                pKuroko->setMvVelo(PX_C(60));
            }
            //画面外 or HIT まで待機
            break;
        }

        case PROG_LEAVE: {
            if (pProg->isJustChanged()) {
                //HIT後消えるまで
            }
            addAlpha(-1.0/90.0); //sayonara(90);だから
            break;
        }
    }
    //座標に反映
    pScaler_->behave();
    pKuroko->behave();
}

void EnemyGlajaLance001::processJudgement() {
    if (isOutOfView()) {
        if (getActiveFrame() > 60) {
            sayonara();
        }
    }
    if (isOutOfUniverse()) {
        sayonara();
    }
}

void EnemyGlajaLance001::onHit(GgafActor* prm_pOtherActor) {
    GgafDxGeometricActor* pOther = (GgafDxGeometricActor*)prm_pOtherActor;
    if (UTIL::calcEnemyStamina(this, pOther) <= 0) {
        setHitAble(false);
        UTIL::activateExplosionEffectOf(this); //爆発エフェクト
        getKuroko()->stopMv();
        sayonara(90);
        getProgress()->change(PROG_LEAVE);
    }
}

EnemyGlajaLance001::~EnemyGlajaLance001() {
    GGAF_DELETE(pScaler_);
}
