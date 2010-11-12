#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

EffectCondensation001::EffectCondensation001(const char* prm_name) : DefaultSpriteSetActor(prm_name, "8/Lockon001") {
    _class_name = "EffectCondensation001";
    inactivateImmediately();
    changeEffectTechnique("DestBlendOne"); //加算合成
    defineRotMvWorldMatrix(GgafDx9Util::setWorldMatrix_RzBxyzMv); //ビルボードRz回転
    setHitAble(false); //当たり判定無し
}

void EffectCondensation001::initialize() {
    _pUvFlipper->forcePtnNoRange(0, 3);   //アニメ範囲を０～１５
    _pUvFlipper->setFlipMethod(FLIP_ORDER_LOOP, 5); //アニメ順序

}

void EffectCondensation001::onActive() {
    _pUvFlipper->setPtnNoToTop();
    setAlpha(0.01);
    _pScaler->forceScaleRange(30000, 1000); //スケーリング・範囲
    _pScaler->setScale(30000);
    _pScaler->intoTargetScaleLinerUntil(1000, 30);//スケーリング・60F費やして1000に縮小
    _pMover->setFaceAngVelo(AXIS_Z, 1000);        //回転
}

void EffectCondensation001::processBehavior() {
    if (getAlpha() < 1.0) {
        addAlpha(0.05);
    }

    if (_pScaler->_method[0] == NOSCALE) {
        //縮小完了後、Beat
        _pScaler->forceScaleRange(1000, 2000);
        _pScaler->beat(30, 2, 2, -1); //無限ループ
    }
    _pUvFlipper->behave();
    _pMover->behave();
    _pScaler->behave();
}

void EffectCondensation001::processJudgement() {
//    if (_fAlpha < 0) {
//        sayonara();
//    }
}

void EffectCondensation001::onInactive() {
}

EffectCondensation001::~EffectCondensation001() {
}
