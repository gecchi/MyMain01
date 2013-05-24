#include "stdafx.h"
#include "EffectExplosion002.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxScaler.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoA.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxUvFlipper.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

EffectExplosion002::EffectExplosion002(const char* prm_name) :
        DefaultSpriteSetActor(prm_name, "EffectExplosion002", nullptr) {
    _class_name = "EffectExplosion002";
    effectBlendOne(); //加算合成するTechnique指定
}

void EffectExplosion002::initialize() {
    _pUvFlipper->setFlipPtnRange(0, 15);
    setHitAble(false);

}

void EffectExplosion002::onActive() {
    _pUvFlipper->setActivePtnToTop();
    _pUvFlipper->exec(FLIP_ORDER_NOLOOP, 1); //パラパラアニメ無し
    _alpha = 0.99;
    _SX = _SY = _SZ = 1000;
}

void EffectExplosion002::processBehavior() {
    _alpha -= 0.03;
    _SX+= 100;
    _SY+= 100;
    _pUvFlipper->behave();
    _pKurokoA->behave();
    _pScaler->behave();
}

void EffectExplosion002::processJudgement() {
    if (_alpha < 0) {
        sayonara();
    }
}

void EffectExplosion002::onInactive() {
}

EffectExplosion002::~EffectExplosion002() {
}
