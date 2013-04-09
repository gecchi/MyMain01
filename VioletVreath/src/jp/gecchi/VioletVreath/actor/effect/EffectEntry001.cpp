#include "stdafx.h"
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
//    defineRotMvWorldMatrix(UTIL::setWorldMatrix_RzBxyzMv); //ビルボードRz回転
}

void EffectEntry001::initialize() {
    useProgress(4);
}

void EffectEntry001::onActive() {
    setHitAble(false);

    _pScaler->forceRange(1, 20000);
    _pScaler->setScaleToBottom();

    _pAFader->forceRange(0, 0.99);
    _pAFader->setToTop();

    _pKurokoA->setFaceAngVelo(11000,5000,7000);
    _pProg->reset(PROG_INIT);
}

void EffectEntry001::processBehavior() {
    switch (_pProg->get()) {
        case PROG_INIT: {
            _pScaler->scaleAcceStep(10000,1,2);
            _pProg->changeNext();
            break;
        }

        case PROG_EXPAND: {
            if (_pScaler->isScaling() == false) {
                _pAFader->fadeLinerUntil(0, 120);
                _pProg->changeNext();
            }
            break;
        }

        case PROG_SHRINK: {
            if (_pAFader->isFading() == false) {
                sayonara();
            }
            break;
        }
        default:
            break;
    }
    _pAFader->behave();
    _pScaler->behave();
    _pKurokoA->behave();
}

void EffectEntry001::processJudgement() {
}

void EffectEntry001::onInactive() {
}

EffectEntry001::~EffectEntry001() {
}
