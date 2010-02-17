#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

TurboMeter::TurboMeter(const char* prm_name) : DefaultBoardActor(prm_name, "TurboMeter") {
    _class_name = "TurboMeter";
    //_z = 0.99;//ÇΩÇ‘ÇÒç≈îwñ  Åi0 <= _z < 1.0ÅjZ=(0Å`+1)
    //_z = 0.9999999f;
    _z = 0.00000001f;
    _max_px = 100.0f;
    _max_val = 100.0f;
    _unit_px = _max_px /_max_val;
    _val = 1.0f;
}

void TurboMeter::initialize() {
    _pUvFlipper->setFlipMethod(FLIP_ORDER_LOOP, 1); //ÉAÉjÉÅèáèò
}

void TurboMeter::onActive() {
}

void TurboMeter::processBehavior() {

    _val = pMYSHIP->_iMvVelo_BeginMT;
    float length_px = _unit_px * _val;
    if (length_px == 0) {
        _sx = 0.0f;
    } else {
        _sx = length_px / _pBoardModel->_fSize_BoardModelWidthPx;
    }
    _pUvFlipper->behave();
}

void TurboMeter::processJudgement() {
}

void TurboMeter::onInactive() {
}

TurboMeter::~TurboMeter() {
}
