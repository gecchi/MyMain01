#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;


MagicMeterCursor001::MagicMeterCursor001(const char* prm_name, MagicMeter* prm_pMagicMeter) :
        DefaultBoardActor(prm_name, "MagicMeter") {
    _class_name = "MagicMeterCursor001";
    _pMagicMeter = prm_pMagicMeter;
    _Z = 0;
}
void MagicMeterCursor001::initialize() {
    _X = _tX = _pMagicMeter->_X + _pMagicMeter->_width*_pMagicMeter->_ringMagics.getCurrentIndex();
    _Y = _tY = _pMagicMeter->_Y;
    _pUvFlipper->setActivePtnNo(0);
}

void MagicMeterCursor001::onActive() {

}

void MagicMeterCursor001::processBehavior() {
    _Z = 0;
    if (_pKurokoA->isMoveingSmooth() == false) {
        _X = _tX;
        _Y = _tY;
    }

    _pKurokoA->behave();
    _pUvFlipper->behave();

}

void MagicMeterCursor001::processJudgement() {

}

void MagicMeterCursor001::moveTo(int prm_magic_mater_index) {
    _tX = _pMagicMeter->_X + _pMagicMeter->_width*prm_magic_mater_index;
    _tY = _pMagicMeter->_Y;
    _pKurokoA->setMvAng(_tX, _tY);
    _pKurokoA->execSmoothMvVeloSequence(0, GgafDxUtil::getDistance(_X, _Y, _tX, _tY),
                                        10, 0.2, 0.4);
}

MagicMeterCursor001::~MagicMeterCursor001() {
}
