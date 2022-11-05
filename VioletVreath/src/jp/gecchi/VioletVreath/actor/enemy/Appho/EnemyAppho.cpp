#include "EnemyAppho.h"

#include "jp/ggaf/dx/actor/supporter/AlphaFader.h"
#include "jp/ggaf/dx/actor/supporter/VecVehicle.h"
#include "jp/ggaf/dx/actor/supporter/SeTransmitterForActor.h"
#include "jp/ggaf/lib/util/WorldCollisionChecker.h"
#include "jp/gecchi/VioletVreath/GameGlobal.h"
#include "jp/gecchi/VioletVreath/Caretaker.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/MyShipScene.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/ggaf/dx/actor/supporter/VecVehicleMvAssistant.h"
#include "jp/gecchi/VioletVreath/actor/effect/Blink/EffectBlink.h"

using namespace GgafLib;
using namespace VioletVreath;

enum {
    SE_EXPLOSION ,
};
enum {
    PHASE_INIT   ,
    PHASE_ENTRY  ,
    PHASE_MOVE01 ,
    PHASE_MOVE02 ,
    PHASE_MOVE03 ,
    PHASE_MOVE04 ,
    PHASE_BANPEI ,
};

EnemyAppho::EnemyAppho(const char* prm_name) :
        VvEnemyActor<DefaultMeshSetActor>(prm_name, "Appho", StatusReset(EnemyAppho)) {
    _class_name = "EnemyAppho";
    GgafDx::SeTransmitterForActor* pSeTx = getSeTransmitter();
    pSeTx->set(SE_EXPLOSION, "SE_EXPLOSION_001");
}

void EnemyAppho::onCreateModel() {
//    pModel->setSpecular(5.0, 1.0);
}

void EnemyAppho::initialize() {
    setScale(100);
    WorldCollisionChecker* pChecker = getWorldCollisionChecker();
    pChecker->createCollisionArea(1);
    pChecker->setColliAACube(0, 40000);
}

void EnemyAppho::onActive() {
    getStatus()->reset();
    getPhase()->reset(PHASE_INIT);
}

void EnemyAppho::processBehavior() {
    GgafDx::VecVehicle* pVecVehicle = getVecVehicle();
    GgafCore::Phase* pPhase = getPhase();

    switch (pPhase->getCurrent()) {

         case PHASE_INIT: {
             setHitAble(false);
             setPositionAt(&entry_pos_);
             setFaceAngTwd(stagnating_pos_.x, stagnating_pos_.y, stagnating_pos_.z);
             setAlpha(0);
             pVecVehicle->linkFaceAngByMvAng(false);
             pVecVehicle->setMvVelo(0);
             pVecVehicle->setMvAngTwd(&stagnating_pos_);
             pVecVehicle->setRollFaceAngVelo(D_ANG(3));
             pPhase->changeNext();
             break;
         }
         case PHASE_ENTRY: {
             EffectBlink* pEffectEntry = nullptr;
             if (pPhase->hasJustChanged()) {
                 pEffectEntry = UTIL::activateEntryEffectOf(this);
                 pVecVehicle->setRollFaceAngVelo(D_ANG(3));
             }
             static const frame frame_of_summons_begin = pEffectEntry->getFrameOfSummonsBegin();
             static const frame frame_of_entering = pEffectEntry->getSummoningFrames() + frame_of_summons_begin;
             if (pPhase->hasArrivedFrameAt(frame_of_summons_begin)) {
                 getAlphaFader()->transitionLinearUntil(1.0, frame_of_entering);
             }
             if (pPhase->hasArrivedFrameAt(frame_of_entering)) {
                 setHitAble(true);
                 pPhase->changeNext();
             }
             break;
         }

         case PHASE_MOVE01: {
             if (pPhase->hasJustChanged()) {
                 //滞留ポイントへGO!
                 velo mv_velo = RF_EnemyAppho_MvVelo(G_RANK);
                 coord d = UTIL::getDistance(this, &stagnating_pos_);
                 pVecVehicle->asstMv()->slideByVd(mv_velo, d,
                                               0.2, 0.8, 200, true);
             }
             //滞留ポイントまで移動中
             if (pPhase->getFrame() % 32U == 0) {
                 //ちょくちょく自機を見つめる
                 pVecVehicle->turnFaceAngTwd(pMYSHIP, D_ANG(0.5), 0,
                                         TURN_CLOSE_TO, true);
             }
             if (pVecVehicle->asstMv()->hasJustFinishedSliding()) {
                 pPhase->changeNext();
             }
             //_TRACE_("PHASE_MOVE01:"<<_x<<","<<_y<<","<<_z<<","<<_pVecVehicle->_velo_mv<<","<<_pVecVehicle->_acc_mv);
             break;
         }

         case PHASE_MOVE02: {
             if (pPhase->hasJustChanged()) {
                 //滞留ポイント到着、自機方向へジワリ移動させる
                 pVecVehicle->turnMvAngTwd(pMYSHIP,
                                       100, 0, TURN_CLOSE_TO, false);
                 //ゆっくり自機の方へ向かせる
                 pVecVehicle->turnFaceAngTwd(pMYSHIP,
                                         D_ANG(1), 0, TURN_CLOSE_TO, true);
             }
             //滞留中
             if (pPhase->getFrame() % 16U == 0) {
                 //ちょくちょく自機を見つめる
                 pVecVehicle->turnFaceAngTwd(pMYSHIP,
                                         D_ANG(1), 0, TURN_CLOSE_TO, true);
             }

             if (pPhase->hasArrivedFrameAt(180)) {
                 //自機の方に向いたら敵弾発射！
                 int shot_num   = RF_EnemyAppho_ShotWay(G_RANK);    //弾数、ランク変動
                 velo shot_velo = RF_EnemyAppho_ShotMvVelo(G_RANK); //弾速、ランク変動
                 for (int i = 0; i < shot_num; i++) {
                     GgafDx::FigureActor* pShot = UTIL::activateAttackShotOf(this);
                     if (pShot) {
                         pShot->activateDelay(1+(i*10)); //ばらつかせ。activate タイミング上書き！
                         GgafDx::VecVehicle* pShot_pVecVehicle = pShot->getVecVehicle();
                         pShot_pVecVehicle->setRzRyMvAng(_rz, _ry);
                         pShot_pVecVehicle->setMvVelo(shot_velo);
                         pShot_pVecVehicle->setMvAcce(100);
                     }
                 }
             }
             if (pPhase->hasArrivedFrameAt(240)) {
                 pPhase->changeNext();
             }
             break;
         }

         case PHASE_MOVE03: {
             //さよなら準備
             if (pPhase->hasJustChanged()) {
                 //ゆっくりさよならポイントへ向ける
                 pVecVehicle->turnMvAngTwd(&leave_pos_,
                                       D_ANG(1), D_ANG(1), TURN_CLOSE_TO, false);
                 pVecVehicle->setMvAcce(10);
             }
             if (pPhase->getFrame() % 16U == 0) {
                 pVecVehicle->turnFaceAngTwd(pMYSHIP,
                                         D_ANG(1), 0, TURN_CLOSE_TO, true);
             }
             if (!pVecVehicle->isTurningMvAng()) {
                 pPhase->changeNext();
             }
             break;
         }

         case PHASE_MOVE04: {
             //さよなら～
             if (pPhase->hasJustChanged()) {
                 pVecVehicle->turnMvAngTwd(&leave_pos_,
                                       D_ANG(1), 0, TURN_CLOSE_TO, false);
                 pVecVehicle->setMvAcce(100+(G_RANK*200));
             }
             if (pPhase->getFrame() % 16U == 0) {
                 //ちょくちょく自機を見つめる
                 pVecVehicle->turnFaceAngTwd(pMYSHIP,
                                         D_ANG(1), 0, TURN_CLOSE_TO, true);
             }
             break;
         }

         default: {
             break;
         }
     }
    pVecVehicle->behave();
    getAlphaFader()->behave();
}

void EnemyAppho::processJudgement() {
    if (isOutOfSpacetime()) {
        sayonara();
    }
}

void EnemyAppho::onHit(const GgafCore::Actor* prm_pOtherActor) {
    bool was_destroyed = UTIL::performEnemyHit(this, (const GgafDx::GeometricActor*)prm_pOtherActor);
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
