#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

EnagyBar::EnagyBar(const char* prm_name, AmountGraph* prm_pAmount) : DefaultBoardActor(prm_name, "TurboMeter") {
    _class_name = "EnagyBar";
    pAmount_ = prm_pAmount;
    //z_ = 0.99;//ÇΩÇ‘ÇÒç≈îwñ  Åi0 <= z_ < 1.0ÅjZ=(0Å`+1)
    //z_ = 0.9999999f;
    _Z = 0.00000001f* LEN_UNIT;
    _fSize_BoardModelWidthPx = _pBoardModel->_fSize_BoardModelWidthPx;
}

void EnagyBar::initialize() {
//    /_pUvFlipper->forcePtnNoRange(0, 10);
    _pUvFlipper->setFlipMethod(FLIP_ORDER_LOOP, 10); //ÉAÉjÉÅèáèò

    onReset();
}

void EnagyBar::onReset() {
    _SX = (pAmount_->_val_px / _fSize_BoardModelWidthPx) * LEN_UNIT;
}

void EnagyBar::onActive() {
}

void EnagyBar::processBehavior() {
//    amount_.set(value_);
    _SX = (pAmount_->_val_px / _fSize_BoardModelWidthPx) * LEN_UNIT;
    _pUvFlipper->behave();
}


void EnagyBar::processJudgement() {
}

void EnagyBar::onInactive() {
}

EnagyBar::~EnagyBar() {
}
