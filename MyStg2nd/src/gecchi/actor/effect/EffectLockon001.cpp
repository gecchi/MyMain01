#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

EffectLockOn001::EffectLockOn001(const char* prm_name) : DefaultSpriteSetActor(prm_name, "8/LockOn001") {
    _class_name = "EffectLockOn001";
    inactivateImmediately();
    setTechnique("DestBlendOne"); //มZฌ
    defineWorldMatrix(GgafDx9Util::calcWorldMatrix_ScRzBBxyzMv); //r{[hRz๑]
    setHitAble(false); //ฝ่ป่ณต
}

void EffectLockOn001::initialize() {
    setUvFlipPtnRenge(0, 15);   //Ajออ๐O`PT
    setUvFlipMethod(FLIP_ORDER_LOOP, 3); //Aj

}

void EffectLockOn001::onActive() {
    resetUvFlipPtnNo();
    setAlpha(0.01);
    _pScaler->setScaleRange(5000, 1000); //XP[OEออ
    _pScaler->setScale(5000);
    _pScaler->intoTargetScaleLinerUntil(1000, 60);//XP[OE60F๏โตฤ1000ษkฌ
    _pMover->setFaceAngVelo(AXIS_Z, 1000);        //๑]
}

void EffectLockOn001::processBehavior() {
    if (getAlpha() < 1.0) {
        addAlpha(0.05);
    }

    if (_pScaler->_method[0] == NOSCALE) {
        //kฌฎนใABeat
        _pScaler->setScaleRange(1000, 2000);
        _pScaler->beat(30, 2, 2, -1); //ณภ[v
    }
    behaveUvFlip();
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
