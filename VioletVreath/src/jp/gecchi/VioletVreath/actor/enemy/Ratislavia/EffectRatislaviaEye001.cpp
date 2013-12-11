#include "stdafx.h"
#include "EffectRatislaviaEye001.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxScaler.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

EffectRatislaviaEye001::EffectRatislaviaEye001(const char* prm_name) :
        DefaultSpriteActor(prm_name, "EffectRatislaviaEye001", nullptr) {
    _class_name = "EffectRatislaviaEye001";
    pScaler_ = NEW GgafDxScaler(this);
    inactivate();
    effectBlendOne(); //加算合成
    setHitAble(false); //当たり判定無し
    cnt_ = 0;
}

void EffectRatislaviaEye001::initialize() {
}

void EffectRatislaviaEye001::onActive() {
    cnt_ = 0;
    pScaler_->forceRange(100000, 1); //スケーリング・範囲
    pScaler_->setScale(100000);
    pScaler_->beat(30, 0, 0, 3);
}

void EffectRatislaviaEye001::processBehavior() {
    pScaler_->behave();
    setAlpha( 1.3 - (pScaler_->_scale[0] / 100000.0 ) );
}

void EffectRatislaviaEye001::processJudgement() {
    if (pScaler_->_method[0] == NOSCALE) {
        inactivate();
    }
}

void EffectRatislaviaEye001::onInactive() {
}

EffectRatislaviaEye001::~EffectRatislaviaEye001() {
    GGAF_DELETE(pScaler_);
}
