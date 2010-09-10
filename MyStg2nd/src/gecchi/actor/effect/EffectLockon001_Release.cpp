#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

EffectLockon001_Release::EffectLockon001_Release(const char* prm_name, EffectLockon001* prm_pEffectLockon001) : DefaultSpriteSetActor(prm_name, "8/Lockon001") {
    _class_name = "EffectLockon001_Release";
    inactivateImmediately();
    chengeEffectTechnique("DestBlendOne"); //加算合成
    defineRotMvWorldMatrix(GgafDx9Util::setWorldMatrix_RzBxyzMv); //ビルボードRz回転
    _pEffectLockon001 = prm_pEffectLockon001;
    setHitAble(false); //当たり判定無し

    setZEnable(false);        //Zバッファは考慮無し
    setZWriteEnable(false);  //Zバッファは書き込み無し
    setSpecialDrawDepth(1); //最前面描画。ロックオンエフェクトが隠れないようにするため
}

void EffectLockon001_Release::initialize() {
    _pUvFlipper->copyStatesFrom(_pEffectLockon001->_pUvFlipper);
}

void EffectLockon001_Release::onActive() {
    setAlpha(_pEffectLockon001->getAlpha());
    _pUvFlipper->copyStatesFrom(_pEffectLockon001->_pUvFlipper);
    _pScaler->forceScaleRange(20000, 2000); //スケーリング・範囲
    _pScaler->setScale(_pEffectLockon001->_pScaler->_scale[0]);
    _pScaler->intoTargetScaleLinerUntil(20000, 50);//スケーリング
    _pMover->setFaceAng(AXIS_Z, _pEffectLockon001->_pMover->_angFace[AXIS_Z]);
    _pMover->setFaceAngVelo(AXIS_Z, _pEffectLockon001->_pMover->_angveloFace[AXIS_Z]*-3);        //回転
}

void EffectLockon001_Release::processBehavior() {
    addAlpha(-0.04);
    if (_fAlpha < 0.0f || getActivePartFrame() > 60) {
        inactivate();
    }
    _pUvFlipper->behave();
    _pMover->behave();
    _pScaler->behave();
}

void EffectLockon001_Release::processJudgement() {
//    if (_fAlpha < 0) {
//        inactivate();
//    }
}

void EffectLockon001_Release::onInactive() {
}

EffectLockon001_Release::~EffectLockon001_Release() {
}
