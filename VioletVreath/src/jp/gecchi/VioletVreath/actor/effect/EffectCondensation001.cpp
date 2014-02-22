#include "stdafx.h"
#include "EffectCondensation001.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxScaler.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxUvFlipper.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

EffectCondensation001::EffectCondensation001(const char* prm_name) :
        DefaultSpriteSetActor(prm_name, "8/Lockon001", nullptr) {
    _class_name = "EffectCondensation001";
    pScaler_ = NEW GgafDxScaler(this);
    inactivate();
    effectBlendOne(); //加算合成
    defineRotMvWorldMatrix(UTIL::setWorldMatrix_RzBxyzMv); //ビルボードRz回転
    setHitAble(false); //当たり判定無し
}

void EffectCondensation001::initialize() {
    _pUvFlipper->setFlipPtnRange(0, 3);   //アニメ範囲を０～１５
    _pUvFlipper->exec(FLIP_ORDER_LOOP, 5); //アニメ順序

}

void EffectCondensation001::onActive() {
    _pUvFlipper->setActivePtnToTop();
    setAlpha(0.01);
    pScaler_->forceRange(30000, 1000); //スケーリング・範囲
    setScale(30000);
    pScaler_->transitionLinerUntil(1000, 30);//スケーリング・60F費やして1000に縮小
    _pKuroko->setFaceAngVelo(AXIS_Z, 1000);        //回転
}

void EffectCondensation001::processBehavior() {
    if (getAlpha() < 1.0) {
        addAlpha(0.05);
    }

    if (pScaler_->_method[0] == NOSCALE) {
        //縮小完了後、Beat
        pScaler_->forceRange(1000, 2000);
        pScaler_->beat(30, 2, 0, 26, -1); //無限ループ
    }
    _pUvFlipper->behave();
    _pKuroko->behave();
    pScaler_->behave();
}

void EffectCondensation001::processJudgement() {
//    if (_alpha < 0) {
//        sayonara();
//    }
}

void EffectCondensation001::onInactive() {
}

EffectCondensation001::~EffectCondensation001() {
    GGAF_DELETE(pScaler_);
}

