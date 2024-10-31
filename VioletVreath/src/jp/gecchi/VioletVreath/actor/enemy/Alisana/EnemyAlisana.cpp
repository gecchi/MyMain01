#include "EnemyAlisana.h"

#include "jp/ggaf/dx/actor/supporter/AlphaFader.h"
#include "jp/ggaf/dx/actor/supporter/LocusVehicle.h"
#include "jp/ggaf/dx/actor/supporter/SeTransmitterForActor.h"
#include "jp/ggaf/dx/model/Model.h"
#include "jp/ggaf/lib/util/WorldCollisionChecker.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"

#include "jp/gecchi/VioletVreath/actor/effect/Blink/EffectBlink.h"

using namespace GgafLib;
using namespace VioletVreath;

enum {
    PHASE_INIT ,
    PHASE_ENTRY,
    PHASE_HATCH_OPEN,
    PHASE_HATCH_OPEN_DONE,
    PHASE_HATCH_CLOSE,
    PHASE_LEAVE,
    PHASE_BANPEI,
};
enum {
    MPH_HATCH_CLOSE,
    MPH_HATCH_OPEN,
};

EnemyAlisana::EnemyAlisana(const char* prm_name) :
        VvEnemyActor<DefaultMorphMeshActor>(prm_name, "Alisana", StatusReset(EnemyAlisana)) {
    _class_name = "EnemyAlisana";
    frame_of_morph_interval_ = 120;
}

void EnemyAlisana::onCreateModel() {
    GgafDx::Model* pModel = getModel();
    pModel->setSpecular(5.0, 1.0);
}

void EnemyAlisana::initialize() {
    WorldCollisionChecker* pChecker = getWorldCollisionChecker();
    pChecker->addCollisionArea(1);
    pChecker->setColliAACube(0, 200000);

    setHitAble(true);
    setScaleR(1.0);
}

void EnemyAlisana::onActive() {
    getStatus()->reset();
    getPhase()->reset(PHASE_INIT);
}

void EnemyAlisana::processBehavior() {
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
                pEffectEntry = (EffectBlink*)UTIL::activateCommonEffectOf(this, STAT_EntryEffectKind);
            }
            static const frame frame_of_summons_begin = pEffectEntry->getFrameOfSummonsBegin();
            static const frame frame_of_entering = pEffectEntry->getSummoningFrames() + frame_of_summons_begin;
            if (pPhase->hasArrivedFrameAt(frame_of_summons_begin)) {
                pAlphaFader->transitionLinearUntil(0.999, frame_of_entering);
            }
            if (pPhase->hasArrivedFrameAt(frame_of_entering)) {
                setHitAble(true);
                pPhase->changeNext();
            }
            break;
        }
        case PHASE_HATCH_OPEN: {
            if (pPhase->hasJustChanged()) {
                getMorpher()->transitionLinearUntil(MPH_HATCH_OPEN,
                                           1.0, frame_of_morph_interval_);
            }
            if (!getMorpher()->isTransitioning()) {
                pPhase->changeNext();
            }
            break;
        }

        case PHASE_HATCH_OPEN_DONE: {
            if (pPhase->hasJustChanged()) {
            }
            //おしまい。
            break;
        }

        //-----------------------------------------------------------------------
        case PHASE_HATCH_CLOSE: {
            if (pPhase->hasJustChanged()) {
                getMorpher()->transitionLinearUntil(MPH_HATCH_OPEN,
                                           0.0, frame_of_morph_interval_);
            }
            if (!getMorpher()->isTransitioning()) {
                pPhase->changeNext();
            }
            break;
        }
        case PHASE_LEAVE: {
            if (pPhase->hasJustChanged()) {
                setHitAble(false);
                UTIL::activateCommonEffectOf(this, STAT_LeaveEffectKind);
                pAlphaFader->transitionLinearUntil(0.0, 30);
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
    getMorpher()->behave();
    getLocusVehicle()->behave();
}

void EnemyAlisana::processJudgement() {
}

void EnemyAlisana::onHit(const GgafCore::Checker* prm_pOtherChecker, const GgafCore::Actor* prm_pOtherActor) {
    bool is_stamina_zero = performEnemyHit((const GgafDx::GeometricActor*)prm_pOtherActor);
    if (is_stamina_zero) {
        //破壊された時(スタミナ <= 0)
        sayonara();
    } else {
        //破壊されなかった時(スタミナ > 0)
    }
}

void EnemyAlisana::onInactive() {
    sayonara();
}

void EnemyAlisana::acitve_open(frame prm_delay) {
    activateDelay(prm_delay);
}

bool EnemyAlisana::isOpenDone() {
    if (getPhase()->getCurrent() == PHASE_HATCH_OPEN_DONE) {
        return true;
    } else {
        return false;
    }
}

void EnemyAlisana::close_sayonara() {
    getMorpher()->stop();
    getPhase()->change(PHASE_HATCH_CLOSE);
}

EnemyAlisana::~EnemyAlisana() {
}

