#include "EffectBunshinMagic001.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxTrucker.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxScaler.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

EffectBunshinMagic001::EffectBunshinMagic001(const char* prm_name)
               : EffectBlink(prm_name, "EffectBunshinMagic001") {
    _class_name = "EffectBunshinMagic001";
    effectBlendOne(); //加算合成するTechnique指定
    setZEnableDraw(true);        //描画時、Zバッファ値は考慮される
    setZWriteEnable(false);  //自身のZバッファを書き込みしない
}

void EffectBunshinMagic001::initialize() {
    setCullingDraw(false);
    getScaler()->setRange(0, R_SC(4.0));
}

void EffectBunshinMagic001::onActive() {
    EffectBlink::onActive();
    getKuroko()->setRollPitchYawFaceAngVelo(PX_C(3), PX_C(5), PX_C(7));
}

void EffectBunshinMagic001::processBehavior() {
    EffectBlink::processBehavior();
    getKuroko()->behave();
    getTrucker()->behave();
}

void EffectBunshinMagic001::processJudgement() {
    EffectBlink::processJudgement();
}

void EffectBunshinMagic001::onInactive() {
    EffectBlink::onInactive();
}

EffectBunshinMagic001::~EffectBunshinMagic001() {
}
