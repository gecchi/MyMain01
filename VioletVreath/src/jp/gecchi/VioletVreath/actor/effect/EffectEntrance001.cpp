#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

EffectEntrance001::EffectEntrance001(const char* prm_name) :
        DefaultSpriteSetActor(prm_name, "Entrance001", NULL) {
    _class_name = "EffectEntrance001";
    inactivateImmed();
    effectBlendOne(); //���Z����
    defineRotMvWorldMatrix(UTIL::setWorldMatrix_RzBxyzMv); //�r���{�[�hRz��]
    setHitAble(false); //�����蔻�薳��
}

void EffectEntrance001::initialize() {
    _pUvFlipper->forcePtnRange(0, 15);   //�A�j���͈͂��O�`�P�T
    _pUvFlipper->setFlipMethod(FLIP_ORDER_LOOP, 1); //�A�j������
    setAlpha(0.99);
}

void EffectEntrance001::onActive() {
    _pUvFlipper->setActivePtnToTop();
    _pKurokoA->setFaceAngVelo(AXIS_Z, 3000);        //��]
}

void EffectEntrance001::processBehavior() {
    _pUvFlipper->behave();
    _pKurokoA->behave();
    _pScaler->behave();
}

void EffectEntrance001::processJudgement() {
    if (VB_PLAY->isBeingPressed(VB_TURBO)) { //�^�[�{

    } else {
        inactivate();
    }
}

void EffectEntrance001::onInactive() {
}

EffectEntrance001::~EffectEntrance001() {
}
