#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

TurboMeter::TurboMeter(const char* prm_name) : DefaultBoardActor(prm_name, "TurboMeter") {
    _class_name = "TurboMeter";
    //_z = 0.99;//たぶん最背面 （0 <= _z < 1.0）Z=(0〜+1)
    //_z = 0.9999999f;
    _z = 0.00000001f;
    _max_px = 1000.0f;
    _max_val = 1000.0f;
    _unit_px = _max_px / _max_val;
    _val = 1.0f;
    _sx = _sy = 1.0f;
}

void TurboMeter::initialize() {
    graduateScale(400, 100000);
    _pUvFlipper->setFlipMethod(FLIP_ORDER_LOOP, 10); //アニメ順序
}

void TurboMeter::onActive() {
}

void TurboMeter::processBehavior() {
    //_sx += 0.01;
    _val = pMYSHIP->_iMvVelo_BeginMT;
    float length_px = _unit_px * _val;
    _sx = length_px / _pBoardModel->_fSize_BoardModelWidthPx;
    _pUvFlipper->behave();
}

void TurboMeter::processJudgement() {
}

void TurboMeter::onInactive() {
}

TurboMeter::~TurboMeter() {
}
