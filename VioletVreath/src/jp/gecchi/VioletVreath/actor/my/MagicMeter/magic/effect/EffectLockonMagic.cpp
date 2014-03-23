#include "stdafx.h"
#include "EffectLockonMagic.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxScaler.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxUvFlipper.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

EffectLockonMagic::EffectLockonMagic(const char* prm_name) :
        DefaultSpriteActor(prm_name, "EffectLockonMagic", nullptr) {
    _class_name = "EffectLockonMagic";
    pScaler_ = NEW GgafDxScaler(this);
    effectBlendOne(); //加算合成Technique
    setZEnable(true);       //Zバッファは考慮有り
    setZWriteEnable(false); //Zバッファは書き込み無し
    defineRotMvWorldMatrix(UTIL::setWorldMatrix_RzBxyzMv); //変換行列をビルボードに
    setHitAble(false);
}

void EffectLockonMagic::initialize() {
    setAlpha(0.9);
    _pUvFlipper->exec(FLIP_ORDER_LOOP, 1);
}

void EffectLockonMagic::onActive() {
}

void EffectLockonMagic::processBehavior() {
    _pUvFlipper->behave();
    getKuroko()->behave();
    pScaler_->behave();
}

void EffectLockonMagic::processJudgement() {
}

void EffectLockonMagic::onInactive() {
}

EffectLockonMagic::~EffectLockonMagic() {
    GGAF_DELETE(pScaler_);
}
