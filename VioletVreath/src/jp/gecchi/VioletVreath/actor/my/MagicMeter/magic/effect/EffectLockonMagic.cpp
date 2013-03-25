#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

EffectLockonMagic::EffectLockonMagic(const char* prm_name) :
        DefaultSpriteActor(prm_name, "EffectLockonMagic", nullptr) {
    _class_name = "EffectLockonMagic";
    effectBlendOne(); //加算合成Technique
    setZEnable(true);       //Zバッファは考慮有り
    setZWriteEnable(false); //Zバッファは書き込み無し
    defineRotMvWorldMatrix(UTIL::setWorldMatrix_RzBxyzMv); //変換行列をビルボードに
    setHitAble(false);
}

void EffectLockonMagic::initialize() {
    _pUvFlipper->exec(FLIP_ORDER_LOOP, 1);
}

void EffectLockonMagic::onActive() {
}

void EffectLockonMagic::processBehavior() {
    _pUvFlipper->behave();
    _pKurokoA->behave();
    _pScaler->behave();
}

void EffectLockonMagic::processJudgement() {
}

void EffectLockonMagic::onInactive() {
}


EffectLockonMagic::~EffectLockonMagic() {
}
