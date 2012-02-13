#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

EnagyBar::EnagyBar(const char* prm_name, AmountGraph* prm_pAmount) : DefaultBoardActor(prm_name, "TurboMeter") {
    _class_name = "EnagyBar";
    _pAmount = prm_pAmount;
    //_z = 0.99;//ÇΩÇ‘ÇÒç≈îwñ  Åi0 <= _z < 1.0ÅjZ=(0Å`+1)
    //_z = 0.9999999f;
    _Z = 0.00000001f* LEN_UNIT;
    _fSize_BoardModelWidthPx = _pBoardModel->_fSize_BoardModelWidthPx;
}

void EnagyBar::initialize() {
//    /_pUvFlipper->forcePtnNoRange(0, 10);
    _pUvFlipper->setFlipMethod(FLIP_ORDER_LOOP, 10); //ÉAÉjÉÅèáèò

    onReset();
}

void EnagyBar::onReset() {
    _SX = (_pAmount->_val_px / _fSize_BoardModelWidthPx) * LEN_UNIT;
}

void EnagyBar::onActive() {
}

void EnagyBar::processBehavior() {
//    _amount.set(_value);
    _SX = (_pAmount->_val_px / _fSize_BoardModelWidthPx) * LEN_UNIT;
    _pUvFlipper->behave();
}


void EnagyBar::processJudgement() {
}

void EnagyBar::onInactive() {
}

EnagyBar::~EnagyBar() {
}
