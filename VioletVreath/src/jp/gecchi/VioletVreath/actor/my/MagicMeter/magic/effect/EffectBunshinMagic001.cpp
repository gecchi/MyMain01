#include "EffectBunshinMagic001.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxAxesMover.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxScaler.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

EffectBunshinMagic001::EffectBunshinMagic001(const char* prm_name)
               : EffectBlink(prm_name, "EffectBunshinMagic001") {
    _class_name = "EffectBunshinMagic001";
    pAxsMver_ = NEW GgafDxAxesMover(this);
    effectBlendOne(); //加算合成するTechnique指定
    setZEnable(true);        //Zバッファは考慮有り
    setZWriteEnable(false);  //Zバッファは書き込み無し
}

void EffectBunshinMagic001::initialize() {
    setAlpha(0.9);
    pScaler_->setRange(0, R_SC(4.0));
}

void EffectBunshinMagic001::onActive() {
    EffectBlink::onActive();
    getKuroko()->setRollPitchYawFaceAngVelo(PX_C(3), PX_C(5), PX_C(7));
}

void EffectBunshinMagic001::processBehavior() {
    EffectBlink::processBehavior();
    getKuroko()->behave();
    pAxsMver_->behave();
}

void EffectBunshinMagic001::processJudgement() {
    EffectBlink::processJudgement();
//    if (_alpha < 0) {
//        sayonara();
//    }
}

void EffectBunshinMagic001::onInactive() {
    EffectBlink::onInactive();
}

EffectBunshinMagic001::~EffectBunshinMagic001() {
    GGAF_DELETE(pAxsMver_);
}
