#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace MyStg2nd;

EffectExplosion003::EffectExplosion003(const char* prm_name) :
        DefaultSpriteSetActor(prm_name, "EffectExplosion003", NULL) {
    _class_name = "EffectExplosion003";
    //���Z����Technique�w��
    changeEffectTechnique("DestBlendOne");
    //���[���h�ϊ��s��̓r���{�[�h�w��
    defineRotMvWorldMatrix(GgafDxUtil::setWorldMatrix_RzBxyzMv);
}

void EffectExplosion003::initialize() {
    _pUvFlipper->forcePtnNoRange(0, 63);
    _pScaler->forceScaleRange(500, 2000);
    setHitAble(false);
}

void EffectExplosion003::onActive() {
    _pUvFlipper->setActivePtnNoToTop();
    _pUvFlipper->setFlipMethod(FLIP_ORDER_NOLOOP, 1);
    _pScaler->setScale(500);
    _pScaler->intoTargetScaleLinerUntil(2000, 64);
    setAlpha(0.99);
}

void EffectExplosion003::processBehavior() {
    _fAlpha -= 0.01;
    _pUvFlipper->behave();
    _pKurokoA->behave();
    _pScaler->behave();
}

void EffectExplosion003::processJudgement() {
    if (_fAlpha < 0) {
        sayonara();
    }
}

EffectExplosion003::~EffectExplosion003() {
}
