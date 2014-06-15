#include "stdafx.h"
#include "EffectEntry002.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxScaler.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

EffectEntry002::EffectEntry002(const char* prm_name) :
        EffectEntry(prm_name, "EffectEntry002") {
    _class_name = "EffectEntry002";
    effectBlendOne();
    setZEnable(false);
    setZWriteEnable(false);
//    defineRotMvWorldMatrix(UTIL::setWorldMatrix_RzBxyzMv); //ビルボードRz回転
}

void EffectEntry002::initialize() {
    EffectEntry::initialize();
    //getUvFlipper()->exec(FLIP_ORDER_LOOP, 1);
    setAlpha(0.99);
}

void EffectEntry002::onActive() {
    EffectEntry::onActive();
    //getUvFlipper()->setActivePtnToTop();
    getKuroko()->setFaceAngVelo(AXIS_Z, 4000);
}

void EffectEntry002::processBehavior() {
    EffectEntry::processBehavior();
    getKuroko()->behave();
}

EffectEntry002::~EffectEntry002() {
}
