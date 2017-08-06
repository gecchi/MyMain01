#include "EffectWormhole.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxScaler.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

EffectWormhole::EffectWormhole(const char* prm_name, const char* prm_model_id) :
        DefaultMorphMeshActor(prm_name, prm_model_id, nullptr) {
    _class_name = "EffectWormhole";
    pScaler_ = NEW GgafDxScaler(this);
    inactivate();
    effectBlendOne(); //加算合成
    defineRotMvWorldMatrix(UTIL::setWorldMatrix_RzBxyzMv); //ビルボードRz回転
    setHitAble(false); //当たり判定無し
}

void EffectWormhole::initialize() {
}

void EffectWormhole::onActive() {
    setAlpha(0.01);
    pScaler_->setRange(30000, 1000); //スケーリング・範囲
    setScale(30000);
    pScaler_->transitionLinearUntil(1000, 30);//スケーリング・60F費やして1000に縮小
    getKuroko()->setFaceAngVelo(AXIS_Z, 1000);        //回転
}

void EffectWormhole::processBehavior() {
    if (getAlpha() < 1.0) {
        addAlpha(0.05);
    }

    if (!pScaler_->isTransitioning()) {
        //縮小完了後、Beat
        pScaler_->setRange(1000, 2000);
        pScaler_->beat(30, 2, 0, 26, -1); //無限ループ
    }
    getKuroko()->behave();
    pScaler_->behave();
}

void EffectWormhole::processJudgement() {
//    if (_alpha < 0) {
//        sayonara();
//    }
}

void EffectWormhole::onInactive() {
}

EffectWormhole::~EffectWormhole() {
    GGAF_DELETE(pScaler_);
}
