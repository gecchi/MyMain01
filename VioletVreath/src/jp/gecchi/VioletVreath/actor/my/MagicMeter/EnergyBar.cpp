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
    _pUvFlipper->exec(FLIP_ORDER_LOOP, 10); //�A�j������
}

void EnergyBar::onReset() {
    setScaleR(pAmount_->getPx() * rate_org_width_, 1.0); //�������ɔ{���ŐL�΂�
}

void EnergyBar::onActive() {
}

void EnergyBar::processBehavior() {
//    amount_.set(value_);
    setScaleR(pAmount_->getPx() * rate_org_width_, 1.0); //�������ɔ{���ŐL�΂�
    _pUvFlipper->behave();
}


void EnergyBar::processJudgement() {
}

void EnergyBar::onInactive() {
}

EnergyBar::~EnergyBar() {
}
