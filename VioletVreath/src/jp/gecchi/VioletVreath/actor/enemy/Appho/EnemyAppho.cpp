#include "EnemyAppho.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxAlphaFader.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxSeTransmitterForActor.h"
#include "jp/ggaf/lib/util/CollisionChecker.h"
#include "jp/gecchi/VioletVreath/GameGlobal.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/MyShipScene.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoMvAssistant.h"
#include "jp/gecchi/VioletVreath/actor/effect/Blink/EffectBlink.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

enum {
    SE_EXPLOSION ,
};
enum {
    PROG_INIT   ,
    PROG_ENTRY  ,
    PROG_MOVE01 ,
    PROG_MOVE02 ,
    PROG_MOVE03 ,
    PROG_MOVE04 ,
    PROG_BANPEI ,
};

EnemyAppho::EnemyAppho(const char* prm_name) :
        DefaultMeshSetActor(prm_name, "Appho", STATUS(EnemyAppho)) {
    _class_name = "EnemyAppho";
    GgafDxSeTransmitterForActor* pSeTx = getSeTransmitter();
    pSeTx->set(SE_EXPLOSION, "WAVE_EXPLOSION_001");
    useProgress(PROG_BANPEI);
}

void EnemyAppho::onCreateModel() {
//    pModel->setSpecular(5.0, 1.0);
}

void EnemyAppho::initialize() {
    setScale(100);
    CollisionChecker* pChecker = getCollisionChecker();
    pChecker->createCollisionArea(1);
    pChecker->setColliAACube(0, 40000);
}

void EnemyAppho::onActive() {
    getStatus()->reset();
    getProgress()->reset(PROG_INIT);
}

void EnemyAppho::processBehavior() {
    GgafDxKuroko* const pKuroko = getKuroko();
    GgafProgress* const pProg = getProgress();

    switch (pProg->get()) {

         case PROG_INIT: {
             setHitAble(false);
             setPositionAt(&entry_pos_);
             setFaceAngTwd(stagnating_pos_.x, stagnating_pos_.y, stagnating_pos_.z);
             setAlpha(0);
             pKuroko->linkFaceAngByMvAng(false);
             pKuroko->setMvVelo(0);
             pKuroko->setMvAngTwd(&stagnating_pos_);
             pKuroko->setRollFaceAngVelo(D_ANG(3));
             pProg->changeNext();
             break;
         }
         case PROG_ENTRY: {
             EffectBlink* pEffectEntry = nullptr;
             if (pProg->hasJustChanged()) {
                 pEffectEntry = UTIL::activateEntryEffectOf(this);
                 pKuroko->setRollFaceAngVelo(D_ANG(3));
             }
             static const frame frame_of_summons_begin = pEffectEntry->getFrameOfSummonsBegin();
             static const frame frame_of_entering = pEffectEntry->getSummoningFrames() + frame_of_summons_begin;
             if (pProg->hasArrivedAt(frame_of_summons_begin)) {
                 getAlphaFader()->transitionLinearUntil(1.0, frame_of_entering);
             }
             if (pProg->hasArrivedAt(frame_of_entering)) {
                 setHitAble(true);
                 pProg->changeNext();
             }
             break;
         }

         case PROG_MOVE01: {
             if (pProg->hasJustChanged()) {
                 //滞留ポイントへGO!
                 velo mv_velo = RF_EnemyAppho_MvVelo(G_RANK);
                 coord d = UTIL::getDistance(this, &stagnating_pos_);
                 pKuroko->asstMv()->slideByVd(mv_velo, d,
                                               0.2, 0.8, 200, true);
             }
             //滞留ポイントまで移動中
             if (pProg->getFrame() % 32U == 0) {
                 //ちょくちょく自機を見つめる
                 pKuroko->turnFaceAngTwd(pMYSHIP, D_ANG(0.5), 0,
                                         TURN_CLOSE_TO, true);
             }
             if (pKuroko->asstMv()->hasJustFinishedSliding()) {
                 pProg->changeNext();
             }
             //_TRACE_("PROG_MOVE01:"<<_x<<","<<_y<<","<<_z<<","<<_pKuroko->_velo_mv<<","<<_pKuroko->_acc_mv);
             break;
         }

         case PROG_MOVE02: {
             if (pProg->hasJustChanged()) {
                 //滞留ポイント到着、自機方向へジワリ移動させる
                 pKuroko->turnMvAngTwd(pMYSHIP,
                                       100, 0, TURN_CLOSE_TO, false);
                 //ゆっくり自機の方へ向かせる
                 pKuroko->turnFaceAngTwd(pMYSHIP,
                                         D_ANG(1), 0, TURN_CLOSE_TO, true);
             }
             //滞留中
             if (pProg->getFrame() % 16U == 0) {
                 //ちょくちょく自機を見つめる
                 pKuroko->turnFaceAngTwd(pMYSHIP,
                                         D_ANG(1), 0, TURN_CLOSE_TO, true);
             }

             if (pProg->hasArrivedAt(180)) {
                 //自機の方に向いたら敵弾発射！
                 int shot_num   = RF_EnemyAppho_ShotWay(G_RANK);    //弾数、ランク変動
                 velo shot_velo = RF_EnemyAppho_ShotMvVelo(G_RANK); //弾速、ランク変動
                 for (int i = 0; i < shot_num; i++) {
                     GgafDxFigureActor* pShot = UTIL::activateAttackShotOf(this);
                     if (pShot) {
                         pShot->activateDelay(1+(i*10)); //ばらつかせ。activate タイミング上書き！
                         GgafDxKuroko* pShot_pKuroko = pShot->getKuroko();
                         pShot_pKuroko->setRzRyMvAng(_rz, _ry);
                         pShot_pKuroko->setMvVelo(shot_velo);
                         pShot_pKuroko->setMvAcce(100);
                     }
                 }
             }
             if (pProg->hasArrivedAt(240)) {
                 pProg->changeNext();
             }
             break;
         }

         case PROG_MOVE03: {
             //さよなら準備
             if (pProg->hasJustChanged()) {
                 //ゆっくりさよならポイントへ向ける
                 pKuroko->turnMvAngTwd(&leave_pos_,
                                       D_ANG(1), D_ANG(1), TURN_CLOSE_TO, false);
                 pKuroko->setMvAcce(10);
             }
             if (pProg->getFrame() % 16U == 0) {
                 pKuroko->turnFaceAngTwd(pMYSHIP,
                                         D_ANG(1), 0, TURN_CLOSE_TO, true);
             }
             if (!pKuroko->isTurningMvAng()) {
                 pProg->changeNext();
             }
             break;
         }

         case PROG_MOVE04: {
             //さよなら～
             if (pProg->hasJustChanged()) {
                 pKuroko->turnMvAngTwd(&leave_pos_,
                                       D_ANG(1), 0, TURN_CLOSE_TO, false);
                 pKuroko->setMvAcce(100+(G_RANK*200));
             }
             if (pProg->getFrame() % 16U == 0) {
                 //ちょくちょく自機を見つめる
                 pKuroko->turnFaceAngTwd(pMYSHIP,
                                         D_ANG(1), 0, TURN_CLOSE_TO, true);
             }
             break;
         }

         default: {
             break;
         }
     }
    pKuroko->behave();
    getAlphaFader()->behave();
}

void EnemyAppho::processJudgement() {
    if (isOutOfSpacetime()) {
        sayonara();
    }
}

void EnemyAppho::onHit(const GgafActor* prm_pOtherActor) {
    bool was_destroyed = UTIL::performEnemyHit(this, (const GgafDxGeometricActor*)prm_pOtherActor);
    if (was_destroyed) {
        //破壊された時(スタミナ <= 0)
        getSeTransmitter()->play3D(SE_EXPLOSION);
        sayonara();
    } else {
        //破壊されなかった時(スタミナ > 0)
    }
}

void EnemyAppho::onInactive() {
    sayonara();
}

EnemyAppho::~EnemyAppho() {
}
