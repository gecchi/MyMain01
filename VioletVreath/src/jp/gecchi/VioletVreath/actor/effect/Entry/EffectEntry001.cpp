#include "stdafx.h"
#include "EffectEntry001.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxScaler.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

EffectEntry001::EffectEntry001(const char* prm_name) :
        EffectEntry(prm_name, "EffectEntry001") {
    _class_name = "EffectEntry001";
    pScaler_ = NEW GgafDxScaler(this);
    effectBlendOne();
}

void EffectEntry001::initialize() {
    EffectEntry::initialize();
    useProgress(PROG_BANPEI);
}

void EffectEntry001::onActive() {
    EffectEntry::onActive();
    pScaler_->forceRange(1, 20000);
    setScale(pScaler_->getBottom());
    setFaceAng(D0ANG, D0ANG, D0ANG);
    getKuroko()->setFaceAngVelo(3000, 5000, 7000);
    getProgress()->reset(PROG_INIT);
}

void EffectEntry001::processBehavior() {
    EffectEntry::processBehavior();
    GgafProgress* pProg = getProgress();
    switch (pProg->get()) {
        case PROG_INIT: {
            pScaler_->transitionLinerToTop(scale_in_frames_);
            pProg->changeNext();
            break;
        }

        case PROG_IN: {
            if (pScaler_->isTransitioning() == false) {
                pProg->changeNext();
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
    getKuroko()->behave();
}

void EffectEntry001::config(frame prm_scale_in_frames, frame prm_duration_frames, frame prm_scale_out_frames) {
    scale_in_frames_ = prm_scale_in_frames;
    duration_frames_ = prm_duration_frames;
    scale_out_frames_ = prm_scale_out_frames;
}

EffectEntry001::~EffectEntry001() {
    GGAF_DELETE(pScaler_);
}
