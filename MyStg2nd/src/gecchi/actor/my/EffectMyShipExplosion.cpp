#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

EffectMyShipExplosion::EffectMyShipExplosion(const char* prm_name) : DefaultSpriteSetActor(prm_name, "EffectExplosion001") {
    _class_name = "EffectMyShipExplosion";
    changeEffectTechnique("DestBlendOne"); //加算合成Technique指定
    defineRotMvWorldMatrix(GgafDx9Util::setWorldMatrix_RzBxyzMv);
}

void EffectMyShipExplosion::initialize() {
    _pUvFlipper->forcePtnNoRange(0, 15);
    setHitAble(false);
}

void EffectMyShipExplosion::onActive() {
    _pUvFlipper->setActivePtnNoToTop();
    _pUvFlipper->setFlipMethod(FLIP_ORDER_NOLOOP, 20);
    locateAs(P_MYSHIP);
    _fAlpha = 0.99;
    _pScaler->setScale(8000);
    _pMvNavigator->setFaceAngVelo(AXIS_Z, 2000);
}

void EffectMyShipExplosion::processBehavior() {
    _fAlpha -= 0.01;
    locateAs(P_MYSHIP);
    _pUvFlipper->behave();
    _pMvNavigator->behave();
    _pScaler->behave();
}

void EffectMyShipExplosion::processJudgement() {
    if (_pUvFlipper->_uvflip_method == NOT_ANIMATED) {
        inactivate();
    }
}

EffectMyShipExplosion::~EffectMyShipExplosion() {
}
