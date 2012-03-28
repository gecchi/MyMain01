#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;


MagicMeterCursor001::MagicMeterCursor001(const char* prm_name, MagicMeter* prm_pMagicMeter) :
        DefaultBoardActor(prm_name, "MagicMeter") {
    _class_name = "MagicMeterCursor001";
    pMagicMeter_ = prm_pMagicMeter;
    _Z = 0;
}
void MagicMeterCursor001::initialize() {
    _X = tX_ = pMagicMeter_->_X + pMagicMeter_->width_*pMagicMeter_->ringMagics_.getCurrentIndex();
    _Y = tY_ = pMagicMeter_->_Y;
    _pUvFlipper->setActivePtn(0);
}

void MagicMeterCursor001::onActive() {

}

void MagicMeterCursor001::processBehavior() {
    _Z = 0;
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
    tX_ = pMagicMeter_->_X + pMagicMeter_->width_*prm_magic_mater_index;
    tY_ = pMagicMeter_->_Y;
    _pKurokoA->setMvAng(tX_, tY_);
    _pKurokoA->execSmoothMvSequence(0, GgafDxUtil::getDistance(_X, _Y, tX_, tY_),
                                        10, 0.2, 0.4);
}

MagicMeterCursor001::~MagicMeterCursor001() {
}
