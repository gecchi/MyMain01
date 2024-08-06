#include "EffectTurbo002.h"

#include "jp/ggaf/dx/actor/supporter/Scaler.h"
#include "jp/ggaf/dx/actor/supporter/LocusVehicle.h"
#include "jp/ggaf/dx/actor/supporter/UvFlipper.h"



using namespace GgafLib;
using namespace VioletVreath;

EffectTurbo002::EffectTurbo002(const char* prm_name) :
        DefaultSpriteActor(prm_name, "Turbo002") {
    _class_name = "EffectTurbo002";
    inactivate();
    effectBlendOne(); //加算合成
    setHitAble(false); //当たり判定無し
}

void EffectTurbo002::initialize() {
    GgafDx::UvFlipper* pUvFlipper = getUvFlipper();
    pUvFlipper->setFlipPtnRange(0, 0);   //アニメ範囲を０～１５
    pUvFlipper->exec(FLIP_ORDER_LOOP, 2); //アニメ順序
}

void EffectTurbo002::onActive() {
    getUvFlipper()->setActivePtnToTop();
    setAlpha(0.4);
    getScaler()->setRange(100000, 1000); //スケーリング・範囲
    setScale(1000);
    getScaler()->transitionLinearUntil(100000, 60);//スケーリング・60F費やして1000に縮小
    setRyFaceAng(D90ANG);
    getLocusVehicle()->setFaceAngVelo(AXIS_Z, 2000);
}

void EffectTurbo002::processBehavior() {
    addAlpha(-(1.0/60.0));
    getUvFlipper()->behave();
    getLocusVehicle()->behave();
    getScaler()->behave();
}

void EffectTurbo002::processJudgement() {
    if (!getScaler()->isTransitioning()) {
        inactivate();
    }
}

void EffectTurbo002::onInactive() {
}

EffectTurbo002::~EffectTurbo002() {
}
