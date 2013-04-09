#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

EffectWormhole001::EffectWormhole001(const char* prm_name) :
        EffectWormhole(prm_name, "8/EffectWormhole001") {
    _class_name = "EffectWormhole001";
    inactivateImmed();
    effectBlendOne(); //加算合成
    defineRotMvWorldMatrix(UTIL::setWorldMatrix_RzBxyzMv); //ビルボードRz回転
    setHitAble(false); //当たり判定無し
}

void EffectWormhole001::initialize() {
}

void EffectWormhole001::onActive() {
    setAlpha(0.01);
    _pScaler->forceRange(30000, 1000); //スケーリング・範囲
    _pScaler->setScale(30000);
    _pScaler->scaleLinerUntil(1000, 30);//スケーリング・60F費やして1000に縮小
    _pKurokoA->setFaceAngVelo(AXIS_Z, 1000);        //回転
}

void EffectWormhole001::processBehavior() {
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

void EffectWormhole001::processJudgement() {
//    if (_alpha < 0) {
//        sayonara();
//    }
}

void EffectWormhole001::onInactive() {
}

EffectWormhole001::~EffectWormhole001() {
}
