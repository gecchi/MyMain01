#include "EffectBlink.h"

#include "jp/ggaf/dx/actor/supporter/LocoVehicle.h"
#include "jp/ggaf/dx/actor/supporter/Scaler.h"
#include "jp/gecchi/VioletVreath/Config.h"


using namespace GgafLib;
using namespace VioletVreath;

enum {
    PHASE_INIT ,
    PHASE_IN   ,
    PHASE_STAY ,
    PHASE_OUT  ,
    PHASE_BANPEI,
};

EffectBlink::EffectBlink(const char* prm_name, const char* prm_model) :
        DefaultMassMeshActor(prm_name, prm_model) {
    _class_name = "EffectBlink";
    setHitAble(false);
    pTarget_ = nullptr;
    scale_in_frames_ = 1;
    duration_frames_ = 1;
    scale_out_frames_ = 1;
    sayonara_end_ = true;
    getScaler()->setRange(0, R_SC(1.0));
}

void EffectBlink::onActive() {
    setScale(getScaler()->getBottom());
    getPhase()->reset(PHASE_INIT);
}

void EffectBlink::processBehavior() {
    if (pTarget_) {
        if (pTarget_->hasJustChangedToInactive()) {
            pTarget_ = nullptr;
        } else {
            setPositionAt(pTarget_);
        }
    }
    if (getActiveFrame() >= CONFIG::END_DELAY_FRAME) {
        pTarget_ = nullptr;
        if (sayonara_end_) {
            sayonara();
        }
    }

    GgafDx::Scaler* const pScaler = getScaler();
    GgafCore::Phase* pPhase = getPhase();
    switch (pPhase->getCurrent()) {
        case PHASE_INIT: {
            if (scale_in_frames_ > 0) {
                pScaler->transitionLinearToTop(scale_in_frames_);
                pPhase->changeNext();
            } else {
                setScale(getScaler()->getTop());
                pPhase->change(PHASE_STAY);
            }
            break;
        }

        case PHASE_IN: {
            if (pScaler->isTransitioning() == false) {
                if (duration_frames_ > 0) {
                    pPhase->changeNext();
                } else {
                    pPhase->change(PHASE_OUT);
                }
            }
            break;
        }

        case PHASE_STAY: {
            if (pPhase->getFrame() >= duration_frames_) {
                pScaler->transitionLinearToBottom(scale_out_frames_);
                pPhase->changeNext();
            }
            break;
        }

        case PHASE_OUT: {
            if (pScaler->isTransitioning() == false) {
                if (sayonara_end_) {
                    sayonara();
                }
                pPhase->changeNothing(); //I—¹
            }
            break;
        }

        default: {
            break;
        }
    }
    pScaler->behave();
}

void EffectBlink::processJudgement() {
    if (isOutOfSpacetime()) {
        pTarget_ = nullptr;
        if (sayonara_end_) {
            sayonara();
        }
    }
}

void EffectBlink::onInactive() {
    pTarget_ = nullptr;
}

void EffectBlink::blink(frame prm_scale_in_frames, frame prm_duration_frames, frame prm_scale_out_frames,
                        const GgafDx::GeometricActor* prm_pFollowTarget, bool prm_sayonara_end) {
    pTarget_ = prm_pFollowTarget;
    scale_in_frames_ = prm_scale_in_frames;
    duration_frames_ = prm_duration_frames;
    scale_out_frames_ = prm_scale_out_frames;
    sayonara_end_ = prm_sayonara_end;
    setScale(getScaler()->getBottom());
    getPhase()->reset(PHASE_INIT);
}

void EffectBlink::blink2(frame prm_scale_in_frames, frame prm_duration_frames, frame prm_scale_out_frames,
                        const GgafDx::GeometricActor* prm_pFollowTarget, bool prm_sayonara_end) {
    pTarget_ = prm_pFollowTarget;
    scale_in_frames_ = prm_scale_in_frames;
    duration_frames_ = prm_duration_frames;
    scale_out_frames_ = prm_scale_out_frames;
    sayonara_end_ = prm_sayonara_end;
    getPhase()->reset(PHASE_INIT);
}

bool EffectBlink::isBlinking() {
    return getPhase()->isNothing();
}

void EffectBlink::forceFadeOut(frame prm_scale_out_frames) {
    getScaler()->transitionLinearToBottom(prm_scale_out_frames);
    getPhase()->change(PHASE_OUT);
}

EffectBlink::~EffectBlink() {
    pTarget_ = nullptr;
}
