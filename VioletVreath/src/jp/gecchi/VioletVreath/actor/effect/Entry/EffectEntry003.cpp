#include "stdafx.h"
#include "EffectEntry003.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxScaler.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoA.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

EffectEntry003::EffectEntry003(const char* prm_name) :
        EffectEntry(prm_name, "EffectEntry003") {
    _class_name = "EffectEntry003";
    effectBlendOne();
}

void EffectEntry003::initialize() {
    EffectEntry::initialize();
    useProgress(PROG_OUT);
}

void EffectEntry003::onActive() {
    EffectEntry::onActive();
    _pScaler->forceRange(1, 128000);
    _pScaler->setScaleToBottom();
    _pKurokoA->setFaceAng(D0ANG, D0ANG, D0ANG);
    _pKurokoA->setFaceAngVelo(11000,5000,7000);
    _pProg->reset(PROG_INIT);
}

void EffectEntry003::processBehavior() {
    EffectEntry::processBehavior();
    switch (_pProg->get()) {
        case PROG_INIT: {
            _pScaler->scaleLinerTop(20);
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
            if (_pProg->getFrameInProgress() >= 10) {
                _pScaler->scaleLinerBottom(20);
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

EffectEntry003::~EffectEntry003() {
}
