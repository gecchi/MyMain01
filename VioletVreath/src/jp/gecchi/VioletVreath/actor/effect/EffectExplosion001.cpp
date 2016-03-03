#include "EffectExplosion001.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxScaler.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxUvFlipper.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

EffectExplosion001::EffectExplosion001(const char* prm_name) :
        DefaultMassSpriteActor(prm_name, "EffectExplosion001", nullptr) {
    _class_name = "EffectExplosion001";
    pScaler_ = NEW GgafDxScaler(this);
    effectBlendOne(); //加算合成Technique指定
    defineRotMvWorldMatrix(UTIL::setWorldMatrix_RzBxyzMv); //XYZ軸ビルボード
}

void EffectExplosion001::initialize() {
    setHitAble(false);
}

void EffectExplosion001::onActive() {
    GgafDxUvFlipper* pUvFlipper = getUvFlipper();
    pUvFlipper->setActivePtnToTop();
    pUvFlipper->exec(FLIP_ORDER_NOLOOP, 1);
    setAlpha(0.99);
    _sx = _sy = _sz = 1000;
}

void EffectExplosion001::processBehavior() {
    _alpha -= 0.03;
    _sx+= 100;
    _sy+= 100;
    getUvFlipper()->behave();
    getKuroko()->behave();
    pScaler_->behave();
}

void EffectExplosion001::processJudgement() {
    if (_alpha < 0) {
        sayonara();
    }
}

void EffectExplosion001::onInactive() {
    getKuroko()->stopMv();
}


EffectExplosion001::~EffectExplosion001() {
    GGAF_DELETE(pScaler_);
}
