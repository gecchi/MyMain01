#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

EffectLockOn001::EffectLockOn001(const char* prm_name) : DefaultSpriteSetActor(prm_name, "8/LockOn001") {
    _class_name = "EffectLockOn001";
    inactivateImmediately();
    chengeEffectTechnique("DestBlendOne"); //加算合成
    defineWorldMatrix(GgafDx9Util::setWorldMatrix_RzBxyzMv); //ビルボードRz回転
    setHitAble(false); //当たり判定無し
}

void EffectLockOn001::initialize() {
    _pUvFlipper->forcePtnNoRange(0, 3);   //アニメ範囲を０～１５
    _pUvFlipper->setFlipMethod(FLIP_ORDER_LOOP, 5); //アニメ順序

}

void EffectLockOn001::onActive() {
    _pUvFlipper->setPtnNoToTop();
    setAlpha(0.01);
    _pScaler->forceScaleRange(60000, 2000); //スケーリング・範囲
    _pScaler->setScale(60000);
    _pScaler->intoTargetScaleLinerUntil(2000, 30);//スケーリング・30F費やして2000に縮小
    _pMover->setFaceAngVelo(AXIS_Z, 1000);        //回転
}

void EffectLockOn001::processBehavior() {
    if (getAlpha() < 1.0) {
        addAlpha(0.05);
    }

    if (_pScaler->_method[0] == NOSCALE) {
        //縮小完了後、Beat
        _pScaler->forceScaleRange(2000, 4000);
        _pScaler->beat(30, 2, 2, -1); //無限ループ
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
