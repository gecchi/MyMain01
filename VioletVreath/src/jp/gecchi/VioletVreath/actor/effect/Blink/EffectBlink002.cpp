#include "EffectBlink002.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxScaler.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

EffectBlink002::EffectBlink002(const char* prm_name) :
        EffectBlink(prm_name, "EffectBlink002") {
    _class_name = "EffectBlink002";
    effectBlendOne();
    setZWriteEnable(false);
//    defineRotMvWorldMatrix(UTIL::setWorldMatrix_RzBxyzMv); //ビルボードRz回転
}

void EffectBlink002::initialize() {
    EffectBlink::initialize();
    //getUvFlipper()->exec(FLIP_ORDER_LOOP, 1);
    setAlpha(0.99);
}

void EffectBlink002::onActive() {
    EffectBlink::onActive();
    //getUvFlipper()->setActivePtnToTop();
    getKuroko()->setFaceAngVelo(AXIS_Z, 4000);
}

void EffectBlink002::processBehavior() {
    EffectBlink::processBehavior();
    getKuroko()->behave();
}

EffectBlink002::~EffectBlink002() {
}
