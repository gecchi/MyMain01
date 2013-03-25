#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

EffectTurbo001::EffectTurbo001(const char* prm_name) :
        DefaultSpriteActor(prm_name, "Turbo001", nullptr) {
    _class_name = "EffectTurbo001";
    inactivateImmed();
    effectBlendOne(); //ÁZ¬
    defineRotMvWorldMatrix(UTIL::setWorldMatrix_RzBxyzMv); //r{[hRzñ]
    setHitAble(false); //½è»è³µ
}

void EffectTurbo001::initialize() {
    _pUvFlipper->setFlipPtnRange(0, 15);   //AjÍÍðO`PT
    _pUvFlipper->exec(FLIP_ORDER_LOOP, 1); //Aj
    setAlpha(0.99);
}

void EffectTurbo001::onActive() {
    _pUvFlipper->setActivePtnToTop();
    _pKurokoA->setFaceAngVelo(AXIS_Z, 3000);        //ñ]
}

void EffectTurbo001::processBehavior() {
    _pUvFlipper->behave();
    _pKurokoA->behave();
    _pScaler->behave();
}

void EffectTurbo001::processJudgement() {
    if (VB_PLAY->isBeingPressed(VB_TURBO)) { //^[{

    } else {
        inactivate();
    }
}

void EffectTurbo001::onInactive() {
}

EffectTurbo001::~EffectTurbo001() {
}
