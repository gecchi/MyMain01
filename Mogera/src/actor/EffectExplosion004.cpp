#include "EffectExplosion004.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxScaler.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxUvFlipper.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace Mogera;

EffectExplosion004::EffectExplosion004(const char* prm_name) :
        DefaultMassSpriteActor(prm_name, "EffectExplosion004", nullptr) {
    _class_name = "EffectExplosion004";
    //加算合成Technique指定
//    effectBlendOne();
    //ワールド変換行列はビルボード指定
    defineRotMvWorldMatrix_Billboard();
}

void EffectExplosion004::initialize() {
    getScaler()->setRange(500, 2000);
    setHitAble(false);
}

void EffectExplosion004::onActive() {
    GgafDxUvFlipper* pUvFlipper = getUvFlipper();
    pUvFlipper->setActivePtnToTop();
    pUvFlipper->exec(FLIP_ORDER_NOLOOP, 1);
    setScale(500);
    getScaler()->transitionLinearUntil(2000, 64);
    setCullingDraw(false);
    setAlpha(1.0);
}

void EffectExplosion004::processBehavior() {
    _alpha -= 0.01;
    getUvFlipper()->behave();
    getKuroko()->behave();
    getScaler()->behave();
}

void EffectExplosion004::processJudgement() {
    if (getActiveFrame() > 120) {
        sayonara();
    }
}

EffectExplosion004::~EffectExplosion004() {
}
