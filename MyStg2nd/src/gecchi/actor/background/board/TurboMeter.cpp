#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace MyStg2nd;

TurboMeter::TurboMeter(const char* prm_name) : DefaultBoardActor(prm_name, "TurboMeter") {
    _class_name = "TurboMeter";
    //_z = 0.99;//ÇΩÇ‘ÇÒç≈îwñ  Åi0 <= _z < 1.0ÅjZ=(0Å`+1)
    //_z = 0.9999999f;
    _Z = 1;
    _max_px = 1000.0f;
    _max_val = 1000.0f;
    _unit_px = _max_px / _max_val;
    _val = 1.0f;
    _SX = _SY = 1000;
}

void TurboMeter::initialize() {
    graduateScale(400, 100000);
    _pUvFlipper->setFlipMethod(FLIP_ORDER_LOOP, 10); //ÉAÉjÉÅèáèò
}

void TurboMeter::onActive() {
}

void TurboMeter::processBehavior() {
    //_sx += 0.01;
    _val = P_MYSHIP->_iMvVelo_BeginMT;
    float length_px = _unit_px * _val;
    _SX = cnvScaleRate2App(length_px / _pBoardModel->_fSize_BoardModelWidthPx);
    _pUvFlipper->behave();
}

void TurboMeter::processJudgement() {
}

void TurboMeter::onInactive() {
}

TurboMeter::~TurboMeter() {
}
