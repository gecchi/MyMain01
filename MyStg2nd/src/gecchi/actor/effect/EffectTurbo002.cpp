#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

EffectTurbo002::EffectTurbo002(const char* prm_name) :
        DefaultSpriteActor(prm_name, "Turbo002", NULL) {
    _class_name = "EffectTurbo002";
    inactivateImmediately();
    changeEffectTechnique("DestBlendOne"); //加算合成
    setHitAble(false); //当たり判定無し
}

void EffectTurbo002::initialize() {
    _pUvFlipper->forcePtnNoRange(0, 0);   //アニメ範囲を０～１５
    _pUvFlipper->setFlipMethod(FLIP_ORDER_LOOP, 2); //アニメ順序

}

void EffectTurbo002::onActive() {
    _pUvFlipper->setActivePtnNoToTop();
    setAlpha(0.4);
    _pScaler->forceScaleRange(100000, 1000); //スケーリング・範囲
    _pScaler->setScale(1000);
    _pScaler->intoTargetScaleLinerUntil(100000, 60);//スケーリング・60F費やして1000に縮小
    _pKurokoA->setFaceAng(AXIS_Y, ANGLE90);
    _pKurokoA->setFaceAngVelo(AXIS_Z, 2000);
}

void EffectTurbo002::processBehavior() {
    addAlpha(-(1.0/60.0));
    _pUvFlipper->behave();
    _pKurokoA->behave();
    _pScaler->behave();
}

void EffectTurbo002::processJudgement() {
    if (_pScaler->_method[0] == NOSCALE) {
        inactivate();
    }
}

void EffectTurbo002::onInactive() {
}

EffectTurbo002::~EffectTurbo002() {
}
