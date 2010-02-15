#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

EffectTurbo002::EffectTurbo002(const char* prm_name) : DefaultSpriteActor(prm_name, "Turbo002") {
    _class_name = "EffectTurbo002";
    inactivateImmediately();
    setTechnique("DestBlendOne"); //���Z����
    setHitAble(false); //�����蔻�薳��
}

void EffectTurbo002::initialize() {
    setUvFlipPtnRenge(0, 1);   //�A�j���͈͂��O�`�P�T
    setUvFlipMethod(FLIP_ORDER_LOOP, 2); //�A�j������

}

void EffectTurbo002::onActive() {
    resetUvFlipPtnNo();
    setAlpha(0.99);
    _pScaler->setScaleRange(100000, 1000); //�X�P�[�����O�E�͈�
    _pScaler->setScale(1000);
    _pScaler->intoTargetScaleLinerUntil(100000, 60);//�X�P�[�����O�E60F��₵��1000�ɏk��
    _pMover->setFaceAng(AXIS_Y, ANGLE90);
    _pMover->setFaceAngVelo(AXIS_Z, 2000);
}

void EffectTurbo002::processBehavior() {
    addAlpha(-(1.0/60.0));
    behaveUvFlip();
    _pMover->behave();
    _pScaler->behave();
}

void EffectTurbo002::processJudgement() {
    if (_pScaler->_method[0] == NOSCALE) {
        inactivate();
    }
}

void EffectTurbo002::onInactive() {
}

EffectTurbo002::~EffectTurbo002() {
}
