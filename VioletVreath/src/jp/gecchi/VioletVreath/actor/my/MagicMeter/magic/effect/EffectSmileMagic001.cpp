#include "stdafx.h"
#include "EffectSmileMagic001.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoA.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxScaler.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxUvFlipper.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

EffectSmileMagic001::EffectSmileMagic001(const char* prm_name) :
        DefaultSpriteActor(prm_name, "EffectSpeedMagic", nullptr) {
    _class_name = "EffectSmileMagic001";
    effectBlendOne(); //加算合成Technique
    setZEnable(true);       //Zバッファは考慮有り
    setZWriteEnable(false); //Zバッファは書き込み無し
    defineRotMvWorldMatrix(UTIL::setWorldMatrix_RzBxyzMv); //変換行列をビルボードに
    setHitAble(false);
}

void EffectSmileMagic001::initialize() {
    setAlpha(0.9);
    _pUvFlipper->exec(FLIP_ORDER_LOOP, 1);
}

void EffectSmileMagic001::onActive() {
}

void EffectSmileMagic001::processBehavior() {
    _pUvFlipper->behave();
    _pKurokoA->behave();
    _pScaler->behave();
}

void EffectSmileMagic001::processJudgement() {
}

void EffectSmileMagic001::onInactive() {
}

EffectSmileMagic001::~EffectSmileMagic001() {
}
