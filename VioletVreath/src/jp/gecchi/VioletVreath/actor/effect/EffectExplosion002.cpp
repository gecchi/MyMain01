#include "EffectExplosion002.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxScaler.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxUvFlipper.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

EffectExplosion002::EffectExplosion002(const char* prm_name) :
        DefaultMassSpriteActor(prm_name, "EffectExplosion002", nullptr) {
    _class_name = "EffectExplosion002";
    effectBlendOne(); //加算合成するTechnique指定
}

void EffectExplosion002::initialize() {
    setHitAble(false);

}

void EffectExplosion002::onActive() {
    GgafDxUvFlipper* pUvFlipper = getUvFlipper();
    pUvFlipper->setActivePtnToTop();
    pUvFlipper->exec(FLIP_ORDER_NOLOOP, 1); //パラパラアニメ無し
    setAlpha(0.99);
    _sx = _sy = _sz = 1000;
}

void EffectExplosion002::processBehavior() {
    _alpha -= 0.03;
    _sx+= 100;
    _sy+= 100;
    getUvFlipper()->behave();
    getKuroko()->behave();
    getScaler()->behave();
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

