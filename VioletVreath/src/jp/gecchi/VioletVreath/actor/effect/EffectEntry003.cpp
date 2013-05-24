#include "stdafx.h"
#include "EffectEntry003.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxScaler.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoA.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

EffectEntry003::EffectEntry003(const char* prm_name) :
        DefaultMeshSetActor(prm_name, "EffectEntry003", nullptr) {
    _class_name = "EffectEntry003";
    effectBlendOne();
    setZEnable(false);
    setZWriteEnable(false);
}

void EffectEntry003::initialize() {
    useProgress(PROG_OUT);
}

void EffectEntry003::onActive() {
    setHitAble(false);
    _pScaler->forceRange(1, 128000);
    _pScaler->setScaleToBottom();
    _pKurokoA->setFaceAngVelo(11000,5000,7000);
    _pProg->reset(PROG_INIT);
}

void EffectEntry003::processBehavior() {
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

void EffectEntry003::processJudgement() {
}

void EffectEntry003::onInactive() {
}

EffectEntry003::~EffectEntry003() {
}
