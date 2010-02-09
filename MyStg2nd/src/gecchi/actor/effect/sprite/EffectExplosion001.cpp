#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

EffectExplosion001::EffectExplosion001(const char* prm_name) : DefaultSpriteSetActor(prm_name, "18/EffectExplosion001") {
    _class_name = "EffectExplosion001";
    setTechnique("DestBlendOne"); //‰ÁŽZ‡¬TechniqueŽw’è
    defineWorldMatrix(GgafDx9Util::calcWorldMatrix_ScRzBBxyzMv);
}

void EffectExplosion001::initialize() {
    setUvFlipMethod(FLIP_ORDER_NOLOOP, 1);
    setUvFlipPtnRenge(0, 15);
    setHitAble(false);

}

void EffectExplosion001::onActive() {
    resetUvFlipPtnNo();
    _fAlpha = 0.99;
    _SX = _SY = _SZ = 1000;
}

void EffectExplosion001::processBehavior() {
    _fAlpha -= 0.03;
    _SX+= 100;
    _SY+= 100;
    behaveUvFlip();
    _pMover->behave();
}

void EffectExplosion001::processJudgement() {
    if (_fAlpha < 0) {
        inactivate();
    }
}

EffectExplosion001::~EffectExplosion001() {
}
