#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

EffectEntrance001::EffectEntrance001(const char* prm_name) :
        DefaultSpriteSetActor(prm_name, "Entrance001", NULL) {
    _class_name = "EffectEntrance001";
    inactivateImmed();
    effectBlendOne(); //â¡éZçáê¨
    defineRotMvWorldMatrix(UTIL::setWorldMatrix_RzBxyzMv); //ÉrÉãÉ{Å[ÉhRzâÒì]
    setHitAble(false); //ìñÇΩÇËîªíËñ≥Çµ
}

void EffectEntrance001::initialize() {
    _pUvFlipper->forcePtnRange(0, 15);   //ÉAÉjÉÅîÕàÕÇÇOÅ`ÇPÇT
    _pUvFlipper->setFlipMethod(FLIP_ORDER_LOOP, 1); //ÉAÉjÉÅèáèò
    setAlpha(0.99);
}

void EffectEntrance001::onActive() {
    _pUvFlipper->setActivePtnToTop();
    _pKurokoA->setFaceAngVelo(AXIS_Z, 3000);        //âÒì]
}

void EffectEntrance001::processBehavior() {
    _pUvFlipper->behave();
    _pKurokoA->behave();
    _pScaler->behave();
}

void EffectEntrance001::processJudgement() {
    if (VB_PLAY->isBeingPressed(VB_TURBO)) { //É^Å[É{

    } else {
        inactivate();
    }
}

void EffectEntrance001::onInactive() {
}

EffectEntrance001::~EffectEntrance001() {
}
