#include "stdafx.h"
#include "EffectEntry.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxScaler.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

EffectEntry::EffectEntry(const char* prm_name, const char* prm_model) :
        DefaultMeshSetActor(prm_name, prm_model, nullptr) {
    _class_name = "EffectEntry";
    setHitAble(false);
    pScaler_ = NEW GgafDxScaler(this);
    pTarget_ = nullptr;
    scale_in_frames_ = 1;
    duration_frames_ = 1;
    scale_out_frames_ = 1;
    useProgress(PROG_BANPEI);
    pScaler_->forceRange(0, R_SC(1.0));
}

void EffectEntry::onActive() {
    setScale(pScaler_->getBottom());
    getProgress()->reset(PROG_INIT);
}

void EffectEntry::processBehavior() {
    if (pTarget_) {
        if (pTarget_->onChangeToInactive()) {
            pTarget_ = nullptr;
        } else {
            positionAs(pTarget_);
        }
    }
    if (getActiveFrame() >= GGAF_END_DELAY) {
        pTarget_ = nullptr;
        sayonara();
    }

    GgafProgress* pProg = getProgress();
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
            if (pProg->getFrameInProgress() >= duration_frames_) {
                pScaler_->transitionLinerToBottom(scale_in_frames_);
                pProg->changeNext();
            }
            break;
        }

        case PROG_OUT: {
            if (pScaler_->isTransitioning() == false) {
                pProg->changeNothing();
                sayonara();
            }
            break;
        }

        default: {
            break;
        }
    }
    pScaler_->behave();
}

void EffectEntry::processJudgement() {
    if (isOutOfUniverse()) {
        pTarget_ = nullptr;
        sayonara();
    }
}

void EffectEntry::onInactive() {
    pTarget_ = nullptr;
}

void EffectEntry::positionFollow(GgafDxCore::GgafDxGeometricActor* prm_pTarget) {
    pTarget_  = prm_pTarget;
}

void EffectEntry::config(frame prm_scale_in_frames, frame prm_duration_frames, frame prm_scale_out_frames) {
    scale_in_frames_ = prm_scale_in_frames;
    duration_frames_ = prm_duration_frames;
    scale_out_frames_ = prm_scale_out_frames;
}

EffectEntry::~EffectEntry() {
    GGAF_DELETE(pScaler_);
    pTarget_ = nullptr;
}
