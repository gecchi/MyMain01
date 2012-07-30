#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

EffectTorpedoMagic::EffectTorpedoMagic(const char* prm_name) :
        DefaultSpriteActor(prm_name, "EffectTorpedoMagic", NULL) {
    _class_name = "EffectTorpedoMagic";
    effectBlendOne(); //加算合成Technique
    setZEnable(true);       //Zバッファは考慮有り
    setZWriteEnable(false); //Zバッファは書き込み無し
    defineRotMvWorldMatrix(UTIL::setWorldMatrix_RzBxyzMv); //変換行列をビルボードに
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
