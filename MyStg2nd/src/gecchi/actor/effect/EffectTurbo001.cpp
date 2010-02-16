#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

EffectTurbo001::EffectTurbo001(const char* prm_name) : DefaultSpriteActor(prm_name, "Turbo001") {
    _class_name = "EffectTurbo001";
    inactivateImmediately();
    chengeEffectTechnique("DestBlendOne"); //ÁZ¬
    defineWorldMatrix(GgafDx9Util::calcWorldMatrix_ScRzBBxyzMv); //r{[hRzñ]
    setHitAble(false); //½è»è³µ
}

void EffectTurbo001::initialize() {
    _pUvFliper->forceUvFlipPtnRange(0, 15);   //AjÍÍðO`PT
    _pUvFliper->setUvFlipMethod(FLIP_ORDER_LOOP, 1); //Aj
    setAlpha(0.99);
}

void EffectTurbo001::onActive() {
    _pUvFliper->resetUvFlipPtnNo();
    _pMover->setFaceAngVelo(AXIS_Z, 3000);        //ñ]
}

void EffectTurbo001::processBehavior() {
    _pUvFliper->behave();
    _pMover->behave();
    _pScaler->behave();
}

void EffectTurbo001::processJudgement() {
    if (VB::isBeingPressed(VB_TURBO)) { //^[{

    } else {
        inactivate();
    }
}

void EffectTurbo001::onInactive() {
}

EffectTurbo001::~EffectTurbo001() {
}
