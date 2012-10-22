#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

EffectSylviaEye001::EffectSylviaEye001(const char* prm_name) :
        DefaultSpriteActor(prm_name, "EffectSylviaEye001", NULL) {
    _class_name = "EffectSylviaEye001";
    inactivateImmed();
    effectBlendOne(); //���Z����
    setHitAble(false); //�����蔻�薳��
    cnt_ = 0;
}

void EffectSylviaEye001::initialize() {
}

void EffectSylviaEye001::onActive() {
    cnt_ = 0;
    _pScaler->forceScaleRange(100000, 1); //�X�P�[�����O�E�͈�
    _pScaler->setScale(100000);
    _pScaler->beat(30, 0, 0, 3);
}

void EffectSylviaEye001::processBehavior() {
    _pScaler->behave();
    setAlpha( 1.3 - (_pScaler->_scale[0] / 100000.0 ) );
}

void EffectSylviaEye001::processJudgement() {
    if (_pScaler->_method[0] == NOSCALE) {
        inactivate();
    }
}

void EffectSylviaEye001::onInactive() {
}

EffectSylviaEye001::~EffectSylviaEye001() {
}
