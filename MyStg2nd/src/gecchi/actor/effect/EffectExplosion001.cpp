#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

EffectExplosion001::EffectExplosion001(const char* prm_name) : DefaultSpriteSetActor(prm_name, "18/EffectExplosion001") {
    _class_name = "EffectExplosion001";
    chengeEffectTechnique("DestBlendOne"); //‰ÁŽZ‡¬TechniqueŽw’è
    defineRotMvWorldMatrix(GgafDx9Util::setWorldMatrix_RzBxyzMv);
}

void EffectExplosion001::initialize() {
    _pUvFlipper->forcePtnNoRange(0, 15);
    setHitAble(false);

}

void EffectExplosion001::onActive() {
    _pUvFlipper->setPtnNoToTop();
    _pUvFlipper->setFlipMethod(FLIP_ORDER_NOLOOP, 1);
    _fAlpha = 0.99;
    _SX = _SY = _SZ = 1000;
}

void EffectExplosion001::processBehavior() {
    _fAlpha -= 0.03;
    _SX+= 100;
    _SY+= 100;
    _pUvFlipper->behave();
    _pMover->behave();
    _pScaler->behave();
}

void EffectExplosion001::processJudgement() {
    if (_fAlpha < 0) {
        sayonara();
    }
}

EffectExplosion001::~EffectExplosion001() {
}
