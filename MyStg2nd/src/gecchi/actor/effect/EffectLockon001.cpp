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
    defineRotMvWorldMatrix(GgafDx9Util::setWorldMatrix_RzBxyzMv); //�r���{�[�hRz��]
    setZEnable(false);        //Z�o�b�t�@�͍l������
    setZWriteEnable(false);  //Z�o�b�t�@�͏������ݖ���
    setSpecialDrawDepth(1); //�őO�ʕ`��B���b�N�I���G�t�F�N�g���B��Ȃ��悤�ɂ��邽��

    setHitAble(false); //�����蔻�薳��
    _pSeTransmitter->useSe(1);
    _pSeTransmitter->set(0, "humei10", GgafRepeatSeq::nextVal("CH_humei10"));
}

void EffectLockOn001::initialize() {
    _pUvFlipper->forcePtnNoRange(0, 3);   //�A�j���͈͂��O�`�P�T
    _pUvFlipper->setFlipMethod(FLIP_ORDER_LOOP, 5); //�A�j������
}

void EffectLockOn001::onActive() {
    _pUvFlipper->setPtnNoToTop();
    setAlpha(0.01);
    _pScaler->forceScaleRange(60000, 2000); //�X�P�[�����O�E�͈�
    _pScaler->setScale(60000); //(6000%)
    _pScaler->intoTargetScaleLinerUntil(2000, 25);//�X�P�[�����O�E20F��₵��2000(200%)�ɏk��
    _pMover->setFaceAngVelo(AXIS_Z, 1000);        //��]
    _pSeTransmitter->play3D(0); //���b�N�I��SE
}

void EffectLockOn001::processBehavior() {
    if (getAlpha() < 1.0) {
        addAlpha(0.01);
    }

    if (_pScaler->_method[0] == NOSCALE) {
        //�k��������ABeat
        _pScaler->forceScaleRange(2000, 4000);
        _pScaler->beat(30, 2, 2, -1); //�������[�v
    }
    _pUvFlipper->behave();
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
