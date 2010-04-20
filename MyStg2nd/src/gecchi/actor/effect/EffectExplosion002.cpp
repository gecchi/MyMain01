#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

EffectExplosion002::EffectExplosion002(const char* prm_name) : DefaultSpriteSetActor(prm_name, "18/EffectExplosion002") {
    _class_name = "EffectExplosion002";
    chengeEffectTechnique("DestBlendOne"); //加算合成するTechnique指定
}

void EffectExplosion002::initialize() {
    _pUvFlipper->forcePtnNoRange(0, 15);
    setHitAble(false);

}

void EffectExplosion002::onActive() {
    _pUvFlipper->setPtnNoToTop();
    _pUvFlipper->setFlipMethod(FLIP_ORDER_NOLOOP, 1); //パラパラアニメ無し
    _fAlpha = 0.99;
    _SX = _SY = _SZ = 1000;
}

void EffectExplosion002::processBehavior() {
    _fAlpha -= 0.03;
    _SX+= 100;
    _SY+= 100;
    _pUvFlipper->behave();
    _pMover->behave();
    _pScaler->behave();
}

void EffectExplosion002::processJudgement() {
    if (_fAlpha < 0) {
        inactivate();
    }
}

void EffectExplosion002::onInactive() {
}

EffectExplosion002::~EffectExplosion002() {
}
