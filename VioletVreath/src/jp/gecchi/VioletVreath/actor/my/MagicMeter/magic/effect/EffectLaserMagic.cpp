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
    setZEnableDraw(true);       //描画時、Zバッファ値は考慮される
    setZWriteEnable(false); //自身のZバッファを書き込みしない
    defineRotMvWorldMatrix(UTIL::setWorldMatrix_RzBxyzMv); //変換行列をビルボードに
    setHitAble(false);
}

void EffectLaserMagic::initialize() {
    setAlpha(0.9);
    getUvFlipper()->exec(FLIP_ORDER_LOOP, 1);
}

void EffectLaserMagic::onActive() {
}

void EffectLaserMagic::processBehavior() {
    getUvFlipper()->behave();
    getKuroko()->behave();
    getScaler()->behave();
}

void EffectLaserMagic::processJudgement() {
}

void EffectLaserMagic::onInactive() {
}

EffectLaserMagic::~EffectLaserMagic() {
}
