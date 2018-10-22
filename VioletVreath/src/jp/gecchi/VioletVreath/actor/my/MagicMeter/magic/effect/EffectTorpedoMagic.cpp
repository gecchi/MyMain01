#include "EffectTorpedoMagic.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxScaler.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxUvFlipper.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

EffectTorpedoMagic::EffectTorpedoMagic(const char* prm_name) :
        DefaultSpriteActor(prm_name, "EffectTorpedoMagic", nullptr) {
    _class_name = "EffectTorpedoMagic";
    effectBlendOne(); //加算合成Technique
    setZEnableDraw(true);       //描画時、Zバッファ値は考慮される
    setZWriteEnable(false); //自身のZバッファを書き込みしない
    defineRotMvWorldMatrix_Billboard(); //変換行列をビルボードに
    setHitAble(false);
}

void EffectTorpedoMagic::initialize() {
    setCullingDraw(false);
    getUvFlipper()->exec(FLIP_ORDER_LOOP, 1);
}

void EffectTorpedoMagic::onActive() {
}

void EffectTorpedoMagic::processBehavior() {
    getUvFlipper()->behave();
    getKuroko()->behave();
    getScaler()->behave();
}

void EffectTorpedoMagic::processJudgement() {
}

void EffectTorpedoMagic::onInactive() {
}

EffectTorpedoMagic::~EffectTorpedoMagic() {
}
