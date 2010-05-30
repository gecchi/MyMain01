#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

EffectLockOn001::EffectLockOn001(const char* prm_name) : DefaultSpriteSetActor(prm_name, "8/LockOn001") {
    _class_name = "EffectLockOn001";
    inactivateImmediately();
    chengeEffectTechnique("DestBlendOne"); //มZฌ
    defineWorldMatrix(GgafDx9Util::setWorldMatrix_RzBxyzMv); //r{[hRz๑]
    setHitAble(false); //ฝ่ป่ณต
    _pSeReflector->useSe(1);
    _pSeReflector->set(0, "humei10", GgafRepeatSeq::nextVal("CH_humei10"));
}

void EffectLockOn001::initialize() {
    _pUvFlipper->forcePtnNoRange(0, 3);   //Ajออ๐O`PT
    _pUvFlipper->setFlipMethod(FLIP_ORDER_LOOP, 5); //Aj

}

void EffectLockOn001::onActive() {
    _pUvFlipper->setPtnNoToTop();
    setAlpha(0.01);
    _pScaler->forceScaleRange(60000, 2000); //XP[OEออ
    _pScaler->setScale(60000); //(6000%)
    _pScaler->intoTargetScaleLinerUntil(2000, 20);//XP[OE20F๏โตฤ2000(200%)ษkฌ
    _pMover->setFaceAngVelo(AXIS_Z, 1000);        //๑]
    _pSeReflector->play3D(0);
}

void EffectLockOn001::processBehavior() {
    if (getAlpha() < 1.0) {
        addAlpha(0.05);
    }

    if (_pScaler->_method[0] == NOSCALE) {
        //kฌฎนใABeat
        _pScaler->forceScaleRange(2000, 4000);
        _pScaler->beat(30, 2, 2, -1); //ณภ[v
    }
    _pUvFlipper->behave();
    _pMover->behave();
    _pScaler->behave();
}

void EffectLockOn001::processJudgement() {
//    if (_fAlpha < 0) {
//        inactivate();
//    }
}

void EffectLockOn001::onInactive() {
}

EffectLockOn001::~EffectLockOn001() {
}
