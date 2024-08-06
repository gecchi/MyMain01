#include "EnemyAntiope.h"

#include "jp/ggaf/dx/actor/supporter/SeTransmitterForActor.h"
#include "jp/ggaf/dx/actor/supporter/LocusVehicle.h"
#include "jp/ggaf/dx/actor/supporter/AlphaFader.h"
#include "jp/ggaf/dx/actor/supporter/CoordVehicle.h"
#include "jp/ggaf/lib/util/WorldCollisionChecker.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/MyShipScene.h"
#include "jp/gecchi/VioletVreath/actor/effect/Blink/EffectBlink.h"

using namespace GgafLib;
using namespace VioletVreath;

enum {
    SE_EXPLOSION,
};
enum {
    PHASE_INIT  ,
    PHASE_ENTRY ,
    PHASE_MOVE01,
    PHASE_LEAVE ,
    PHASE_RUSH,
    PHASE_BANPEI,
};


EnemyAntiope::EnemyAntiope(const char* prm_name, const char* prm_model, void* prm_pFuncStatusReset) :
        VvEnemyActor<DefaultMeshSetActor>(prm_name, prm_model, prm_pFuncStatusReset) {
    _class_name = "EnemyAntiope";
    GgafDx::SeTransmitterForActor* pSeXmtr = getSeXmtr();
    pSeXmtr->set(SE_EXPLOSION, "SE_EXPLOSION_001");
    pP_ = nullptr;
}

void EnemyAntiope::onCreateModel() {
//    GgafDx::Model* pModel = getModel();
//    pModel->setSpecular(5.0, 1.0);
}

void EnemyAntiope::initialize() {
    WorldCollisionChecker* pChecker = getWorldCollisionChecker();
    pChecker->addCollisionArea(1);
    pChecker->setColliAACube(0, 40000);
}

void EnemyAntiope::onActive() {
    getStatus()->reset();
    getPhase()->reset(PHASE_INIT);
}

void EnemyAntiope::processBehavior() {
    GgafDx::LocusVehicle* pLocusVehicle = getLocusVehicle();
    GgafDx::CoordVehicle* const pCoordVehicle = getCoordVehicle();
    GgafDx::AlphaFader* pAlphaFader = getAlphaFader();

    GgafCore::Phase* pPhase = getPhase();
    switch (pPhase->getCurrent()) {
         case PHASE_INIT: {
             setHitAble(false);
             setAlpha(0);
             pLocusVehicle->stop();
             pLocusVehicle->setRollFaceAngVelo(D_ANG(10));
             pCoordVehicle->setXYZZero();
             pPhase->changeNext();
             break;
         }
         case PHASE_ENTRY: {
             EffectBlink* pEffectEntry = nullptr;
             if (pPhase->hasJustChanged()) {
                 pEffectEntry = UTIL::activateEntryEffectOf(this);
             }
             static const frame frame_of_summons_begin = pEffectEntry->getFrameOfSummonsBegin();
             static const frame frame_of_entering = pEffectEntry->getSummoningFrames() + frame_of_summons_begin;
             if (pPhase->hasArrivedFrameAt(frame_of_summons_begin)) {
                 pAlphaFader->transitionLinearUntil(1.0, frame_of_entering);
             }
             if (pPhase->hasArrivedFrameAt(frame_of_entering)) {
                 setHitAble(true);
                 pPhase->changeNext();
             }
             break;
         }

         case PHASE_MOVE01: { //放物線のような動き
             if (pPhase->hasJustChanged()) {
                 pLocusVehicle->setMvVelo(PX_C(30));
                 pLocusVehicle->setMvAcce(-1000);
                 //平行移動速度の方向ベクトル mv_velo_twd_ はフォーメーションが設定
                 pCoordVehicle->setVeloXYZ(mv_velo_twd_.x, mv_velo_twd_.y, mv_velo_twd_.z);
             }

             if (pLocusVehicle->_velo_mv <= (-PX_C(30) + 1000)) {
                 if (pP_) {
                     pLocusVehicle->stop();
                     pCoordVehicle->setXYZZero();
                     pPhase->change(PHASE_LEAVE);
                 } else {
                     pCoordVehicle->setVeloXYZ(
                                  mv_velo_twd_.x + (pLocusVehicle->_vX * pLocusVehicle->_velo_mv),
                                  mv_velo_twd_.y + (pLocusVehicle->_vY * pLocusVehicle->_velo_mv),
                                  mv_velo_twd_.z + (pLocusVehicle->_vZ * pLocusVehicle->_velo_mv)
                                );
                     pLocusVehicle->stop();
                     pPhase->change(PHASE_RUSH);
                 }
             }
             break;
         }

         case PHASE_LEAVE: {
             if (pPhase->hasJustChanged()) {
                 UTIL::activateLeaveEffectOf(this);
                 pAlphaFader->transitionLinearUntil(0.0, 15);
             }
             if (pPhase->hasArrivedFrameAt(15)) {
                 setHitAble(false);
                 sayonara();
             }
             break;
         }

         case PHASE_RUSH: {
             //相方がいなくなった場合
             if (pPhase->hasJustChanged()) {
                 pCoordVehicle->execGravitationMvSequenceTwd(pMYSHIP, PX_C(30), 200, PX_C(50));
                 pLocusVehicle->keepOnTurningFaceAngTwd(pMYSHIP, D_ANG(2), 0, TURN_CLOSE_TO, false);
             }
             break;
         }

         default: {
             break;
         }
     }

//    _TRACE_(this<<":"<<getActiveFrame()<<" "<<_x<<","<<_y<<","<<_z<<"  ("<<_pLocusVehicle->_velo_mv<<") "<<_pLocusVehicle->_vX<<","<<_pLocusVehicle->_vY<<","<<_pLocusVehicle->_vZ<<"");
    pLocusVehicle->behave();
    pCoordVehicle->behave();
    pAlphaFader->behave();
}

void EnemyAntiope::processJudgement() {
    if (isOutOfSpacetime()) {
        pP_ = nullptr;
        sayonara();
    }
}

void EnemyAntiope::onHit(const GgafCore::Actor* prm_pOtherActor) {
    bool is_stamina_zero = performEnemyHit((const GgafDx::GeometricActor*)prm_pOtherActor);
    if (is_stamina_zero) {
        //破壊された時(スタミナ <= 0)
        getSeXmtr()->play3D(SE_EXPLOSION);
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
