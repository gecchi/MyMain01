#include "EnemyGlajaLance001.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxSeTransmitterForActor.h"
#include "jp/ggaf/lib/util/CollisionChecker.h"
#include "jp/gecchi/VioletVreath/actor/effect/EffectExplosion001.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/CommonScene.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/MyShipScene.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxScaler.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoFaceAngAssistant.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

EnemyGlajaLance001::EnemyGlajaLance001(const char* prm_name) :
        DefaultMeshSetActor(prm_name, "GlajaLance001", STATUS(EnemyGlajaLance001)) {
    _class_name = "EnemyGlajaLance001";
    pScaler_ = NEW GgafDxScaler(this);
    effectBlendOne(); //加算合成
    setZEnableDraw(true);
    setZWriteEnable(false);
    useProgress(PROG_BANPEI);
}

void EnemyGlajaLance001::initialize() {
    setHitAble(false);
    CollisionChecker* pChecker = getCollisionChecker();
    pChecker->createCollisionArea(3);
    pChecker->setColliAABox_Cube(0, PX_C(20));
    pChecker->setColliAABox_Cube(1, -PX_C(80), 0, 0,
                                        PX_C(10),
                                        true, true, true);
    pChecker->setColliAABox_Cube(2, PX_C(80), 0, 0,
                                        PX_C(10),
                                        true, true, true);

}
void EnemyGlajaLance001::onReset() {

}

void EnemyGlajaLance001::onActive() {
    GgafDxKuroko* const pKuroko = getKuroko();
    pKuroko->setMvAcce(0);
    pKuroko->setMvVelo(PX_C(3));
    setRollPitchYawFaceAng(0, RND(D_ANG(0), D_ANG(360)),
                              RND(D_ANG(0), D_ANG(360)) );
    pKuroko->setRollPitchYawFaceAngVelo(D_ANG(0), D_ANG(20), D_ANG(15));
    pKuroko->linkFaceAngByMvAng(true);
    CollisionChecker* pChecker = getCollisionChecker();
    pChecker->disable(1);
    pChecker->disable(2);
    setScale(R_SC(1));
    pScaler_->reset();
    pScaler_->behave();
    getStatus()->reset();
    setAlpha(0.99);
    getProgress()->reset(PROG_INIT);
}

void EnemyGlajaLance001::processBehavior() {
    MyShip* pMyShip = P_MYSHIP;
    GgafDxKuroko* const pKuroko = getKuroko();
    GgafProgress* const pProg = getProgress();
    switch (pProg->get()) {
        case PROG_INIT: {
            setHitAble(true, false);
            //_pKuroko->setMvAngTwd(&turning_pos_);
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
                pKuroko->stopMv();
                pKuroko->setRollPitchYawFaceAngVelo(0, 0, 0);
                pScaler_->transitionAcceUntil(AXIS_X, R_SC(30), R_SC(1), R_SC(0.1));
                pScaler_->transitionAcceUntil(AXIS_Y, R_SC(2), R_SC(1), R_SC(0.1));
                pScaler_->transitionAcceUntil(AXIS_Z, R_SC(2), R_SC(1), R_SC(0.1));
            }
            if (!pScaler_->isTransitioning()) {
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
                pKuroko->asstFaceAng()->turnByDtTwd(pMyShip, TURN_ANTICLOSE_TO, false,
                                                        60, 0.2, 0.4, 0, true );
            }
            if (!pKuroko->isTurningFaceAng()) {
                pProg->changeNext();
            }
            break;
        }
        case PROG_MOVE02: {
            if (pProg->hasJustChanged()) {
                pKuroko->setMvAngByFaceAng(); //今向いてる方向にこれから移動する
                pKuroko->setMvVelo(-PX_C(3)); //ちょっとバックして貯めを表現
                pKuroko->setRollFaceAngVelo(D_ANG(1)); //スピンスピン
                pKuroko->setRollFaceAngAcce(100); //スピンスピン
            }
            if (pProg->getFrame() >= 60) {
                pProg->changeNext();
            }
            break;
        }
        case PROG_MOVE03: {
            if (pProg->hasJustChanged()) {
                //ズキューーンと移動
                pKuroko->setMvVelo(PX_C(50));
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
    pScaler_->behave();
    pKuroko->behave();
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

void EnemyGlajaLance001::onHit(const GgafActor* prm_pOtherActor) {
    bool was_destroyed = UTIL::performEnemyHit(this, (const GgafDxGeometricActor*)prm_pOtherActor);
    if (was_destroyed) {
        //破壊された時(スタミナ <= 0)
        getKuroko()->stopMv();
        sayonara(90);
        getProgress()->change(PROG_LEAVE); //矢がフェードアウトする
    } else {
        //破壊されなかった時(スタミナ > 0)
    }
}

EnemyGlajaLance001::~EnemyGlajaLance001() {
    GGAF_DELETE(pScaler_);
}
