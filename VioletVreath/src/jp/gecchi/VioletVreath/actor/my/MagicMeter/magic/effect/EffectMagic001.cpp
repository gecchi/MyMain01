#include "EffectMagic001.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxAxesMover.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

EffectMagic001::EffectMagic001(const char* prm_name)
               : DefaultMeshSetActor(prm_name, "EffectMagic001", nullptr) {
    _class_name = "EffectMagic001";
    effectBlendOne(); //加算合成するTechnique指定
    setZEnableDraw(true);        //描画時、Zバッファ値は考慮される
    setZWriteEnable(false);  //自身のZバッファを書き込みしない
}

void EffectMagic001::initialize() {
    setAlpha(0.9);
//    getUvFlipper()->setFlipPtnRange(0, 63);
    setHitAble(false);
}

void EffectMagic001::onActive() {
    getKuroko()->setRollPitchYawFaceAngVelo(PX_C(3), PX_C(5), PX_C(7));
}

void EffectMagic001::processBehavior() {
    getKuroko()->behave();
}

void EffectMagic001::processJudgement() {
//    if (_alpha < 0) {
//        sayonara();
//    }
}

void EffectMagic001::onInactive() {
}

EffectMagic001::~EffectMagic001() {
}
