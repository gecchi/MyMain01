#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

EffectLockon001_Sub::EffectLockon001_Sub(const char* prm_name) : EffectLockon001(prm_name, "8/Lockon001_Sub") {
    _class_name = "EffectLockon001_Sub";
    setProgress(EffectLockon001_PROG_LOCK);
}

void EffectLockon001_Sub::initialize() {
    EffectLockon001::initialize();
    _pUvFlipper->forcePtnNoRange(0, 3);   //ÉAÉjÉÅîÕàÕÇÇOÅ`ÇPÇT
    _pUvFlipper->setFlipMethod(FLIP_ORDER_LOOP, 5); //ÉAÉjÉÅèáèò
}

void EffectLockon001_Sub::onActive() {
    EffectLockon001::onActive();
    _pEffectLockon001_Main = (EffectLockon001_Main*)getParent()->getSubFirst();
_TRACE_("_pEffectLockon001_Main="<<_pEffectLockon001_Main);
    _pUvFlipper->setPtnNoToTop();
    setAlpha(0.01);
    _SX = _SY = _SZ = _pEffectLockon001_Main->_SX;
    _pMover->setFaceAngVelo(AXIS_Z, 1000);        //âEâÒì]
    //_pSeTransmitter->play3D(0); //ÉçÉbÉNÉIÉìSE
    setGeometry(_pTarget);

    setProgress(EffectLockon001_PROG_LOCK);
}

void EffectLockon001_Sub::processBehavior() {
    EffectLockon001::processBehavior();

    if (getProgress() == EffectLockon001_PROG_LOCK) {
        if (getAlpha() < 0.7) {
            if (_pEffectLockon001_Main->getProgress() == EffectLockon001_PROG_LOCK) {
                addAlpha(0.07);
            } else if (_pEffectLockon001_Main->getProgress() == EffectLockon001_PROG_FIRST_LOCK) {
                addAlpha(0.01);
            } else {
                addAlpha(0.01);
            }
         }
         //èkè¨äÆóπå„ÅAMainÇÃÉrÅ[ÉgÇ…çáÇÌÇπÇÈ
         _SX = _SY = _SZ = _pEffectLockon001_Main->_SX;
         _pMover->_angveloFace[AXIS_Z] = _pEffectLockon001_Main->_pMover->_angveloFace[AXIS_Z];
         if (_pTarget) {
             if (_pTarget->isActive() || _pTarget->_will_activate_after_flg) {
                 if (abs(_pTarget->_X-_X) <= 200000 &&
                     abs(_pTarget->_Y-_Y) <= 200000 &&
                     abs(_pTarget->_Z-_Z) <= 200000) {
                     setGeometry(_pTarget);
                     _pMover->setMvVelo(0);
                 } else {
                     _pMover->setMvAng(_pTarget);
                     _pMover->setMvVelo(200000);
                 }
             } else {
                 setProgress(EffectLockon001_PROG_RELEASE);
             }
         } else {
             setProgress(EffectLockon001_PROG_RELEASE);
         }
    }

    if (getProgress() == EffectLockon001_PROG_RELEASE) {
        _pTarget = NULL;
        addAlpha(-0.05);
        _SX = _SY = _SZ = _pEffectLockon001_Main->_SX;
        _pMover->_angveloFace[AXIS_Z] = _pEffectLockon001_Main->_pMover->_angveloFace[AXIS_Z];
        if (getAlpha() <= 0.0) {
            inactivate();
        }
    }

    _pUvFlipper->behave();
    _pMover->behave();
}

void EffectLockon001_Sub::processJudgement() {
    EffectLockon001::processJudgement();
}

void EffectLockon001_Sub::onInactive() {
    EffectLockon001::onInactive();
}

void EffectLockon001_Sub::lockon(GgafDx9GeometricActor* prm_pTarget) {
    if (prm_pTarget == NULL || _pTarget == prm_pTarget) {
        return;
    }
    _pTarget = prm_pTarget;

    if (getProgress() == EffectLockon001_PROG_LOCK) {
    } else if (getProgress() == EffectLockon001_PROG_RELEASE) {
        _pMover->setFaceAngVelo(AXIS_Z, 1000);   //âEâÒì]
        setProgress(EffectLockon001_PROG_LOCK);
    }

}
void EffectLockon001_Sub::releaseLockon() {
    if (isActive()) {
        if (getProgress() == EffectLockon001_PROG_LOCK) {
            _pMover->setFaceAngVelo(AXIS_Z, _pMover->_angveloFace[AXIS_Z]*-3); //ë¨Ç≠ãtâÒì]
            setProgress(EffectLockon001_PROG_RELEASE);
        } else if (getProgress() == EffectLockon001_PROG_RELEASE) {
            //âΩÇ‡ñ≥Çµ
        }
    }
    _pTarget = NULL;
}

EffectLockon001_Sub::~EffectLockon001_Sub() {
}

