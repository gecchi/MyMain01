#include "EnemyAntiope.h"

#include "jp/ggaf/dx/actor/supporter/SeTransmitterForActor.h"
#include "jp/ggaf/dx/actor/supporter/VecVehicle.h"
#include "jp/ggaf/dx/actor/supporter/AlphaFader.h"
#include "jp/ggaf/dx/actor/supporter/GeoVehicle.h"
#include "jp/ggaf/lib/util/CollisionChecker.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/MyShipScene.h"
#include "jp/gecchi/VioletVreath/actor/effect/Blink/EffectBlink.h"

using namespace GgafLib;
using namespace VioletVreath;

enum {
    SE_EXPLOSION,
};
enum {
    PROG_INIT  ,
    PROG_ENTRY ,
    PROG_MOVE01,
    PROG_LEAVE ,
    PROG_RUSH,
    PROG_BANPEI,
};


EnemyAntiope::EnemyAntiope(const char* prm_name, const char* prm_model, void* prm_pFuncStatusReset) :
        VvEnemyActor<DefaultMeshSetActor>(prm_name, prm_model, prm_pFuncStatusReset) {
    _class_name = "EnemyAntiope";
    GgafDx::SeTransmitterForActor* pSeTx = getSeTransmitter();
    pSeTx->set(SE_EXPLOSION, "SE_EXPLOSION_001");
    pP_ = nullptr;
}

void EnemyAntiope::onCreateModel() {
//    GgafDx::Model* pModel = getModel();
//    pModel->setSpecular(5.0, 1.0);
}

void EnemyAntiope::initialize() {
    CollisionChecker* pChecker = getCollisionChecker();
    pChecker->createCollisionArea(1);
    pChecker->setColliAACube(0, 40000);
}

void EnemyAntiope::onActive() {
    getStatus()->reset();
    getProgress()->reset(PROG_INIT);
}

void EnemyAntiope::processBehavior() {
    GgafDx::VecVehicle* const pVecVehicle = getVecVehicle();
    GgafDx::GeoVehicle* const pGeoVehicle = getGeoVehicle();
    GgafDx::AlphaFader* pAlphaFader = getAlphaFader();

    GgafCore::Progress* const pProg = getProgress();
    switch (pProg->get()) {
         case PROG_INIT: {
             setHitAble(false);
             setAlpha(0);
             pVecVehicle->stop();
             pVecVehicle->setRollFaceAngVelo(D_ANG(10));
             pGeoVehicle->setXYZZero();
             pProg->changeNext();
             break;
         }
         case PROG_ENTRY: {
             EffectBlink* pEffectEntry = nullptr;
             if (pProg->hasJustChanged()) {
                 pEffectEntry = UTIL::activateEntryEffectOf(this);
             }
             static const frame frame_of_summons_begin = pEffectEntry->getFrameOfSummonsBegin();
             static const frame frame_of_entering = pEffectEntry->getSummoningFrames() + frame_of_summons_begin;
             if (pProg->hasArrivedAt(frame_of_summons_begin)) {
                 pAlphaFader->transitionLinearUntil(1.0, frame_of_entering);
             }
             if (pProg->hasArrivedAt(frame_of_entering)) {
                 setHitAble(true);
                 pProg->changeNext();
             }
             break;
         }

         case PROG_MOVE01: { //放物線のような動き
             if (pProg->hasJustChanged()) {
                 pVecVehicle->setMvVelo(PX_C(30));
                 pVecVehicle->setMvAcce(-1000);
                 //平行移動速度の方向ベクトル mv_velo_twd_ はフォーメーションが設定
                 pGeoVehicle->setVeloXYZ(mv_velo_twd_.x, mv_velo_twd_.y, mv_velo_twd_.z);
             }

             if (pVecVehicle->_velo_mv <= (-PX_C(30) + 1000)) {
                 if (pP_) {
                     pVecVehicle->stop();
                     pGeoVehicle->setXYZZero();
                     pProg->change(PROG_LEAVE);
                 } else {
                     pGeoVehicle->setVeloXYZ(
                                  mv_velo_twd_.x + (pVecVehicle->_vX * pVecVehicle->_velo_mv),
                                  mv_velo_twd_.y + (pVecVehicle->_vY * pVecVehicle->_velo_mv),
                                  mv_velo_twd_.z + (pVecVehicle->_vZ * pVecVehicle->_velo_mv)
                                );
                     pVecVehicle->stop();
                     pProg->change(PROG_RUSH);
                 }
             }
             break;
         }

         case PROG_LEAVE: {
             if (pProg->hasJustChanged()) {
                 UTIL::activateLeaveEffectOf(this);
                 pAlphaFader->transitionLinearUntil(0.0, 15);
             }
             if (pProg->hasArrivedAt(15)) {
                 setHitAble(false);
                 sayonara();
             }
             break;
         }

         case PROG_RUSH: {
             //相方がいなくなった場合
             if (pProg->hasJustChanged()) {
                 pGeoVehicle->execGravitationMvSequenceTwd(pMYSHIP, PX_C(30), 200, PX_C(50));
                 pVecVehicle->keepOnTurningFaceAngTwd(pMYSHIP, D_ANG(2), 0, TURN_CLOSE_TO, false);
             }
             break;
         }

         default: {
             break;
         }
     }

//    _TRACE_(this<<":"<<getActiveFrame()<<" "<<_x<<","<<_y<<","<<_z<<"  ("<<_pVecVehicle->_velo_mv<<") "<<_pVecVehicle->_vX<<","<<_pVecVehicle->_vY<<","<<_pVecVehicle->_vZ<<"");
    pVecVehicle->behave();
    pGeoVehicle->behave();
    pAlphaFader->behave();
}

void EnemyAntiope::processJudgement() {
    if (isOutOfSpacetime()) {
        pP_ = nullptr;
        sayonara();
    }
}

void EnemyAntiope::onHit(const GgafCore::Actor* prm_pOtherActor) {
    bool was_destroyed = UTIL::performEnemyHit(this, (const GgafDx::GeometricActor*)prm_pOtherActor);
    if (was_destroyed) {
        //破壊された時(スタミナ <= 0)
        getSeTransmitter()->play3D(SE_EXPLOSION);
        if (pP_) {
            if (pP_->pP_) {
                pP_->pP_ = nullptr;
            }
        }
        pP_ = nullptr;
        sayonara();
    } else {
        //破壊されなかった時(スタミナ > 0)
    }
}

void EnemyAntiope::onInactive() {
    pP_ = nullptr;
    sayonara();
}

EnemyAntiope::~EnemyAntiope() {
}
