#include "stdafx.h"
#include "EffectOptionMagic001.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxAxesMover.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

EffectOptionMagic001::EffectOptionMagic001(const char* prm_name)
               : DefaultMeshSetActor(prm_name, "EffectOptionMagic001", nullptr) {
    _class_name = "EffectOptionMagic001";
    pAxsMver_ = NEW GgafDxAxesMover(this);
    effectBlendOne(); //加算合成するTechnique指定
    setZEnable(true);        //Zバッファは考慮有り
    setZWriteEnable(false);  //Zバッファは書き込み無し
}

void EffectOptionMagic001::initialize() {
    setAlpha(0.9);
//    _pUvFlipper->setFlipPtnRange(0, 63);
    setHitAble(false);
}

void EffectOptionMagic001::onActive() {
    getKuroko()->setFaceAngVelo(PX_C(3), PX_C(5), PX_C(7));
}

void EffectOptionMagic001::processBehavior() {
    getKuroko()->behave();
    pAxsMver_->behave();
}

void EffectOptionMagic001::processJudgement() {
//    if (_alpha < 0) {
//        sayonara();
//    }
}

void EffectOptionMagic001::onInactive() {
}

EffectOptionMagic001::~EffectOptionMagic001() {
    GGAF_DELETE(pAxsMver_);
}
