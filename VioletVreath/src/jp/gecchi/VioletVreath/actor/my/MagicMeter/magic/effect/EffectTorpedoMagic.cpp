#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

EffectTorpedoMagic::EffectTorpedoMagic(const char* prm_name) :
        DefaultSpriteActor(prm_name, "EffectTorpedoMagic", NULL) {
    _class_name = "EffectTorpedoMagic";
    effectBlendOne(); //���Z����Technique
    setZEnable(true);       //Z�o�b�t�@�͍l���L��
    setZWriteEnable(false); //Z�o�b�t�@�͏������ݖ���
    defineRotMvWorldMatrix(UTIL::setWorldMatrix_RzBxyzMv); //�ϊ��s����r���{�[�h��
    setHitAble(false);
}

void EffectTorpedoMagic::initialize() {
    _pUvFlipper->setFlipMethod(FLIP_ORDER_LOOP, 1);
}

void EffectTorpedoMagic::onActive() {
}

void EffectTorpedoMagic::processBehavior() {
    _pUvFlipper->behave();
    _pKurokoA->behave();
    _pScaler->behave();
}

void EffectTorpedoMagic::processJudgement() {
}

void EffectTorpedoMagic::onInactive() {
}


EffectTorpedoMagic::~EffectTorpedoMagic() {
}
