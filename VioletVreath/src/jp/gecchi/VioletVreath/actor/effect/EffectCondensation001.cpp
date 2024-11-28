#include "EffectCondensation001.h"

#include "jp/ggaf/dx/actor/supporter/LocusVehicle.h"
#include "jp/ggaf/dx/actor/supporter/Scaler.h"
#include "jp/ggaf/dx/actor/supporter/UvFlipper.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"

using namespace GgafLib;
using namespace VioletVreath;

EffectCondensation001::EffectCondensation001(const char* prm_name) :
        VvEffectActor<DefaultSpriteSetActor>(prm_name, "Lockon001") {
    _class_name = "EffectCondensation001";
    inactivate();
    effectBlendOne(); //加算合成
    defineRotMvWorldMatrix_Billboard(); //ビルボードRz回転
    setHitAble(false); //当たり判定無し
}

void EffectCondensation001::initialize() {
    GgafDx::UvFlipper* pUvFlipper = getUvFlipper();
    pUvFlipper->setFlipPtnRange(0, 3);   //アニメ範囲を０～１５
    pUvFlipper->exec(FLIP_ORDER_LOOP, 5); //アニメ順序
}

void EffectCondensation001::onActive() {
    getUvFlipper()->setActivePtnToTop();
    setAlpha(0.01);
    getScaler()->setRange(30000, 1000); //スケーリング・範囲
    setScale(30000);
    getScaler()->transitionLinearUntil(1000, 30);//スケーリング・60F費やして1000に縮小
    getLocusVehicle()->setFaceAngVelo(AXIS_Z, 1000);        //回転
}

void EffectCondensation001::processBehavior() {
    GgafDx::Scaler* const pScaler = getScaler();

    if (getAlpha() < 1.0) {
        addAlpha(0.05);
    }

    if (!pScaler->isTransitioning()) {
        //縮小完了後、Beat
        pScaler->setRange(1000, 2000);
        pScaler->beat(30, 2, 0, 26, -1); //無限ループ
    }
    getUvFlipper()->behave();
    getLocusVehicle()->behave();
    pScaler->behave();
}

void EffectCondensation001::processJudgement() {
}

void EffectCondensation001::onInactive() {
}

EffectCondensation001::~EffectCondensation001() {
}

