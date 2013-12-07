#include "stdafx.h"
#include "EffectLaserMagic.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxScaler.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxUvFlipper.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

EffectLaserMagic::EffectLaserMagic(const char* prm_name) :
        DefaultSpriteActor(prm_name, "EffectLaserMagic", nullptr) {
    _class_name = "EffectLaserMagic";
    effectBlendOne(); //加算合成Technique
    setZEnable(true);       //Zバッファは考慮有り
    setZWriteEnable(false); //Zバッファは書き込み無し
    defineRotMvWorldMatrix(UTIL::setWorldMatrix_RzBxyzMv); //変換行列をビルボードに
    setHitAble(false);
}

void EffectLaserMagic::initialize() {
    setAlpha(0.9);
    _pUvFlipper->exec(FLIP_ORDER_LOOP, 1);
}

void EffectLaserMagic::onActive() {
}

void EffectLaserMagic::processBehavior() {
    _pUvFlipper->behave();
    _pKuroko->behave();
    _pScaler->behave();
}

void EffectLaserMagic::processJudgement() {
}

void EffectLaserMagic::onInactive() {
}

EffectLaserMagic::~EffectLaserMagic() {
}
