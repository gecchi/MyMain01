#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

EffectTurbo001::EffectTurbo001(const char* prm_name) :
        DefaultSpriteActor(prm_name, "Turbo001", nullptr) {
    _class_name = "EffectTurbo001";
    inactivateImmed();
    effectBlendOne(); //���Z����
    defineRotMvWorldMatrix(UTIL::setWorldMatrix_RzBxyzMv); //�r���{�[�hRz��]
    setHitAble(false); //�����蔻�薳��
}

void EffectTurbo001::initialize() {
    _pUvFlipper->forcePtnRange(0, 15);   //�A�j���͈͂��O�`�P�T
    _pUvFlipper->setFlipMethod(FLIP_ORDER_LOOP, 1); //�A�j������
    setAlpha(0.99);
}

void EffectTurbo001::onActive() {
    _pUvFlipper->setActivePtnToTop();
    _pKurokoA->setFaceAngVelo(AXIS_Z, 3000);        //��]
}

void EffectTurbo001::processBehavior() {
    _pUvFlipper->behave();
    _pKurokoA->behave();
    _pScaler->behave();
}

void EffectTurbo001::processJudgement() {
    if (VB_PLAY->isBeingPressed(VB_TURBO)) { //�^�[�{

    } else {
        inactivate();
    }
}

void EffectTurbo001::onInactive() {
}

EffectTurbo001::~EffectTurbo001() {
}
