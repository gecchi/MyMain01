#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

CostDispBar::CostDispBar(const char* prm_name, EnergyBar* prm_pEnergyBar, AmountGraph* prm_pCostDisp) : DefaultBoardActor(prm_name, "CostDispBar") {
    _class_name = "CostDispBar";
    pEnergyBar_ = prm_pEnergyBar;
    pCostDisp_ = prm_pCostDisp;
    _Z = 3;
    _fSize_BoardModelWidthPx = _pBoardModel->_fSize_BoardModelWidthPx;
}

void CostDispBar::initialize() {
    _pUvFlipper->setFlipMethod(NOT_ANIMATED); //ƒAƒjƒ‡˜
    setAlpha(0.7);
}

void CostDispBar::onReset() {
    _SX = R_SC(pCostDisp_->getPx() / _fSize_BoardModelWidthPx); //‰¡•ûŒü‚É”{—¦‚ÅL‚Î‚·
}

void CostDispBar::onActive() {
}

void CostDispBar::processBehavior() {
    if ( pCostDisp_->getPx() > 0) {
        _pUvFlipper->setActivePtn(0);
        pixcoord px = pEnergyBar_->pAmount_->getPx() -  pCostDisp_->getPx();
        if (px > 0) {
            _X = pEnergyBar_->_X +  PX_C(px);
            _SX = R_SC(pCostDisp_->getPx() / _fSize_BoardModelWidthPx); //‰¡•ûŒü‚É”{—¦‚ÅL‚Î‚·
        } else {
            _X = pEnergyBar_->_X;
            _SX = pEnergyBar_->_SX;
        }
    } else {
        _pUvFlipper->setActivePtn(1);
        _X = pEnergyBar_->_X + PX_C(pEnergyBar_->pAmount_->getPx());
        _SX = R_SC(-1.0* pCostDisp_->getPx() / _fSize_BoardModelWidthPx); //‰¡•ûŒü‚É”{—¦‚ÅL‚Î‚·
    }
    _pUvFlipper->behave();
}


void CostDispBar::processJudgement() {
}

void CostDispBar::onInactive() {
}

CostDispBar::~CostDispBar() {
}
