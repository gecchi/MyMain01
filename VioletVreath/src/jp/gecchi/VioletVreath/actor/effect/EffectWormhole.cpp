#include "stdafx.h"
#include "EffectWormhole.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxScaler.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoA.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

EffectWormhole::EffectWormhole(const char* prm_name, const char* prm_model_id) :
        DefaultMorphMeshActor(prm_name, prm_model_id, nullptr) {
    _class_name = "EffectWormhole";
    inactivate();
    effectBlendOne(); //加算合成
    defineRotMvWorldMatrix(UTIL::setWorldMatrix_RzBxyzMv); //ビルボードRz回転
    setHitAble(false); //当たり判定無し
}

void EffectWormhole::initialize() {
}

void EffectWormhole::onActive() {
    setAlpha(0.01);
    _pScaler->forceRange(30000, 1000); //スケーリング・範囲
    _pScaler->setScale(30000);
    _pScaler->scaleLinerUntil(1000, 30);//スケーリング・60F費やして1000に縮小
    _pKurokoA->setFaceAngVelo(AXIS_Z, 1000);        //回転
}

void EffectWormhole::processBehavior() {
    if (getAlpha() < 1.0) {
        addAlpha(0.05);
    }

    if (_pScaler->_method[0] == NOSCALE) {
        //縮小完了後、Beat
        _pScaler->forceRange(1000, 2000);
        _pScaler->beat(30, 2, 2, -1); //無限ループ
    }
    _pKurokoA->behave();
    _pScaler->behave();
}

void EffectWormhole::processJudgement() {
//    if (_alpha < 0) {
//        sayonara();
//    }
}

void EffectWormhole::onInactive() {
}

EffectWormhole::~EffectWormhole() {
}
