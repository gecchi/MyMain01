#include "EffectLaserMagic.h"

#include "jp/ggaf/dx/actor/supporter/LocusVehicle.h"
#include "jp/ggaf/dx/actor/supporter/Scaler.h"
#include "jp/ggaf/dx/actor/supporter/UvFlipper.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"



using namespace GgafLib;
using namespace VioletVreath;

EffectLaserMagic::EffectLaserMagic(const char* prm_name) :
        DefaultSpriteActor(prm_name, "EffectLaserMagic") {
    _class_name = "EffectLaserMagic";
    effectBlendOne(); //加算合成Technique
    useZBufferDrawing(true);       //描画時、Zバッファ値は考慮される
    setZBufferWriteEnable(false); //自身のZバッファを書き込みしない
    defineRotMvWorldMatrix_Billboard(); //変換行列をビルボードに
    setHitAble(false);
}

void EffectLaserMagic::initialize() {
    setCullingDraw(false);
    getUvFlipper()->exec(FLIP_ORDER_LOOP, 1);
}

void EffectLaserMagic::onActive() {
}

void EffectLaserMagic::processBehavior() {
    getUvFlipper()->behave();
    getLocusVehicle()->behave();
    getScaler()->behave();
}

void EffectLaserMagic::processJudgement() {
}

void EffectLaserMagic::onInactive() {
}

EffectLaserMagic::~EffectLaserMagic() {
}
