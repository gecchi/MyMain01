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
    _pUvFlipper->setFlipMethod(NOT_ANIMATED); //アニメ順序
    setAlpha(0.7);
}

void CostDispBar::onReset() {
    setScaleR(pCostValue_->getPx() / org_width_, 1.0); //横方向に倍率で伸ばす
}

void CostDispBar::onActive() {
}

void CostDispBar::processBehavior() {
    if ( pCostValue_->getPx() > 0) {
        //正の値はコスト有りを表す。主メーターの削減値を赤で示すようにする。
        _pUvFlipper->setActivePtn(0);
        pixcoord px = pSourceBar_->pAmount_->getPx() - pCostValue_->getPx();
        if (px > 0) {
            _X = pSourceBar_->_X +  PX_C(px);
            setScaleR(pCostValue_->getPx() / org_width_, 1.0); //横方向に倍率で伸ばす
        } else {
            //元メーターからははみ出ないようにする
            _X = pSourceBar_->_X;
            _SX = pSourceBar_->_SX;
        }
    } else {
        //負の値はコストがマイナス、つまり元の値が増える。主メーターの増分値を青で示すようにする。
        _pUvFlipper->setActivePtn(1);
        _X = pSourceBar_->_X + PX_C(pSourceBar_->pAmount_->getPx());
        setScaleR(-1.0 * pCostValue_->getPx() / org_width_, 1.0); //横方向に倍率で伸ばす
    }
    _pUvFlipper->behave();
}


void CostDispBar::processJudgement() {
}

void CostDispBar::onInactive() {
}

CostDispBar::~CostDispBar() {
}
