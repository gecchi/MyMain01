#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

EffectEntry001::EffectEntry001(const char* prm_name) :
        DefaultMeshSetActor(prm_name, "EffectEntry001", nullptr) {
    _class_name = "EffectEntry001";
    effectBlendOne();
    setZEnable(true);
    setZWriteEnable(false);
//    defineRotMvWorldMatrix(UTIL::setWorldMatrix_RzBxyzMv); //ビルボードRz回転
}

void EffectEntry001::initialize() {
    _pScaler->forceScaleRange(R_SC(0.0), R_SC(1.0));
    useProgress(4);
}

void EffectEntry001::onActive() {
    setHitAble(false);

    _pScaler->forceScaleRange(1, 5000);
    _pScaler->setScaleToBottom();

    _pFader->forceAlphaRange(0, 0.99);
    _pFader->setAlphaToTop();

    _pKurokoA->setFaceAngVelo(11000,5000,7000);
    _pProg->set(PROG_INIT);
}

void EffectEntry001::processBehavior() {
    switch (_pProg->get()) {
        case PROG_INIT: {
            _pScaler->intoTargetScaleAcceStep(10000,1,10);
            _pProg->changeNext();
            break;
        }

        case PROG_EXPAND: {
            if (_pScaler->isWorking() == false) {
                _pFader->intoTargetAlphaLinerUntil(0, 120);
                _pProg->changeNext();
            }
            break;
        }

        case PROG_SHRINK: {
            if (_pFader->isWorking() == false) {
                sayonara();
            }
            break;
        }
        default:
            break;
    }
    _pFader->behave();
    _pScaler->behave();
    _pKurokoA->behave();
}

void EffectEntry001::processJudgement() {
}

void EffectEntry001::onInactive() {
}

EffectEntry001::~EffectEntry001() {
}
