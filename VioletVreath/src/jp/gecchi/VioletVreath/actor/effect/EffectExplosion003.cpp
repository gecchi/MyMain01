#include "stdafx.h"
#include "EffectExplosion003.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxScaler.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxUvFlipper.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

EffectExplosion003::EffectExplosion003(const char* prm_name) :
        DefaultSpriteSetActor(prm_name, "EffectExplosion003", nullptr) {
    _class_name = "EffectExplosion003";
    pScaler_ = NEW GgafDxScaler(this);
    //加算合成Technique指定
    effectBlendOne();
    //ワールド変換行列はビルボード指定
    defineRotMvWorldMatrix(UTIL::setWorldMatrix_RzBxyzMv);
}

void EffectExplosion003::initialize() {
    getUvFlipper()->setFlipPtnRange(0, 63);
    pScaler_->forceRange(500, 2000);
    setHitAble(false);
}

void EffectExplosion003::onActive() {
    GgafDxUvFlipper* pUvFlipper = getUvFlipper();
    pUvFlipper->setActivePtnToTop();
    pUvFlipper->exec(FLIP_ORDER_NOLOOP, 1);
    setScale(500);
    pScaler_->transitionLinerUntil(2000, 64);
    setAlpha(0.99);
}

void EffectExplosion003::processBehavior() {
    _alpha -= 0.01;
    getUvFlipper()->behave();
    getKuroko()->behave();
    pScaler_->behave();
}

void EffectExplosion003::processJudgement() {
    if (_alpha < 0) {
        sayonara();
    }
}

EffectExplosion003::~EffectExplosion003() {
    GGAF_DELETE(pScaler_);
}
