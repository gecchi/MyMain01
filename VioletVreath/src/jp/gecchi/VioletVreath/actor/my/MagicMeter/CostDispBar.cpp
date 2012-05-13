#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

CostDispBar::CostDispBar(const char* prm_name, GraphBar* prm_pSourceBar, AmountGraph* prm_pCostValue)
      : GraphBar(prm_name, "CostDispBar", prm_pCostValue) {
    _class_name = "CostDispBar";
    pSourceBar_ = prm_pSourceBar;
    pCostValue_ = prm_pCostValue;
    _Z = 3;
}

void CostDispBar::initialize() {
    _pUvFlipper->setFlipMethod(NOT_ANIMATED); //ƒAƒjƒ‡˜
    setAlpha(0.7);
}

void CostDispBar::onReset() {
    setScaleR(pCostValue_->getPx() / org_width_, 1.0); //‰¡•ûŒü‚É”{—¦‚ÅL‚Î‚·
}

void CostDispBar::onActive() {
}

void CostDispBar::processBehavior() {
    if ( pCostValue_->getPx() > 0) {
        _pUvFlipper->setActivePtn(0);
        pixcoord px = pSourceBar_->pAmount_->getPx() -  pCostValue_->getPx();
        if (px > 0) {
            _X = pSourceBar_->_X +  PX_C(px);
            setScaleR(pCostValue_->getPx() / org_width_, 1.0); //‰¡•ûŒü‚É”{—¦‚ÅL‚Î‚·
        } else {
            _X = pSourceBar_->_X;
            _SX = pSourceBar_->_SX;
        }
    } else {
        _pUvFlipper->setActivePtn(1);
        _X = pSourceBar_->_X + PX_C(pSourceBar_->pAmount_->getPx());
        setScaleR(-1.0* pCostValue_->getPx() / org_width_, 1.0); //‰¡•ûŒü‚É”{—¦‚ÅL‚Î‚·
    }
    _pUvFlipper->behave();
}


void CostDispBar::processJudgement() {
}

void CostDispBar::onInactive() {
}

CostDispBar::~CostDispBar() {
}
