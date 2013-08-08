#include "stdafx.h"
#include "EffectMagic001.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoA.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoB.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

EffectMagic001::EffectMagic001(const char* prm_name)
               : DefaultMeshSetActor(prm_name, "EffectMagic001", nullptr) {
    _class_name = "EffectMagic001";
    effectBlendOne(); //加算合成するTechnique指定
    setZEnable(true);        //Zバッファは考慮有り
    setZWriteEnable(false);  //Zバッファは書き込み無し
}

void EffectMagic001::initialize() {
    setAlpha(0.9);
//    _pUvFlipper->setFlipPtnRange(0, 63);
    setHitAble(false);
}

void EffectMagic001::onActive() {
    _pKurokoA->setFaceAngVelo(PX_C(3), PX_C(5), PX_C(7));
}

void EffectMagic001::processBehavior() {
    _pKurokoA->behave();
    _pKurokoB->behave();
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
