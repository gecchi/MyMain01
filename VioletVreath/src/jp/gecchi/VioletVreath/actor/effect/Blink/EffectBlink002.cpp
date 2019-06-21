#include "EffectBlink002.h"

#include "jp/ggaf/dx/actor/supporter/Rikisha.h"



using namespace GgafLib;
using namespace VioletVreath;

EffectBlink002::EffectBlink002(const char* prm_name) :
        EffectBlink(prm_name, "EffectBlink002") {
    _class_name = "EffectBlink002";
    effectBlendOne();
    setZWriteEnable(false);
//    defineRotMvWorldMatrix_Billboard(); //�r���{�[�hRz��]
}

void EffectBlink002::initialize() {
    EffectBlink::initialize();
    //getUvFlipper()->exec(FLIP_ORDER_LOOP, 1);
    setCullingDraw(false);
}

void EffectBlink002::onActive() {
    EffectBlink::onActive();
    //getUvFlipper()->setActivePtnToTop();
    callRikisha()->setFaceAngVelo(AXIS_Z, 4000);
}

void EffectBlink002::processBehavior() {
    EffectBlink::processBehavior();
    callRikisha()->behave();
}

EffectBlink002::~EffectBlink002() {
}
