#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

EffectLockon001_Sub::EffectLockon001_Sub(const char* prm_name) : EffectLockon001(prm_name, "8/Lockon001_Sub") {
    _class_name = "EffectLockon001_Sub";
    _pPrg->change(EffectLockon001_SCENE_PROG_LOCK);
}

void EffectLockon001_Sub::initialize() {
    EffectLockon001::initialize();
    _pUvFlipper->forcePtnNoRange(0, 3);   //ƒAƒjƒ”ÍˆÍ‚ð‚O`‚P‚T
    _pUvFlipper->setFlipMethod(FLIP_ORDER_LOOP, 5); //ƒAƒjƒ‡˜
}

void EffectLockon001_Sub::onActive() {
    EffectLockon001::onActive();
    _pEffectLockon001_Main = (EffectLockon001_Main*)getParent()->getSubFirst();
    _pUvFlipper->setPtnNoToTop();
    setAlpha(0.01);
    _SX = _SY = _SZ = _pEffectLockon001_Main->_SX;
    _pKuroko->setFaceAngVelo(AXIS_Z, 1000);        //‰E‰ñ“]
    //_pSeTransmitter->play3D(0); //ƒƒbƒNƒIƒ“SE
    locateAs(_pTarget);

    _pPrg->change(EffectLockon001_SCENE_PROG_LOCK);
}

void EffectLockon001_Sub::processBehavior() {
    EffectLockon001::processBehavior();

    if (_pPrg->get() == EffectLockon001_SCENE_PROG_LOCK) {
        if (getAlpha() < 0.7) {
            if (_pEffectLockon001_Main->_pPrg->get() == EffectLockon001_SCENE_PROG_LOCK) {
                addAlpha(0.07);
            } else if (_pEffectLockon001_Main->_pPrg->get() == EffectLockon001_SCENE_PROG_FIRST_LOCK) {
                addAlpha(0.01);
            } else {
                addAlpha(0.01);
            }
         }
         //k¬Š®—¹ŒãAMain‚Ìƒr[ƒg‚É‡‚í‚¹‚é
         _SX = _SY = _SZ = _pEffectLockon001_Main->_SX;
         _pKuroko->_angveloFace[AXIS_Z] = _pEffectLockon001_Main->_pKuroko->_angveloFace[AXIS_Z];
         if (_pTarget) {
             if (_pTarget->isActiveActor() || _pTarget->_will_activate_after_flg) {
                 if (abs(_pTarget->_X-_X) <= 200000 &&
                     abs(_pTarget->_Y-_Y) <= 200000 &&
                     abs(_pTarget->_Z-_Z) <= 200000) {
                     locateAs(_pTarget);
                     _pKuroko->setMvVelo(0);
                 } else {
                     _pKuroko->setMvAng(_pTarget);
                     _pKuroko->setMvVelo(200000);
                 }
             } else {
                 _pPrg->change(EffectLockon001_SCENE_PROG_RELEASE);
             }
         } else {
             _pPrg->change(EffectLockon001_SCENE_PROG_RELEASE);
         }
    }

    if (_pPrg->get() == EffectLockon001_SCENE_PROG_RELEASE) {
        _pTarget = NULL;
        addAlpha(-0.05);
        _SX = _SY = _SZ = _pEffectLockon001_Main->_SX;
        _pKuroko->_angveloFace[AXIS_Z] = _pEffectLockon001_Main->_pKuroko->_angveloFace[AXIS_Z];
        if (getAlpha() <= 0.0) {
            inactivate();
        }
    }

    _pUvFlipper->behave();
    _pKuroko->behave();
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

    if (_pPrg->get() == EffectLockon001_SCENE_PROG_LOCK) {
    } else if (_pPrg->get() == EffectLockon001_SCENE_PROG_RELEASE) {
        _pKuroko->setFaceAngVelo(AXIS_Z, 1000);   //‰E‰ñ“]
        _pPrg->change(EffectLockon001_SCENE_PROG_LOCK);
    }

}
void EffectLockon001_Sub::releaseLockon() {
    if (isActiveActor()) {
        if (_pPrg->get() == EffectLockon001_SCENE_PROG_LOCK) {
            _pKuroko->setFaceAngVelo(AXIS_Z, _pKuroko->_angveloFace[AXIS_Z]*-3); //‘¬‚­‹t‰ñ“]
            _pPrg->change(EffectLockon001_SCENE_PROG_RELEASE);
        } else if (_pPrg->get() == EffectLockon001_SCENE_PROG_RELEASE) {
            //‰½‚à–³‚µ
        }
    }
    _pTarget = NULL;
}

EffectLockon001_Sub::~EffectLockon001_Sub() {
}

