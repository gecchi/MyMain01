#include "EffectExplosion001.h"

#include "jp/ggaf/core/actor/SceneMediator.h"
#include "jp/ggaf/core/scene/Scene.h"
#include "jp/ggaf/dx/actor/supporter/Scaler.h"
#include "jp/ggaf/dx/actor/supporter/VecVehicle.h"
#include "jp/ggaf/dx/actor/supporter/UvFlipper.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"

using namespace GgafLib;
using namespace VioletVreath;

EffectExplosion001::EffectExplosion001(const char* prm_name) :
        DefaultMassSpriteActor(prm_name, "EffectExplosion001") {
    _class_name = "EffectExplosion001";
    effectBlendOne(); //加算合成Technique指定
    defineRotMvWorldMatrix_Billboard(); //XYZ軸ビルボード
}

void EffectExplosion001::initialize() {
    setHitAble(false);
}

void EffectExplosion001::onActive() {
    GgafDx::UvFlipper* pUvFlipper = getUvFlipper();
    pUvFlipper->setActivePtnToTop();
    pUvFlipper->exec(FLIP_ORDER_NOLOOP, 1);
    setCullingDraw(false);
    setAlpha(1.0);
    _sx = _sy = _sz = 1000;
}

void EffectExplosion001::processBehavior() {
    addAlpha(-0.03);
    _sx+= 100;
    _sy+= 100;
    getUvFlipper()->behave();
    getVecVehicle()->behave();
    getScaler()->behave();
}

void EffectExplosion001::processJudgement() {
    if (!getUvFlipper()->isFlipping()) {
        //アニメーションが終わったら終了
        sayonara();
    }
}

void EffectExplosion001::onInactive() {
    getVecVehicle()->stop();
}


EffectExplosion001::~EffectExplosion001() {
}
