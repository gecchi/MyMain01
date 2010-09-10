#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

EffectLockon001_Release::EffectLockon001_Release(const char* prm_name, EffectLockon001* prm_pEffectLockon001) : DefaultSpriteSetActor(prm_name, "8/Lockon001") {
    _class_name = "EffectLockon001_Release";
    inactivateImmediately();
    chengeEffectTechnique("DestBlendOne"); //���Z����
    defineRotMvWorldMatrix(GgafDx9Util::setWorldMatrix_RzBxyzMv); //�r���{�[�hRz��]
    _pEffectLockon001 = prm_pEffectLockon001;
    setHitAble(false); //�����蔻�薳��

    setZEnable(false);        //Z�o�b�t�@�͍l������
    setZWriteEnable(false);  //Z�o�b�t�@�͏������ݖ���
    setSpecialDrawDepth(1); //�őO�ʕ`��B���b�N�I���G�t�F�N�g���B��Ȃ��悤�ɂ��邽��
}

void EffectLockon001_Release::initialize() {
    _pUvFlipper->copyStatesFrom(_pEffectLockon001->_pUvFlipper);
}

void EffectLockon001_Release::onActive() {
    setAlpha(_pEffectLockon001->getAlpha());
    _pUvFlipper->copyStatesFrom(_pEffectLockon001->_pUvFlipper);
    _pScaler->forceScaleRange(20000, 2000); //�X�P�[�����O�E�͈�
    _pScaler->setScale(_pEffectLockon001->_pScaler->_scale[0]);
    _pScaler->intoTargetScaleLinerUntil(20000, 50);//�X�P�[�����O
    _pMover->setFaceAng(AXIS_Z, _pEffectLockon001->_pMover->_angFace[AXIS_Z]);
    _pMover->setFaceAngVelo(AXIS_Z, _pEffectLockon001->_pMover->_angveloFace[AXIS_Z]*-3);        //��]
}

void EffectLockon001_Release::processBehavior() {
    addAlpha(-0.04);
    if (_fAlpha < 0.0f || getActivePartFrame() > 60) {
        inactivate();
    }
    _pUvFlipper->behave();
    _pMover->behave();
    _pScaler->behave();
}

void EffectLockon001_Release::processJudgement() {
//    if (_fAlpha < 0) {
//        inactivate();
//    }
}

void EffectLockon001_Release::onInactive() {
}

EffectLockon001_Release::~EffectLockon001_Release() {
}
