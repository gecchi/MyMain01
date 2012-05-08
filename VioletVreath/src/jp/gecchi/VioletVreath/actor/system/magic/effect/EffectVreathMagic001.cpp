#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

EffectVreathMagic001::EffectVreathMagic001(const char* prm_name) :
        DefaultSpriteActor(prm_name, "EffectSpeedMagic", NULL) {
    _class_name = "EffectVreathMagic001";
    changeEffectTechnique("DestBlendOne"); //加算合成Technique
    setZEnable(true);       //Zバッファは考慮有り
    setZWriteEnable(false); //Zバッファは書き込み無し
    defineRotMvWorldMatrix(GgafDxUtil::setWorldMatrix_RzBxyzMv); //変換行列をビルボードに
    setHitAble(false);
}

void EffectVreathMagic001::initialize() {
    _pUvFlipper->setFlipMethod(FLIP_ORDER_LOOP, 1);
}

void EffectVreathMagic001::onActive() {
}

void EffectVreathMagic001::processBehavior() {
    _pUvFlipper->behave();
    _pKurokoA->behave();
    _pScaler->behave();
}

void EffectVreathMagic001::processJudgement() {
}

void EffectVreathMagic001::onInactive() {
}


EffectVreathMagic001::~EffectVreathMagic001() {
}
