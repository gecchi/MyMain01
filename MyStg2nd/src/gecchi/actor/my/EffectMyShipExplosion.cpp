#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace MyStg2nd;

EffectMyShipExplosion::EffectMyShipExplosion(const char* prm_name) : 
        DefaultSpriteSetActor(prm_name, "EffectExplosion001", NULL) {
    _class_name = "EffectMyShipExplosion";
    changeEffectTechnique("DestBlendOne"); //‰ÁŽZ‡¬TechniqueŽw’è
    defineRotMvWorldMatrix(GgafDxUtil::setWorldMatrix_RzBxyzMv);
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
    _pKurokoA->setFaceAngVelo(AXIS_Z, 2000);
}

void EffectMyShipExplosion::processBehavior() {
    _fAlpha -= 0.01;
    locateAs(P_MYSHIP);
    _pUvFlipper->behave();
    _pKurokoA->behave();
    _pScaler->behave();
}

void EffectMyShipExplosion::processJudgement() {
    if (_pUvFlipper->_uvflip_method == NOT_ANIMATED) {
        inactivate();
    }
}

EffectMyShipExplosion::~EffectMyShipExplosion() {
}
