#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

EffectLockOn001::EffectLockOn001(const char* prm_name) : DefaultSpriteSetActor(prm_name, "8/LockOn001") {
    _class_name = "EffectLockOn001";
    inactivateImmediately();
    chengeEffectTechnique("DestBlendOne"); //���Z����
    defineWorldMatrix(GgafDx9Util::calcWorldMatrix_ScRzBBxyzMv); //�r���{�[�hRz��]
    setHitAble(false); //�����蔻�薳��
}

void EffectLockOn001::initialize() {
    _pUvFliper->forceUvFlipPtnRange(0, 15);   //�A�j���͈͂��O�`�P�T
    _pUvFliper->setUvFlipMethod(FLIP_ORDER_LOOP, 3); //�A�j������

}

void EffectLockOn001::onActive() {
    _pUvFliper->resetUvFlipPtnNo();
    setAlpha(0.01);
    _pScaler->forceScaleRange(5000, 1000); //�X�P�[�����O�E�͈�
    _pScaler->setScale(5000);
    _pScaler->intoTargetScaleLinerUntil(1000, 60);//�X�P�[�����O�E60F��₵��1000�ɏk��
    _pMover->setFaceAngVelo(AXIS_Z, 1000);        //��]
}

void EffectLockOn001::processBehavior() {
    if (getAlpha() < 1.0) {
        addAlpha(0.05);
    }

    if (_pScaler->_method[0] == NOSCALE) {
        //�k��������ABeat
        _pScaler->forceScaleRange(1000, 2000);
        _pScaler->beat(30, 2, 2, -1); //�������[�v
    }
    _pUvFliper->behave();
    _pMover->behave();
    _pScaler->behave();
}

void EffectLockOn001::processJudgement() {
//    if (_fAlpha < 0) {
//        inactivate();
//    }
}

void EffectLockOn001::onInactive() {
}

EffectLockOn001::~EffectLockOn001() {
}
