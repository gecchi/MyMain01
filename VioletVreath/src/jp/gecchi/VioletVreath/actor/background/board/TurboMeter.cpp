#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

TurboMeter::TurboMeter(const char* prm_name) : DefaultBoardActor(prm_name, "TurboMeter") {
    _class_name = "TurboMeter";
    //z_ = 0.99;//ÇΩÇ‘ÇÒç≈îwñ  Åi0 <= z_ < 1.0ÅjZ=(0Å`+1)
    //z_ = 0.9999999f;
    _Z = 1;
    max_px_ = 1000.0f;
    max_val_ = 1000.0f;
    unit_px_ = max_px_ / max_val_;
    val_ = 1.0f;
    _SX = _SY = 1000;
}

void TurboMeter::initialize() {
    graduateScale(400, 100000);
    _pUvFlipper->setFlipMethod(FLIP_ORDER_LOOP, 10); //ÉAÉjÉÅèáèò
}

void TurboMeter::onActive() {
}

void TurboMeter::processBehavior() {
    //sx_ += 0.01;
    val_ = P_MYSHIP->iMvVelo_BeginMT_;
    float length_px = unit_px_ * val_;
    _SX = R_SC(length_px / _pBoardModel->_fSize_BoardModelWidthPx);
    _pUvFlipper->behave();
}

void TurboMeter::processJudgement() {
}

void TurboMeter::onInactive() {
}

TurboMeter::~TurboMeter() {
}
