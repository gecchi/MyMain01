#include "EnemyOebiusCore.h"

#include "jp/ggaf/dx/actor/supporter/AlphaFader.h"
#include "jp/ggaf/dx/actor/supporter/Rikisha.h"
#include "jp/ggaf/dx/actor/supporter/SeTransmitterForActor.h"
#include "jp/ggaf/lib/util/CollisionChecker.h"
#include "jp/gecchi/VioletVreath/GameGlobal.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/MyShipScene.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/ggaf/lib/util/spline/SplineLeader.h"
#include "jp/ggaf/lib/actor/DefaultGeometricActor.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Oebius/FormationOebius001.h"
#include "EnemyOebiusController.h"
#include "jp/ggaf/dx/util/Input.h"
#include "jp/gecchi/VioletVreath/actor/effect/Blink/EffectBlink.h"

using namespace GgafLib;
using namespace VioletVreath;

enum {
    PROG_INIT  ,
    PROG_ENTRY ,
    PROG_WAIT01 ,
    PROG_LEAVE ,
    PROG_BANPEI,
};
enum {
    SE_DAMAGED  ,
    SE_UNDAMAGED  ,
    SE_EXPLOSION,
    SE_FIRE,
};

EnemyOebiusCore::EnemyOebiusCore(const char* prm_name, EnemyOebiusController* prm_pController) :
        VvEnemyActor<DefaultMorphMeshActor>(prm_name, "OebiusCore_1", StatusReset(EnemyOebiusCore)) {
    _class_name = "EnemyOebiusCore";
    pController_ = prm_pController;
    GgafDx::SeTransmitterForActor* pSeTx = getSeTransmitter();
    pSeTx->set(SE_DAMAGED  , "WAVE_ENEMY_DAMAGED_001");
    pSeTx->set(SE_UNDAMAGED, "WAVE_ENEMY_UNDAMAGED_001");
    pSeTx->set(SE_EXPLOSION, "WAVE_EXPLOSION_002");
    pSeTx->set(SE_FIRE     , "WAVE_ENEMY_FIRE_LASER_001");


}

void EnemyOebiusCore::onCreateModel() {
//    pModel->setSpecular(5.0, 1.0);
}

void EnemyOebiusCore::initialize() {
    CollisionChecker* pChecker = getCollisionChecker();
    pChecker->createCollisionArea(1);
    pChecker->setColliAACube(0, 40000);
    GgafDx::Rikisha* const pRikisha = callRikisha();
    pRikisha->linkFaceAngByMvAng(true);
    pRikisha->forceMvVeloRange(PX_C(15));
}

void EnemyOebiusCore::onActive() {
    getStatus()->reset();
    getProgress()->reset(PROG_INIT);
}

void EnemyOebiusCore::processBehavior() {
    GgafDx::Rikisha* const pRikisha = callRikisha();
    GgafDx::AlphaFader* pAlphaFader = getAlphaFader();

    GgafCore::Progress* const pProg = getProgress();
    switch (pProg->get()) {
        case PROG_INIT: {
            setHitAble(false);
            setAlpha(0);
            pRikisha->setRollFaceAngVelo(D_ANG(3));
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

        case PROG_WAIT01: {
            if (pProg->hasJustChanged()) {
//                pRikisha->keepOnTurningFaceAngTwd(pMYSHIP, D_ANG(1), 0, TURN_CLOSE_TO, false);
                pRikisha->setRollPitchYawFaceAngVelo(D_ANG(0.027), D_ANG(0.031), D_ANG(0.071));
            }
            if (pProg->hasArrivedAt(10*60*60)) {
                pProg->changeNext();
            }
            break;
        }

        case PROG_LEAVE: {
            if (pProg->hasJustChanged()) {
                UTIL::activateLeaveEffectOf(this);
                pAlphaFader->transitionLinearUntil(0.0, 30);
            }
            if (pProg->hasArrivedAt(60)) {
                sayonara();
                pProg->changeNothing(); //おしまい！
            }
            break;
        }
        default :
            break;
    }

    pAlphaFader->behave();
    pRikisha->behave();
}

void EnemyOebiusCore::processJudgement() {
    if (isOutOfSpacetime()) {
        sayonara();
    }
}

void EnemyOebiusCore::onHit(const GgafCore::Actor* prm_pOtherActor) {
    bool was_destroyed = UTIL::performEnemyHit(this, (const GgafDx::GeometricActor*)prm_pOtherActor);
    if (was_destroyed) {
        //破壊された時(スタミナ <= 0)
        getSeTransmitter()->play3D(SE_EXPLOSION);
        sayonara();
    } else {
        //破壊されなかった時(スタミナ > 0)
    }
}

void EnemyOebiusCore::onInactive() {
    sayonara();
//    pController_->pOebiusCore_ = nullptr;
}

EnemyOebiusCore::~EnemyOebiusCore() {
}
