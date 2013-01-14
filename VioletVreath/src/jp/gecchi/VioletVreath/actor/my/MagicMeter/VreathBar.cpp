#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

VreathBar::VreathBar(const char* prm_name, AmountGraph* prm_pAmount)
      : GraphBar(prm_name, "TurboMeter", prm_pAmount) {
    _class_name = "VreathBar";
    pAmount_ = prm_pAmount;
    _Z = 4;
}

void VreathBar::initialize() {
    _pUvFlipper->setFlipMethod(FLIP_ORDER_LOOP, 10); //ƒAƒjƒ‡˜
}

void VreathBar::onReset() {
    _SX = R_SC(pAmount_->getPx() * rate_org_width_); //‰¡•ûŒü‚É”{—¦‚ÅL‚Î‚·
}

void VreathBar::onActive() {
}

void VreathBar::processBehavior() {
    _SX = R_SC(pAmount_->getPx() * rate_org_width_); //‰¡•ûŒü‚É”{—¦‚ÅL‚Î‚·
    _pUvFlipper->behave();
}


void VreathBar::processJudgement() {
}

void VreathBar::onInactive() {
}

VreathBar::~VreathBar() {
}
