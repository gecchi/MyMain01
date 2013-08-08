#include "stdafx.h"
#include "EffectSpeedMagic.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoA.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxScaler.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxUvFlipper.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"

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
    setAlpha(0.9);
    _pUvFlipper->exec(FLIP_ORDER_LOOP, 1);
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
