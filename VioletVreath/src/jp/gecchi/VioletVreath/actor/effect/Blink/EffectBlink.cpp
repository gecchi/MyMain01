#include "EffectBlink.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxScaler.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

EffectBlink::EffectBlink(const char* prm_name, const char* prm_model) :
        DefaultMassMeshActor(prm_name, prm_model, nullptr) {
    _class_name = "EffectBlink";
    setHitAble(false);
    pScaler_ = NEW GgafDxScaler(this);
    pTarget_ = nullptr;
    scale_in_frames_ = 1;
    duration_frames_ = 1;
    scale_out_frames_ = 1;
    sayonara_end_ = true;
    useProgress(PROG_BANPEI);
    pScaler_->setRange(0, R_SC(1.0));
}

void EffectBlink::onActive() {
    setScale(pScaler_->getBottom());
    getProgress()->reset(PROG_INIT);
}

void EffectBlink::processBehavior() {
    if (pTarget_) {
        if (pTarget_->hasJustChangedToInactive()) {
            pTarget_ = nullptr;
        } else {
            placeAs(pTarget_);
        }
    }
    if (getActiveFrame() >= GGAF_END_DELAY) {
        pTarget_ = nullptr;
        if (sayonara_end_) {
            sayonara();
        }
    }

    GgafProgress* const pProg = getProgress();
    switch (pProg->get()) {
        case PROG_INIT: {
            pScaler_->transitionLinerToTop(scale_in_frames_);
            pProg->changeNext();
            break;
        }

        case PROG_IN: {
            if (pScaler_->isTransitioning() == false) {
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
                pScaler_->transitionLinerToBottom(scale_out_frames_);
                pProg->changeNext();
            }
            break;
        }

        case PROG_OUT: {
            if (pScaler_->isTransitioning() == false) {
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
    pScaler_->behave();
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
                        const GgafDxCore::GgafDxGeometricActor* prm_pFollowTarget, bool prm_sayonara_end) {
    pTarget_ = prm_pFollowTarget;
    scale_in_frames_ = prm_scale_in_frames;
    duration_frames_ = prm_duration_frames;
    scale_out_frames_ = prm_scale_out_frames;
    sayonara_end_ = prm_sayonara_end;
    setScale(pScaler_->getBottom());
    getProgress()->reset(PROG_INIT);
}

bool EffectBlink::isBlinking() {
    return getProgress()->isNothing();
}

void EffectBlink::forceFadeOut(frame prm_scale_out_frames) {
    pScaler_->transitionLinerToBottom(prm_scale_out_frames);
    getProgress()->change(PROG_OUT);
}

EffectBlink::~EffectBlink() {
    GGAF_DELETE(pScaler_);
    pTarget_ = nullptr;
}
