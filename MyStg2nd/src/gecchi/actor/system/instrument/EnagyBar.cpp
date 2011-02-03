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
    _z = 0.00000001f;
    _fSize_BoardModelWidthPx = _pBoardModel->_fSize_BoardModelWidthPx;
}

void EnagyBar::initialize() {
    _pUvFlipper->forcePtnNoRange(0, 10);
    _pUvFlipper->setFlipMethod(FLIP_ORDER_LOOP, 10); //アニメ順序
    _sx = _qu._val_px / _fSize_BoardModelWidthPx;
    processReset();
}

void EnagyBar::processReset() {
    _enagy = 1000.0f;
    _qu.config(400.0f, _enagy); //初期値は400pxでフルエネルキー
}

void EnagyBar::onActive() {
}

void EnagyBar::processBehavior() {
//    _sx = _qu._val_px / _fSize_BoardModelWidthPx;
    _pUvFlipper->behave();
}


void EnagyBar::processJudgement() {
}

void EnagyBar::onInactive() {
}

EnagyBar::~EnagyBar() {
}
