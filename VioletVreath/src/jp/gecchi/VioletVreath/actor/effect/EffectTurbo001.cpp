#include "EffectTurbo001.h"

#include "jp/ggaf/dx/actor/supporter/Scaler.h"
#include "jp/ggaf/dx/actor/supporter/VecVehicle.h"
#include "jp/ggaf/dx/actor/supporter/UvFlipper.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/gecchi/VioletVreath/Caretaker.h"



using namespace GgafLib;
using namespace VioletVreath;

EffectTurbo001::EffectTurbo001(const char* prm_name) :
        DefaultSpriteActor(prm_name, "Turbo001") {
    _class_name = "EffectTurbo001";
    inactivate();
    effectBlendOne(); //加算合成
    defineRotMvWorldMatrix_Billboard(); //ビルボードRz回転
    setHitAble(false); //当たり判定無し
}

void EffectTurbo001::initialize() {
    GgafDx::UvFlipper* pUvFlipper = getUvFlipper();
    pUvFlipper->exec(FLIP_ORDER_LOOP, 1); //アニメ順序
    setCullingDraw(false);
}

void EffectTurbo001::onActive() {
    getUvFlipper()->setActivePtnToTop();
    getVecVehicle()->setFaceAngVelo(AXIS_Z, 3000);        //回転
}

void EffectTurbo001::processBehavior() {
    getUvFlipper()->behave();
    getVecVehicle()->behave();
    getScaler()->behave();
    if (VB_PLAY->isPressed(0, VB_TURBO)) { //ターボ

    } else {
        inactivate();
    }
}

void EffectTurbo001::processJudgement() {

}

void EffectTurbo001::onInactive() {
}

EffectTurbo001::~EffectTurbo001() {
}
