#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

EffectTurbo001::EffectTurbo001(const char* prm_name) : DefaultSpriteActor(prm_name, "Turbo001") {
    _class_name = "EffectTurbo001";
    inactivateImmediately();
    chengeEffectTechnique("DestBlendOne"); //���Z����
    defineWorldMatrix(GgafDx9Util::setWorldMatrix_ScRzBxyzMv); //�r���{�[�hRz��]
    setHitAble(false); //�����蔻�薳��
}

void EffectTurbo001::initialize() {
    _pUvFlipper->forcePtnNoRange(0, 15);   //�A�j���͈͂��O�`�P�T
    _pUvFlipper->setFlipMethod(FLIP_ORDER_LOOP, 1); //�A�j������
    setAlpha(0.99);
}

void EffectTurbo001::onActive() {
    _pUvFlipper->setPtnNoToTop();
    _pMover->setFaceAngVelo(AXIS_Z, 3000);        //��]
}

void EffectTurbo001::processBehavior() {
    _pUvFlipper->behave();
    _pMover->behave();
    _pScaler->behave();
}

void EffectTurbo001::processJudgement() {
    if (VB::isBeingPressed(VB_TURBO)) { //�^�[�{

    } else {
        inactivate();
    }
}

void EffectTurbo001::onInactive() {
}

EffectTurbo001::~EffectTurbo001() {
}
