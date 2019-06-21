#include "EffectBlink.h"

#include "jp/ggaf/dx/actor/supporter/Rikisha.h"
#include "jp/ggaf/dx/actor/supporter/Scaler.h"



using namespace GgafLib;
using namespace VioletVreath;

enum {
    PROG_INIT ,
    PROG_IN   ,
    PROG_STAY ,
    PROG_OUT  ,
    PROG_BANPEI,
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
    getProgress()->reset(PROG_INIT);
}

void EffectBlink::processBehavior() {
    if (pTarget_) {
        if (pTarget_->hasJustChangedToInactive()) {
            pTarget_ = nullptr;
        } else {
            setPositionAt(pTarget_);
        }
    }
    if (getActiveFrame() >= GGAF_END_DELAY) {
        pTarget_ = nullptr;
        if (sayonara_end_) {
            sayonara();
        }
    }

    GgafDx::Scaler* const pScaler = getScaler();
    GgafCore::Progress* const pProg = getProgress();
    switch (pProg->get()) {
        case PROG_INIT: {
            if (scale_in_frames_ > 0) {
                pScaler->transitionLinearToTop(scale_in_frames_);
                pProg->changeNext();
            } else {
                setScale(getScaler()->getTop());
                pProg->change(PROG_STAY);
            }
            break;
        }

        case PROG_IN: {
            if (pScaler->isTransitioning() == false) {
                if (duration_frames_ > 0) {
                    pProg->changeNext();
                } else {
                    pProg->change(PROG_OUT);
                }
            }
            break;
        }

        case PROG_STAY: {
            if (pProg->getFrame() >= duration_frames_) {
                pScaler->transitionLinearToBottom(scale_out_frames_);
                pProg->changeNext();
            }
            break;
        }

        case PROG_OUT: {
            if (pScaler->isTransitioning() == false) {
                if (sayonara_end_) {
                    sayonara();
                }
                pProg->changeNothing(); //I—¹
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
    getProgress()->reset(PROG_INIT);
}

void EffectBlink::blink2(frame prm_scale_in_frames, frame prm_duration_frames, frame prm_scale_out_frames,
                        const GgafDx::GeometricActor* prm_pFollowTarget, bool prm_sayonara_end) {
    pTarget_ = prm_pFollowTarget;
    scale_in_frames_ = prm_scale_in_frames;
    duration_frames_ = prm_duration_frames;
    scale_out_frames_ = prm_scale_out_frames;
    sayonara_end_ = prm_sayonara_end;
    getProgress()->reset(PROG_INIT);
}

bool EffectBlink::isBlinking() {
    return getProgress()->isNothing();
}

void EffectBlink::forceFadeOut(frame prm_scale_out_frames) {
    getScaler()->transitionLinearToBottom(prm_scale_out_frames);
    getProgress()->change(PROG_OUT);
}

EffectBlink::~EffectBlink() {
    pTarget_ = nullptr;
}
