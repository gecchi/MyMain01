#include "EffectSpeedMagic.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
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
    setZEnableDraw(true);       //描画時、Zバッファ値は考慮される
    setZWriteEnable(false); //自身のZバッファを書き込みしない
    defineRotMvWorldMatrix_Billboard(); //変換行列をビルボードに
    setHitAble(false);
}

void EffectSpeedMagic::initialize() {
    setCullingDraw(false);
    getUvFlipper()->exec(FLIP_ORDER_LOOP, 1);
}

void EffectSpeedMagic::onActive() {
}

void EffectSpeedMagic::processBehavior() {
    getUvFlipper()->behave();
    getKuroko()->behave();
    getScaler()->behave();
}

void EffectSpeedMagic::processJudgement() {
}

void EffectSpeedMagic::onInactive() {
}

EffectSpeedMagic::~EffectSpeedMagic() {
}
