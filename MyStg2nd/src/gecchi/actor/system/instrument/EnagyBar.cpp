#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

EnagyBar::EnagyBar(const char* prm_name) : DefaultBoardActor(prm_name, "TurboMeter") {
    _class_name = "EnagyBar";
    //_z = 0.99;//たぶん最背面 （0 <= _z < 1.0）Z=(0～+1)
    //_z = 0.9999999f;
    _Z = 0.00000001f* LEN_UNIT;
    _fSize_BoardModelWidthPx = _pBoardModel->_fSize_BoardModelWidthPx;
}

void EnagyBar::initialize() {
//    /_pUvFlipper->forcePtnNoRange(0, 10);
    _pUvFlipper->setFlipMethod(FLIP_ORDER_LOOP, 10); //アニメ順序

    onReset();
}

void EnagyBar::onReset() {
    _amount.config(600, 10000); //値 10000 で表示は400pxとする。
    _amount.set(10000);           //初期値は5000
    _SX = (_amount._val_px / _fSize_BoardModelWidthPx) * LEN_UNIT;
}

void EnagyBar::onActive() {
}

void EnagyBar::processBehavior() {
//    _amount.set(_value);
    _SX = (_amount._val_px / _fSize_BoardModelWidthPx) * LEN_UNIT;
    _pUvFlipper->behave();
}


void EnagyBar::processJudgement() {
}

void EnagyBar::onInactive() {
}

EnagyBar::~EnagyBar() {
}
