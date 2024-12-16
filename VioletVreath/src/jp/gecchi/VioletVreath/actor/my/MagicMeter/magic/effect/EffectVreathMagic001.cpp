#include "EffectVreathMagic001.h"

#include "jp/ggaf/dx/actor/supporter/LocusVehicle.h"
#include "jp/ggaf/dx/actor/supporter/Scaler.h"
#include "jp/ggaf/dx/actor/supporter/UvFlipper.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"



using namespace GgafLib;
using namespace VioletVreath;

EffectVreathMagic001::EffectVreathMagic001(const char* prm_name) :
        DefaultSpriteActor(prm_name, "EffectSpeedMagic") {
    _class_name = "EffectVreathMagic001";
    effectBlendOne(); //加算合成Technique
    useZBufferDrawing(true);       //描画時、Zバッファ値は考慮される
    setZBufferWriteEnable(false); //自身のZバッファを書き込みしない
    defineRotMvWorldMatrix_Billboard(); //変換行列をビルボードに
    setHitAble(false);
}

void EffectVreathMagic001::initialize() {
    setCullingDraw(false);
    getUvFlipper()->exec(FLIP_ORDER_LOOP, 1);
}

void EffectVreathMagic001::onActive() {
}

void EffectVreathMagic001::processBehavior() {
    getUvFlipper()->behave();
    getLocusVehicle()->behave();
    getScaler()->behave();
}

void EffectVreathMagic001::processJudgement() {
}

void EffectVreathMagic001::onInactive() {
}

EffectVreathMagic001::~EffectVreathMagic001() {
}
