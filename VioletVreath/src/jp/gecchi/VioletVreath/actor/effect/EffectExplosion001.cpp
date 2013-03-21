#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

EffectExplosion001::EffectExplosion001(const char* prm_name) :
        DefaultSpriteSetActor(prm_name, "EffectExplosion001", nullptr) {
    _class_name = "EffectExplosion001";
    effectBlendOne(); //加算合成Technique指定
    defineRotMvWorldMatrix(UTIL::setWorldMatrix_RzBxyzMv); //XYZ軸ビルボード
}

void EffectExplosion001::initialize() {
    _pUvFlipper->setFlipPtnRange(0, 15);
    setHitAble(false);

}

void EffectExplosion001::onActive() {
    _pUvFlipper->setActivePtnToTop();
    _pUvFlipper->setFlipMethod(FLIP_ORDER_NOLOOP, 1);
    _alpha = 0.99;
    _SX = _SY = _SZ = 1000;
}

void EffectExplosion001::processBehavior() {
    _alpha -= 0.03;
    _SX+= 100;
    _SY+= 100;
    _pUvFlipper->behave();
    _pKurokoA->behave();
    _pScaler->behave();
}

void EffectExplosion001::processJudgement() {
    if (_alpha < 0) {
        sayonara();
    }
}

void EffectExplosion001::onInactive() {
    _pKurokoA->setMvVelo(0);
    _pKurokoA->setMvAcce(0);
}


EffectExplosion001::~EffectExplosion001() {
}
