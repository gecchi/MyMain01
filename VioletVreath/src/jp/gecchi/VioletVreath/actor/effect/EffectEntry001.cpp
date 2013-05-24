#include "stdafx.h"
#include "EffectEntry001.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxScaler.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoA.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

EffectEntry001::EffectEntry001(const char* prm_name) :
        DefaultMeshSetActor(prm_name, "EffectEntry001", nullptr) {
    _class_name = "EffectEntry001";
    effectBlendOne();
    setZEnable(false);
    setZWriteEnable(false);
    scale_in_frames_ = duration_frames_ = scale_out_frames_ = 1;
}

void EffectEntry001::initialize() {
    useProgress(PROG_OUT);
}

void EffectEntry001::onActive() {
    setHitAble(false);
    _pScaler->forceRange(1, 20000);
    _pScaler->setScaleToBottom();
    _pKurokoA->setFaceAngVelo(11000,5000,7000);
    _pProg->reset(PROG_INIT);
}

void EffectEntry001::processBehavior() {
    switch (_pProg->get()) {
        case PROG_INIT: {
            _pScaler->scaleLinerTop(scale_in_frames_);
            _pProg->changeNext();
            break;
        }

        case PROG_IN: {
            if (_pScaler->isScaling() == false) {
                _pProg->changeNext();
            }
            break;
        }

        case PROG_STAY: {
            if (_pProg->getFrameInProgress() >= duration_frames_) {
                _pScaler->scaleLinerBottom(scale_in_frames_);
                _pProg->changeNext();
            }
            break;
        }

        case PROG_OUT: {
            if (_pScaler->isScaling() == false) {
                _pProg->changeNothing();
                sayonara();
            }
            break;
        }

        default:
            break;
    }
    _pScaler->behave();
    _pKurokoA->behave();
}

void EffectEntry001::processJudgement() {
}

void EffectEntry001::onInactive() {
}

void EffectEntry001::config(frame prm_scale_in_frames, frame prm_duration_frames, frame prm_scale_out_frames) {
    scale_in_frames_ = prm_scale_in_frames;
    duration_frames_ = prm_duration_frames;
    scale_out_frames_ = prm_scale_out_frames;
}

EffectEntry001::~EffectEntry001() {
}
