#include "EnemyAntiope.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxSeTransmitterForActor.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxAlphaFader.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxAxesMover.h"
#include "jp/ggaf/lib/util/CollisionChecker.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/MyShipScene.h"
#include "jp/gecchi/VioletVreath/actor/effect/Blink/EffectBlink.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

EnemyAntiope::EnemyAntiope(const char* prm_name, const char* prm_model, GgafStatus* prm_pStat) :
        DefaultMeshSetActor(prm_name, prm_model, prm_pStat) {
    _class_name = "EnemyAntiope";
    pAFader_ = NEW GgafDxAlphaFader(this);
    GgafDxSeTransmitterForActor* pSe = getSeTransmitter();
    pSe->set(SE_EXPLOSION, "WAVE_EXPLOSION_001");
    useProgress(PROG_BANPEI);
    pP_ = nullptr;
}

void EnemyAntiope::onCreateModel() {
//    GgafDxModel* pModel = getModel();
//    pModel->setSpecular(5.0, 1.0);
}

void EnemyAntiope::initialize() {
    CollisionChecker* pChecker = getCollisionChecker();
    pChecker->createCollisionArea(1);
    pChecker->setColliAABox_Cube(0, 40000);
}

void EnemyAntiope::onActive() {
    getStatus()->reset();
    getProgress()->reset(PROG_INIT);
}

void EnemyAntiope::processBehavior() {
    GgafDxKuroko* const pKuroko = getKuroko();
    GgafDxAxesMover* const pAxesMover = getAxesMover();
    GgafProgress* const pProg = getProgress();
    switch (pProg->get()) {
         case PROG_INIT: {
             setHitAble(false);
             setAlpha(0);
             pKuroko->stopMv();
             pKuroko->setRollFaceAngVelo(D_ANG(10));
             pAxesMover->setZeroVxyzMvVelo();
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
                 pAFader_->transitionLinearUntil(1.0, frame_of_entering);
             }
             if (pProg->hasArrivedAt(frame_of_entering)) {
                 setHitAble(true);
                 pProg->changeNext();
             }
             break;
         }

         case PROG_MOVE01: { //放物線のような動き
             if (pProg->hasJustChanged()) {
                 pKuroko->setMvVelo(PX_C(30));
                 pKuroko->setMvAcce(-1000);
                 //平行移動速度の方向ベクトル mv_velo_twd_ はフォーメーションが設定
                 pAxesMover->setVxyzMvVelo(mv_velo_twd_.x, mv_velo_twd_.y, mv_velo_twd_.z);
             }

             if (pKuroko->_velo_mv <= (-PX_C(30) + 1000)) {
                 if (pP_) {
                     pKuroko->stopMv();
                     pAxesMover->setZeroVxyzMvVelo();
                     pProg->change(PROG_LEAVE);
                 } else {
                     pAxesMover->setVxyzMvVelo(
                                  mv_velo_twd_.x + (pKuroko->_vX * pKuroko->_velo_mv),
                                  mv_velo_twd_.y + (pKuroko->_vY * pKuroko->_velo_mv),
                                  mv_velo_twd_.z + (pKuroko->_vZ * pKuroko->_velo_mv)
                                );
                     pKuroko->stopMv();
                     pProg->change(PROG_RUSH);
                 }
             }
             break;
         }

         case PROG_LEAVE: {
             if (pProg->hasJustChanged()) {
                 UTIL::activateLeaveEffectOf(this);
                 pAFader_->transitionLinearUntil(0.0, 15);
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
                 pAxesMover->execGravitationMvSequenceTwd(P_MYSHIP, PX_C(30), 200, PX_C(50));
                 pKuroko->keepOnTurningFaceAngTwd(P_MYSHIP, D_ANG(2), 0, TURN_CLOSE_TO, false);
             }
             break;
         }

         default: {
             break;
         }
     }

//    _TRACE_(this<<":"<<getActiveFrame()<<" "<<_x<<","<<_y<<","<<_z<<"  ("<<_pKuroko->_velo_mv<<") "<<_pKuroko->_vX<<","<<_pKuroko->_vY<<","<<_pKuroko->_vZ<<"");
    pKuroko->behave();
    pAxesMover->behave();
    pAFader_->behave();
}

void EnemyAntiope::processJudgement() {
    if (isOutOfSpacetime()) {
        pP_ = nullptr;
        sayonara();
    }
}

void EnemyAntiope::onHit(const GgafActor* prm_pOtherActor) {
    bool was_destroyed = UTIL::performEnemyHit(this, (const GgafDxGeometricActor*)prm_pOtherActor);
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
    GGAF_DELETE(pAFader_);
}
