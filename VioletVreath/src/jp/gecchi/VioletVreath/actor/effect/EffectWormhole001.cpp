#include "EffectWormhole001.h"

#include "jp/ggaf/dx/actor/supporter/Scaler.h"
#include "jp/ggaf/dx/actor/supporter/LocoVehicle.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"



using namespace GgafLib;
using namespace VioletVreath;

EffectWormhole001::EffectWormhole001(const char* prm_name) :
        EffectWormhole(prm_name, "EffectWormhole001_8") {
    _class_name = "EffectWormhole001";
    inactivate();
    effectBlendOne(); //加算合成
    defineRotMvWorldMatrix_Billboard(); //ビルボードRz回転
    setHitAble(false); //当たり判定無し
}

void EffectWormhole001::initialize() {
}

void EffectWormhole001::onActive() {
    setAlpha(0.01);
    getScaler()->setRange(30000, 1000); //スケーリング・範囲
    setScale(30000);
    getScaler()->transitionLinearUntil(1000, 30);//スケーリング・60F費やして1000に縮小
    getLocoVehicle()->setFaceAngVelo(AXIS_Z, 1000);        //回転
}

void EffectWormhole001::processBehavior() {
    if (getAlpha() < 1.0) {
        addAlpha(0.05);
    }
    GgafDx::Scaler* pScaler = getScaler();
    if (!pScaler->isTransitioning()) {
        //縮小完了後、Beat
        pScaler->setRange(1000, 2000);
        pScaler->beat(30, 2, 0, 26, -1); //無限ループ
    }
    getLocoVehicle()->behave();
    pScaler->behave();
}

void EffectWormhole001::processJudgement() {
}

void EffectWormhole001::onInactive() {
}

EffectWormhole001::~EffectWormhole001() {
}
