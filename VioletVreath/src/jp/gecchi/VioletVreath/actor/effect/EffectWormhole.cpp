#include "EffectWormhole.h"

#include "jp/ggaf/dx/actor/supporter/Scaler.h"
#include "jp/ggaf/dx/actor/supporter/LocusVehicle.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"



using namespace GgafLib;
using namespace VioletVreath;

EffectWormhole::EffectWormhole(const char* prm_name, const char* prm_model) :
        VvEffectActor<DefaultMorphMeshActor>(prm_name, prm_model) {
    _class_name = "EffectWormhole";
    inactivate();
    effectBlendOne(); //加算合成
    defineRotMvWorldMatrix_Billboard(); //ビルボードRz回転
    setHitAble(false); //当たり判定無し
}

void EffectWormhole::initialize() {
}

void EffectWormhole::onActive() {
    setAlpha(0.01);
    getScaler()->setRange(30000, 1000); //スケーリング・範囲
    setScale(30000);
    getScaler()->transitionLinearUntil(1000, 30);//スケーリング・60F費やして1000に縮小
    getLocusVehicle()->setFaceAngVelo(AXIS_Z, 1000);        //回転
}

void EffectWormhole::processBehavior() {
    GgafDx::Scaler* const pScaler = getScaler();

    if (getAlpha() < 1.0) {
        addAlpha(0.05);
    }

    if (!pScaler->isTransitioning()) {
        //縮小完了後、Beat
        pScaler->setRange(1000, 2000);
        pScaler->beat(30, 2, 0, 26, -1); //無限ループ
    }
    getLocusVehicle()->behave();
    pScaler->behave();
}

void EffectWormhole::processJudgement() {
}

void EffectWormhole::onInactive() {
}

EffectWormhole::~EffectWormhole() {
}
