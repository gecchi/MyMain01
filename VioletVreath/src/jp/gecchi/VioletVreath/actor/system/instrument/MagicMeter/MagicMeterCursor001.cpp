#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;


MagicMeterCursor001::MagicMeterCursor001(const char* prm_name, MagicMeter* prm_pMagicMeter) :
        DefaultBoardActor(prm_name, "Cursor001") {
    _class_name = "MagicMeterCursor001";
    pMagicMeter_ = prm_pMagicMeter;
}
void MagicMeterCursor001::initialize() {
    setAlign(ALIGN_CENTER, VALIGN_MIDDLE);
    _X = tX_ = pMagicMeter_->_X + pMagicMeter_->width_*pMagicMeter_->ringMagics_.getCurrentIndex() + (pMagicMeter_->width_/2);
    _Y = tY_ = pMagicMeter_->_Y + (pMagicMeter_->height_/2);
    _pUvFlipper->setActivePtn(0);
}

void MagicMeterCursor001::onActive() {

}

void MagicMeterCursor001::processBehavior() {
    _Z = 1;
    if (_pKurokoA->isMoveingSmooth() == false) {
        _X = tX_;
        _Y = tY_;
    }

    _pKurokoA->behave();
    _pUvFlipper->behave();

}

void MagicMeterCursor001::processJudgement() {

}

void MagicMeterCursor001::moveTo(int prm_magic_mater_index) {
    tX_ = pMagicMeter_->_X + pMagicMeter_->width_*prm_magic_mater_index + (pMagicMeter_->width_/2);
    tY_ = pMagicMeter_->_Y + (pMagicMeter_->height_/2);
    _pKurokoA->setMvAng(tX_, tY_);
    _pKurokoA->execSmoothMvSequence(0, GgafDxUtil::getDistance(_X, _Y, tX_, tY_),
                                        10, 0.2, 0.4);
}

MagicMeterCursor001::~MagicMeterCursor001() {
}
