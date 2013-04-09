#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

EffectExplosion004::EffectExplosion004(const char* prm_name) :
        DefaultSpriteSetActor(prm_name, "EffectExplosion004", nullptr) {
    _class_name = "EffectExplosion004";
    //加算合成Technique指定
    effectBlendOne();
    //ワールド変換行列はビルボード指定
    defineRotMvWorldMatrix(UTIL::setWorldMatrix_RzBxyzMv);
}

void EffectExplosion004::initialize() {
    _pUvFlipper->setFlipPtnRange(0, 63);
    _pScaler->forceRange(500, 2000);
    setHitAble(false);
}

void EffectExplosion004::onActive() {
    _pUvFlipper->setActivePtnToTop();
    _pUvFlipper->exec(FLIP_ORDER_NOLOOP, 1);
    _pScaler->setScale(500);
    _pScaler->scaleLinerUntil(2000, 64);
    setAlpha(0.99);
}

void EffectExplosion004::processBehavior() {
    _alpha -= 0.01;
    _pUvFlipper->behave();
    _pKurokoA->behave();
    _pScaler->behave();
}

void EffectExplosion004::processJudgement() {
    if (_alpha < 0) {
        sayonara();
    }
}

EffectExplosion004::~EffectExplosion004() {
}
