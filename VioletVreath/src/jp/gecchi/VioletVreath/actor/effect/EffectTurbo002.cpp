#include "stdafx.h"
#include "EffectTurbo002.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxScaler.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxUvFlipper.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

EffectTurbo002::EffectTurbo002(const char* prm_name) :
        DefaultSpriteActor(prm_name, "Turbo002", nullptr) {
    _class_name = "EffectTurbo002";
    inactivate();
    effectBlendOne(); //加算合成
    setHitAble(false); //当たり判定無し
}

void EffectTurbo002::initialize() {
    _pUvFlipper->setFlipPtnRange(0, 0);   //アニメ範囲を０～１５
    _pUvFlipper->exec(FLIP_ORDER_LOOP, 2); //アニメ順序

}

void EffectTurbo002::onActive() {
    _pUvFlipper->setActivePtnToTop();
    setAlpha(0.4);
    _pScaler->forceRange(100000, 1000); //スケーリング・範囲
    _pScaler->setScale(1000);
    _pScaler->scaleLinerUntil(100000, 60);//スケーリング・60F費やして1000に縮小
    _pKuroko->setFaceAng(AXIS_Y, D90ANG);
    _pKuroko->setFaceAngVelo(AXIS_Z, 2000);
}

void EffectTurbo002::processBehavior() {
    addAlpha(-(1.0/60.0));
    _pUvFlipper->behave();
    _pKuroko->behave();
    _pScaler->behave();
}

void EffectTurbo002::processJudgement() {
    if (_pScaler->_method[0] == NOSCALE) {
        inactivate();
    }
}

void EffectTurbo002::onInactive() {
}

EffectTurbo002::~EffectTurbo002() {
}
