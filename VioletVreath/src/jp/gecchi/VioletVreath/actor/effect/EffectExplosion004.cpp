#include "EffectExplosion004.h"

#include "jp/ggaf/core/actor/SceneChief.h"
#include "jp/ggaf/core/scene/Scene.h"
#include "jp/ggaf/dx/actor/supporter/Scaler.h"
#include "jp/ggaf/dx/actor/supporter/LocoVehicle.h"
#include "jp/ggaf/dx/actor/supporter/UvFlipper.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"



using namespace GgafLib;
using namespace VioletVreath;

EffectExplosion004::EffectExplosion004(const char* prm_name) :
        DefaultMassSpriteActor(prm_name, "EffectExplosion004") {
    _class_name = "EffectExplosion004";
    //加算合成Technique指定
    effectBlendOne();
    //ワールド変換行列はビルボード指定
    defineRotMvWorldMatrix_Billboard();
}

void EffectExplosion004::initialize() {
    getScaler()->setRange(500, 2000);
    setHitAble(false);
}

void EffectExplosion004::onActive() {
    GgafDx::UvFlipper* pUvFlipper = getUvFlipper();
    pUvFlipper->setActivePtnToTop();
    pUvFlipper->exec(FLIP_ORDER_NOLOOP, 1);
    setScale(500);
    getScaler()->transitionLinearUntil(2000, 64);
    setCullingDraw(false);
    setAlpha(1.0);
}

void EffectExplosion004::processBehavior() {
    addAlpha(-0.03);
    getUvFlipper()->behave();
    getLocoVehicle()->behave();
    getScaler()->behave();
}

void EffectExplosion004::processJudgement() {
    if (!getUvFlipper()->isFlipping()) {
        //アニメーションが終わったら終了
        sayonara();
    }
}

EffectExplosion004::~EffectExplosion004() {
}
