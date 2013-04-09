#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

EffectWormhole001::EffectWormhole001(const char* prm_name) :
        EffectWormhole(prm_name, "8/EffectWormhole001") {
    _class_name = "EffectWormhole001";
    inactivateImmed();
    effectBlendOne(); //���Z����
    defineRotMvWorldMatrix(UTIL::setWorldMatrix_RzBxyzMv); //�r���{�[�hRz��]
    setHitAble(false); //�����蔻�薳��
}

void EffectWormhole001::initialize() {
}

void EffectWormhole001::onActive() {
    setAlpha(0.01);
    _pScaler->forceRange(30000, 1000); //�X�P�[�����O�E�͈�
    _pScaler->setScale(30000);
    _pScaler->scaleLinerUntil(1000, 30);//�X�P�[�����O�E60F��₵��1000�ɏk��
    _pKurokoA->setFaceAngVelo(AXIS_Z, 1000);        //��]
}

void EffectWormhole001::processBehavior() {
    if (getAlpha() < 1.0) {
        addAlpha(0.05);
    }

    if (_pScaler->_method[0] == NOSCALE) {
        //�k��������ABeat
        _pScaler->forceRange(1000, 2000);
        _pScaler->beat(30, 2, 2, -1); //�������[�v
    }
    _pKurokoA->behave();
    _pScaler->behave();
}

void EffectWormhole001::processJudgement() {
//    if (_alpha < 0) {
//        sayonara();
//    }
}

void EffectWormhole001::onInactive() {
}

EffectWormhole001::~EffectWormhole001() {
}
