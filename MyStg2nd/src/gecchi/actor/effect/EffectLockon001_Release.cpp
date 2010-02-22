#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

EffectLockOn001_Release::EffectLockOn001_Release(const char* prm_name, EffectLockOn001* prm_pEffectLockOn001) : DefaultSpriteSetActor(prm_name, "8/LockOn001") {
    _class_name = "EffectLockOn001_Release";
    inactivateImmediately();
    chengeEffectTechnique("DestBlendOne"); //加算合成
    defineWorldMatrix(GgafDx9Util::calcWorldMatrix_ScRzBBxyzMv); //ビルボードRz回転
    _pEffectLockOn001 = prm_pEffectLockOn001;
    setHitAble(false); //当たり判定無し
}

void EffectLockOn001_Release::initialize() {
    _pUvFlipper->copyStatesFrom(_pEffectLockOn001->_pUvFlipper);
}

void EffectLockOn001_Release::onActive() {
    setAlpha(_pEffectLockOn001->getAlpha());
    _pUvFlipper->copyStatesFrom(_pEffectLockOn001->_pUvFlipper);
    _pScaler->forceScaleRange(20000, 1000); //スケーリング・範囲
    _pScaler->setScale(_pEffectLockOn001->_pScaler->_scale[0]);
    _pScaler->intoTargetScaleLinerUntil(20000, 60);//スケーリング
    _pMover->setFaceAng(AXIS_Z, _pEffectLockOn001->_pMover->_angFace[AXIS_Z]);
    _pMover->setFaceAngVelo(AXIS_Z, _pEffectLockOn001->_pMover->_angveloFace[AXIS_Z]);        //回転
}

void EffectLockOn001_Release::processBehavior() {
    addAlpha(-0.01);
    if (_pScaler->_method[0] == NOSCALE) {
        inactivate();
    }
    _pUvFlipper->behave();
    _pMover->behave();
    _pScaler->behave();
}

void EffectLockOn001_Release::processJudgement() {
//    if (_fAlpha < 0) {
//        inactivate();
//    }
}

void EffectLockOn001_Release::onInactive() {
}

EffectLockOn001_Release::~EffectLockOn001_Release() {
}
