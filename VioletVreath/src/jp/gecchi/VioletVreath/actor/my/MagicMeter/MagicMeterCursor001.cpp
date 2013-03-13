#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;


MagicMeterCursor001::MagicMeterCursor001(const char* prm_name, MagicMeter* prm_pMagicMeter) :
        DefaultBoardActor(prm_name, "Cursor001") {
    _class_name = "MagicMeterCursor001";
    pMagicMeter_ = prm_pMagicMeter;
    tmp_alpha_ = _alpha;
    tX_ = 0;
    tY_ = 0;
}
void MagicMeterCursor001::initialize() {
    setAlign(ALIGN_CENTER, VALIGN_MIDDLE);
    _X = tX_ = pMagicMeter_->_X + pMagicMeter_->width_*pMagicMeter_->lstMagic_.getCurrentIndex() + (pMagicMeter_->width_/2);
    _Y = tY_ = pMagicMeter_->_Y + (pMagicMeter_->height_/2);
    _pUvFlipper->setActivePtn(0);
}

void MagicMeterCursor001::onActive() {

}

void MagicMeterCursor001::processBehavior() {
    _Z = 1;
    if (_pKurokoA->isRunnigSmoothMvVeloSequence() == false) {
        _X = tX_;
        _Y = tY_;
    }
    setAlpha(pMagicMeter_->getAlpha());
    _pKurokoA->behave();
    _pUvFlipper->behave();
}

void MagicMeterCursor001::processJudgement() {

}

void MagicMeterCursor001::moveTo(int prm_magic_mater_index) {
    tX_ = pMagicMeter_->_X + pMagicMeter_->width_*prm_magic_mater_index + (pMagicMeter_->width_/2);
    tY_ = pMagicMeter_->_Y + (pMagicMeter_->height_/2);
    _pKurokoA->setMvAngTwd(tX_, tY_);
    _pKurokoA->execSmoothMvVeloSequence(0, UTIL::getDistance(_X, _Y, tX_, tY_),
                                        12, 0.2, 0.4);
}

MagicMeterCursor001::~MagicMeterCursor001() {
}
