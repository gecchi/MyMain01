#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

EnergyBar::EnergyBar(const char* prm_name, AmountGraph* prm_pAmount)
      : GraphBar(prm_name, "TurboMeter", prm_pAmount) {
    _class_name = "EnergyBar";
}

void EnergyBar::initialize() {
    _pUvFlipper->exec(FLIP_ORDER_LOOP, 10); //ƒAƒjƒ‡˜
}

void EnergyBar::onReset() {
    setScaleR(pAmount_->getPx() * rate_org_width_, 1.0); //‰¡•ûŒü‚É”{—¦‚ÅL‚Î‚·
}

void EnergyBar::onActive() {
}

void EnergyBar::processBehavior() {
//    amount_.set(value_);
    setScaleR(pAmount_->getPx() * rate_org_width_, 1.0); //‰¡•ûŒü‚É”{—¦‚ÅL‚Î‚·
    _pUvFlipper->behave();
}


void EnergyBar::processJudgement() {
}

void EnergyBar::onInactive() {
}

EnergyBar::~EnergyBar() {
}
