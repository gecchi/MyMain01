#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

EnergyBar::EnergyBar(const char* prm_name, AmountGraph* prm_pAmount) : DefaultBoardActor(prm_name, "TurboMeter") {
    _class_name = "EnergyBar";
    pAmount_ = prm_pAmount;
    _Z = 4;
    _fSize_BoardModelWidthPx = _pBoardModel->_fSize_BoardModelWidthPx;
}

void EnergyBar::initialize() {
    _pUvFlipper->setFlipMethod(FLIP_ORDER_LOOP, 10); //ƒAƒjƒ‡˜
}

void EnergyBar::onReset() {
    _SX = R_SC(pAmount_->getPx() / _fSize_BoardModelWidthPx); //‰¡•ûŒü‚É”{—¦‚ÅL‚Î‚·
}

void EnergyBar::onActive() {
}

void EnergyBar::processBehavior() {
//    amount_.set(value_);
    _SX = R_SC(pAmount_->getPx() / _fSize_BoardModelWidthPx); //‰¡•ûŒü‚É”{—¦‚ÅL‚Î‚·
    _pUvFlipper->behave();
}


void EnergyBar::processJudgement() {
}

void EnergyBar::onInactive() {
}

EnergyBar::~EnergyBar() {
}
