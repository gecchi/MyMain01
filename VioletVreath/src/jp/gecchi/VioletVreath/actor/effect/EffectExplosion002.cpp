#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

EffectExplosion002::EffectExplosion002(const char* prm_name) :
        DefaultSpriteSetActor(prm_name, "EffectExplosion002", NULL) {
    _class_name = "EffectExplosion002";
    changeEffectTechnique("DestBlendOne"); //加算合成するTechnique指定
}

void EffectExplosion002::initialize() {
    _pUvFlipper->forcePtnRange(0, 15);
    setHitAble(false);

}

void EffectExplosion002::onActive() {
    _pUvFlipper->setActivePtnToTop();
    _pUvFlipper->setFlipMethod(FLIP_ORDER_NOLOOP, 1); //パラパラアニメ無し
    _alpha = 0.99;
    _SX = _SY = _SZ = 1000;
}

void EffectExplosion002::processBehavior() {
    _alpha -= 0.03;
    _SX+= 100;
    _SY+= 100;
    _pUvFlipper->behave();
    _pKurokoA->behave();
    _pScaler->behave();
}

void EffectExplosion002::processJudgement() {
    if (_alpha < 0) {
        sayonara();
    }
}

void EffectExplosion002::onInactive() {
}

EffectExplosion002::~EffectExplosion002() {
}
