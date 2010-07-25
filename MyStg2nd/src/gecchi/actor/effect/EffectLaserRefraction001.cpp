#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

EffectLaserRefraction001::EffectLaserRefraction001(const char* prm_name)
               : DefaultSpriteSetActor(prm_name, "EffectExplosion003") {
    _class_name = "EffectLaserRefraction001";
    chengeEffectTechnique("DestBlendOne"); //加算合成するTechnique指定
}

void EffectLaserRefraction001::initialize() {
    _pUvFlipper->forcePtnNoRange(0, 63);
    setHitAble(false);

}

void EffectLaserRefraction001::onActive() {
    _pUvFlipper->setPtnNoToTop();
    _pUvFlipper->setFlipMethod(FLIP_ORDER_LOOP, 1); //パラパラアニメ無し
    _fAlpha = 0.99;
    _SX = _SY = _SZ = 10000;
}

void EffectLaserRefraction001::processBehavior() {
    _SX+= 100;
    _SY+= 100;
    _pUvFlipper->behave();
    _pMover->behave();
    _pScaler->behave();
}

void EffectLaserRefraction001::processJudgement() {
//    if (_fAlpha < 0) {
//        sayonara();
//    }
}

void EffectLaserRefraction001::onInactive() {
}

EffectLaserRefraction001::~EffectLaserRefraction001() {
}
