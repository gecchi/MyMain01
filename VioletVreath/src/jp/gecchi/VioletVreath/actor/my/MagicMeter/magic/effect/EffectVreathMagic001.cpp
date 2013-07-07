#include "stdafx.h"
#include "EffectVreathMagic001.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoA.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxScaler.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxUvFlipper.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

EffectVreathMagic001::EffectVreathMagic001(const char* prm_name) :
        DefaultSpriteActor(prm_name, "EffectSpeedMagic", nullptr) {
    _class_name = "EffectVreathMagic001";
    effectBlendOne(); //加算合成Technique
    setZEnable(true);       //Zバッファは考慮有り
    setZWriteEnable(false); //Zバッファは書き込み無し
    defineRotMvWorldMatrix(UTIL::setWorldMatrix_RzBxyzMv); //変換行列をビルボードに
    setHitAble(false);
}

void EffectVreathMagic001::initialize() {
    _pUvFlipper->exec(FLIP_ORDER_LOOP, 1);
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
