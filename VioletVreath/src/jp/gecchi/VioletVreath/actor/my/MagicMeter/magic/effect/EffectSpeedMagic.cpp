#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

EffectSpeedMagic::EffectSpeedMagic(const char* prm_name) :
        DefaultSpriteActor(prm_name, "EffectSpeedMagic", nullptr) {
    _class_name = "EffectSpeedMagic";
    effectBlendOne(); //加算合成Technique
    setZEnable(true);       //Zバッファは考慮有り
    setZWriteEnable(false); //Zバッファは書き込み無し
    defineRotMvWorldMatrix(UTIL::setWorldMatrix_RzBxyzMv); //変換行列をビルボードに
    setHitAble(false);
}

void EffectSpeedMagic::initialize() {
    _pUvFlipper->setFlipMethod(FLIP_ORDER_LOOP, 1);
}

void EffectSpeedMagic::onActive() {
}

void EffectSpeedMagic::processBehavior() {
    _pUvFlipper->behave();
    _pKurokoA->behave();
    _pScaler->behave();
}

void EffectSpeedMagic::processJudgement() {
}

void EffectSpeedMagic::onInactive() {
}


EffectSpeedMagic::~EffectSpeedMagic() {
}
