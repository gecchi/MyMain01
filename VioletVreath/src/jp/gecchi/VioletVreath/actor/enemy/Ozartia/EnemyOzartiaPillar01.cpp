#include "EnemyOzartiaPillar01.h"
#include "jp/ggaf/dx/actor/supporter/LocoVehicle.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/ggaf/lib/util/WorldCollisionChecker.h"
#include "jp/ggaf/dx/actor/supporter/AlphaFader.h"
#include "jp/gecchi/VioletVreath/actor/effect/Blink/EffectBlink.h"

using namespace GgafLib;
using namespace VioletVreath;

enum {
    PHASE_INIT   ,
    PHASE_ENTRY  ,
    PHASE_MOVE01 ,
    PHASE_LEAVE  ,
    PHASE_BANPEI,
};

EnemyOzartiaPillar01::EnemyOzartiaPillar01(const char* prm_name) :
        VvEnemyActor<DefaultMeshSetActor>(prm_name, "myvic", StatusReset(EnemyOzartiaPillar01)) {
    _class_name = "EnemyOzartiaPillar01";
}

void EnemyOzartiaPillar01::initialize() {
    WorldCollisionChecker* pChecker = getWorldCollisionChecker();
    pChecker->addCollisionArea(1);
    pChecker->setColliAACube(0, PX_C(60));
    setHitAble(true);
    getPhase()->reset(PHASE_INIT);
}

void EnemyOzartiaPillar01::onActive() {
    getStatus()->reset();
}

void EnemyOzartiaPillar01::processBehavior() {
    //本体移動系の処理 ここから --->
    GgafDx::LocoVehicle* pLocoVehicle = getLocoVehicle();
    GgafDx::AlphaFader* pAlphaFader = getAlphaFader();
    GgafCore::Phase* pPhase = getPhase();
    switch (pPhase->getCurrent()) {
        case PHASE_INIT: {
            setHitAble(false);
            setAlpha(0);
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
                pPhase->change(PHASE_MOVE01);
            }
            break;
        }
        case PHASE_MOVE01: {
            if (pPhase->hasJustChanged()) {
            }
            if (pPhase->hasArrivedFrameAt(60*10)) {
                pPhase->change(PHASE_LEAVE);
            }
            break;
        }
        case PHASE_LEAVE: {
             if (pPhase->hasJustChanged()) {
                 UTIL::activateLeaveEffectOf(this);
                 pAlphaFader->transitionLinearUntil(0.0, 15);
             }
             if (pPhase->hasArrivedFrameAt(60)) {
                 sayonara();
                 pPhase->changeNothing(); //おしまい！
             }
             break;
         }
        default :
            break;
    }
    pAlphaFader->behave();
    pLocoVehicle->behave();
}

void EnemyOzartiaPillar01::processJudgement() {
    if (isOutOfSpacetime()) {
        sayonara();
    }
}

void EnemyOzartiaPillar01::onHit(const GgafCore::Actor* prm_pOtherActor) {
    bool was_destroyed = performEnemyHit((const GgafDx::GeometricActor*)prm_pOtherActor);
    if (was_destroyed) {
        //破壊された時(スタミナ <= 0)
        sayonara();
    } else {
        //破壊されなかった時(スタミナ > 0)
    }
}

void EnemyOzartiaPillar01::onInactive() {
    sayonara();
}

EnemyOzartiaPillar01::~EnemyOzartiaPillar01() {
}
