#include "stdafx.h"
#include "EnemyAppho.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxAlphaFader.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxSeTransmitterForActor.h"
#include "jp/ggaf/lib/util/CollisionChecker3D.h"
#include "jp/gecchi/VioletVreath/GameGlobal.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/MyShipScene.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoAssistantA.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

EnemyAppho::EnemyAppho(const char* prm_name) :
        DefaultMeshSetActor(prm_name, "Appho", STATUS(EnemyAppho)) {
    _class_name = "EnemyAppho";
    pAFader_ = NEW GgafDxAlphaFader(this);
    GgafDxSeTransmitterForActor* pSeTx = getSeTx();
    pSeTx->set(SE_EXPLOSION, "WAVE_EXPLOSION_001");
    useProgress(PROG_BANPEI);
}

void EnemyAppho::onCreateModel() {
//    pModel->setSpecular(5.0, 1.0);
}

void EnemyAppho::initialize() {
    setScale(100);
    CollisionChecker3D* pColliChecker = getCollisionChecker();
    pColliChecker->makeCollision(1);
    pColliChecker->setColliAAB_Cube(0, 40000);
}

void EnemyAppho::onActive() {
    getStatus()->reset();
    getProgress()->reset(PROG_INIT);
}

void EnemyAppho::processBehavior() {
    //加算ランクポイントを減少
    UTIL::updateEnemyRankPoint(this);
    GgafDxKuroko* pKuroko = getKuroko();
    GgafProgress* pProg = getProgress();
    switch (pProg->get()) {
         case PROG_INIT: {
             setHitAble(false);
             positionAs(&entry_pos_);
             setAlpha(0);
             pKuroko->setMvVelo(0);
             pKuroko->relateFaceByMvAng(true);
             pKuroko->setMvAngTwd(&hanging_pos_);
             pKuroko->setFaceAngVelo(AXIS_X, D_ANG(3));
             UTIL::activateEntryEffectOf(this);
             pProg->changeNext();
             break;
         }
         case PROG_ENTRY: {
             if (pProg->getFrameInProgress() == 60) {
                 pAFader_->transitionLinerUntil(1.0, 60);
             }
             if (getAlpha() > 0.5) {
                 setHitAble(true);
                 pProg->changeNext();
             }
             break;
         }

         case PROG_MOVE01: {
             if (pProg->isJustChanged()) {
                 //滞留ポイントへGO!
                 velo mv_velo = RF_EnemyAppho_MvVelo(G_RANK);
                 coord d = UTIL::getDistance(this, &hanging_pos_);
                 pKuroko->asstA()->slideMvByVd(mv_velo, d,
                                        0.2, 0.8, RND(-PX_C(0.5),PX_C(0.5)), true);
             }
             //滞留ポイントまで移動中
             if (pProg->getFrameInProgress() % 32U == 0) {
                 //ちょくちょく自機を見つめる
                 pKuroko->turnFaceAngTwd(P_MYSHIP, D_ANG(0.5), 0,
                                          TURN_CLOSE_TO, true);
             }
             if (pKuroko->asstA()->isJustFinishSlidingMv()) {
                 pProg->changeNext();
             }
             //_TRACE_("PROG_MOVE01:"<<_x<<","<<_y<<","<<_z<<","<<_pKuroko->_veloMv<<","<<_pKuroko->_accMv);
             break;
         }

         case PROG_MOVE02: {
             if (pProg->isJustChanged()) {
                 //移動方向と向きの連携解除
                 pKuroko->relateFaceByMvAng(false);
                 //滞留ポイント到着、ふらふら気ままな方向へ移動させる
                 pKuroko->turnMvAngTwd(_x + RND(-PX_C(100),PX_C(100)),
                                       _y + RND(-PX_C(100),PX_C(100)),
                                       _z + RND(-PX_C(100),PX_C(100)),
                                       100, 0, TURN_CLOSE_TO, false);
                 //ゆっくり自機の方へ向かせる
                 pKuroko->turnFaceAngTwd(P_MYSHIP,
                                         D_ANG(1), 0, TURN_CLOSE_TO, true);
             }
             //滞留中
             if (pProg->getFrameInProgress() % 16U == 0) {
                 //ちょくちょく自機を見つめる
                 pKuroko->turnFaceAngTwd(P_MYSHIP,
                                         D_ANG(1), 0, TURN_CLOSE_TO, true);
             }

             if (pProg->getFrameInProgress() == 180) {
                 //自機の方に向いたら敵弾発射！
                 int shot_num   = RF_EnemyAppho_ShotWay(G_RANK);    //弾数、ランク変動
                 velo shot_velo = RF_EnemyAppho_ShotMvVelo(G_RANK); //弾速、ランク変動
                 for (int i = 0; i < shot_num; i++) {
                     GgafDxDrawableActor* pShot = UTIL::activateAttackShotOf(this);
                     if (pShot) {
                         pShot->activateDelay(1+(i*10)); //ばらつかせ。activate タイミング上書き！
                         GgafDxKuroko* pShot_pKuroko = pShot->getKuroko();
                         pShot_pKuroko->setRzRyMvAng(_rz, _ry);
                         pShot_pKuroko->setMvVelo(shot_velo);
                         pShot_pKuroko->setMvAcce(100);
                     }
                 }
             }
             if (pProg->getFrameInProgress() == 240) {
                 pProg->changeNext();
             }
             break;
         }

         case PROG_MOVE03: {
             //さよなら準備
             if (pProg->isJustChanged()) {
                 //ゆっくりさよならポイントへ向ける
                 pKuroko->turnMvAngTwd(&leave_pos_,
                                       D_ANG(1), D_ANG(1), TURN_CLOSE_TO, false);
                 pKuroko->setMvAcce(10);
             }
             if (pProg->getFrameInProgress() % 16U == 0) {
                 pKuroko->turnFaceAngTwd(P_MYSHIP,
                                         D_ANG(1), 0, TURN_CLOSE_TO, true);
             }
             if (!pKuroko->isTurningMvAng()) {
                 pProg->changeNext();
             }
             break;
         }

         case PROG_MOVE04: {
             //さよなら～
             if (pProg->isJustChanged()) {
                 pKuroko->turnMvAngTwd(&leave_pos_,
                                       D_ANG(1), 0, TURN_CLOSE_TO, false);
                 pKuroko->setMvAcce(100+(G_RANK*200));
             }
             if (pProg->getFrameInProgress() % 16U == 0) {
                 //ちょくちょく自機を見つめる
                 pKuroko->turnFaceAngTwd(P_MYSHIP,
                                         D_ANG(1), 0, TURN_CLOSE_TO, true);
             }
             break;
         }

         default: {
             break;
         }
     }
    pKuroko->behave();
    pAFader_->behave();
}

void EnemyAppho::processJudgement() {
    if (isOutOfUniverse()) {
        sayonara();
    }
}

void EnemyAppho::onHit(GgafActor* prm_pOtherActor) {
    bool was_destroyed = UTIL::proceedEnemyHit(this, (GgafDxGeometricActor*)prm_pOtherActor);
    if (was_destroyed) {
        //破壊時
        getSeTx()->play3D(SE_EXPLOSION);
    } else {
        //非破壊時
    }
}

void EnemyAppho::onInactive() {
    sayonara();
}

EnemyAppho::~EnemyAppho() {
    GGAF_DELETE(pAFader_);
}
