#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

EffectExplosion001::EffectExplosion001(const char* prm_name) :
        DefaultSpriteSetActor(prm_name, "EffectExplosion001", NULL) {
    _class_name = "EffectExplosion001";
    changeEffectTechnique("DestBlendOne"); //加算合成Technique指定
    defineRotMvWorldMatrix(GgafDxUtil::setWorldMatrix_RzBxyzMv); //XYZ軸ビルボード
}

void EffectExplosion001::initialize() {
    _pUvFlipper->forcePtnNoRange(0, 15);
    setHitAble(false);

}

void EffectExplosion001::onActive() {
    _pUvFlipper->setActivePtnNoToTop();
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
    _pKurokoA->resetMv();
}


EffectExplosion001::~EffectExplosion001() {
}
