#include "EffectExplosion002.h"

#include "jp/ggaf/dx/actor/supporter/Scaler.h"
#include "jp/ggaf/dx/actor/supporter/VecVehicle.h"
#include "jp/ggaf/dx/actor/supporter/UvFlipper.h"



using namespace GgafLib;
using namespace VioletVreath;

EffectExplosion002::EffectExplosion002(const char* prm_name) :
        DefaultMassSpriteActor(prm_name, "EffectExplosion002") {
    _class_name = "EffectExplosion002";
    effectBlendOne(); //加算合成するTechnique指定
}

void EffectExplosion002::initialize() {
    setHitAble(false);
}

void EffectExplosion002::onActive() {
    GgafDx::UvFlipper* pUvFlipper = getUvFlipper();
    pUvFlipper->setActivePtnToTop();
    pUvFlipper->exec(FLIP_ORDER_NOLOOP, 1); //パラパラアニメ無し
    setCullingDraw(false);
    setAlpha(1.0);
    _sx = _sy = _sz = 1000;
}

void EffectExplosion002::processBehavior() {
    addAlpha(-0.03);
    _sx+= 100;
    _sy+= 100;
    getUvFlipper()->behave();
    getVecVehicle()->behave();
    getScaler()->behave();
}

void EffectExplosion002::processJudgement() {
    if (!getUvFlipper()->isFlipping()) {
        //アニメーションが終わったら終了
        sayonara();
    }
}

void EffectExplosion002::onInactive() {
}

EffectExplosion002::~EffectExplosion002() {
}

