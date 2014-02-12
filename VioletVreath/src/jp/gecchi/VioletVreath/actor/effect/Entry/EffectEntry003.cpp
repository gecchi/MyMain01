#include "stdafx.h"
#include "EffectEntry003.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxScaler.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

EffectEntry003::EffectEntry003(const char* prm_name) :
        EffectEntry(prm_name, "EffectEntry003") {
    _class_name = "EffectEntry003";
    pScaler_ = NEW GgafDxScaler(this);
    effectBlendOne();
}

void EffectEntry003::initialize() {
    EffectEntry::initialize();
    useProgress(PROG_BANPEI);
}

void EffectEntry003::onActive() {
    EffectEntry::onActive();
    pScaler_->forceRange(1, 128000);
    setScale(pScaler_->getBottom());
    setFaceAng(D0ANG, D0ANG, D0ANG);
    _pKuroko->setFaceAngVelo(11000,5000,7000);
    _pProg->reset(PROG_INIT);
}

void EffectEntry003::processBehavior() {
    EffectEntry::processBehavior();
    switch (_pProg->get()) {
        case PROG_INIT: {
            pScaler_->scaleLinerTop(20);
            _pProg->changeNext();
            break;
        }

        case PROG_IN: {
            if (pScaler_->isScaling() == false) {
                _pProg->changeNext();
            }
            break;
        }

        case PROG_STAY: {
            if (_pProg->getFrameInProgress() >= 10) {
                pScaler_->scaleLinerBottom(20);
                _pProg->changeNext();
            }
            break;
        }

        case PROG_OUT: {
            if (pScaler_->isScaling() == false) {
                _pProg->changeNothing();
                sayonara();
            }
            break;
        }

        default:
            break;
    }
    pScaler_->behave();
    _pKuroko->behave();
}

EffectEntry003::~EffectEntry003() {
    GGAF_DELETE(pScaler_);
}
