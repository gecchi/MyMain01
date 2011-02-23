#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

EffectMyShipExplosion::EffectMyShipExplosion(const char* prm_name) : DefaultSpriteSetActor(prm_name, "EffectExplosion001") {
    _class_name = "EffectMyShipExplosion";
    changeEffectTechnique("DestBlendOne"); //‰ÁŽZ‡¬TechniqueŽw’è
    defineRotMvWorldMatrix(GgafDx9Util::setWorldMatrix_RzBxyzMv);
}

void EffectMyShipExplosion::initialize() {
    _pUvFlipper->forcePtnNoRange(0, 15);
    setHitAble(false);
}

void EffectMyShipExplosion::onActive() {
    _pUvFlipper->setPtnNoToTop();
    _pUvFlipper->setFlipMethod(FLIP_ORDER_NOLOOP, 20);
    setCoordinateBy(P_MYSHIP);
    _fAlpha = 0.99;
    _pScaler->setScale(8000);
    _pKuroko->setFaceAngVelo(AXIS_Z, 2000);
}

void EffectMyShipExplosion::processBehavior() {
    _fAlpha -= 0.01;
    setCoordinateBy(P_MYSHIP);
    _pUvFlipper->behave();
    _pKuroko->behave();
    _pScaler->behave();
}

void EffectMyShipExplosion::processJudgement() {
    if (_pUvFlipper->_uvflip_method == NOT_ANIMATED) {
        inactivate();
    }
}

EffectMyShipExplosion::~EffectMyShipExplosion() {
}
