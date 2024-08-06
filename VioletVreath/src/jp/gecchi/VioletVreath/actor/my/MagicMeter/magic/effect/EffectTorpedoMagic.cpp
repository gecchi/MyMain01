#include "EffectTorpedoMagic.h"

#include "jp/ggaf/dx/actor/supporter/LocusVehicle.h"
#include "jp/ggaf/dx/actor/supporter/Scaler.h"
#include "jp/ggaf/dx/actor/supporter/UvFlipper.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"



using namespace GgafLib;
using namespace VioletVreath;

EffectTorpedoMagic::EffectTorpedoMagic(const char* prm_name) :
        DefaultSpriteActor(prm_name, "EffectTorpedoMagic") {
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
    getLocusVehicle()->behave();
    getScaler()->behave();
}

void EffectTorpedoMagic::processJudgement() {
}

void EffectTorpedoMagic::onInactive() {
}

EffectTorpedoMagic::~EffectTorpedoMagic() {
}
