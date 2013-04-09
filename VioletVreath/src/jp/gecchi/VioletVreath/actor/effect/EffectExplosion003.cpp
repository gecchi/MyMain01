#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

EffectExplosion003::EffectExplosion003(const char* prm_name) :
        DefaultSpriteSetActor(prm_name, "EffectExplosion003", nullptr) {
    _class_name = "EffectExplosion003";
    //加算合成Technique指定
    effectBlendOne();
    //ワールド変換行列はビルボード指定
    defineRotMvWorldMatrix(UTIL::setWorldMatrix_RzBxyzMv);
}

void EffectExplosion003::initialize() {
    _pUvFlipper->setFlipPtnRange(0, 63);
    _pScaler->forceRange(500, 2000);
    setHitAble(false);
}

void EffectExplosion003::onActive() {
    _pUvFlipper->setActivePtnToTop();
    _pUvFlipper->exec(FLIP_ORDER_NOLOOP, 1);
    _pScaler->setScale(500);
    _pScaler->scaleLinerUntil(2000, 64);
    setAlpha(0.99);
}

void EffectExplosion003::processBehavior() {
    _alpha -= 0.01;
    _pUvFlipper->behave();
    _pKurokoA->behave();
    _pScaler->behave();
}

void EffectExplosion003::processJudgement() {
    if (_alpha < 0) {
        sayonara();
    }
}

EffectExplosion003::~EffectExplosion003() {
}
