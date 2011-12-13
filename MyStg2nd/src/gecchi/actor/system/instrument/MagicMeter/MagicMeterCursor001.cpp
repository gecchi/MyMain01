#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace MyStg2nd;


MagicMeterCursor001::MagicMeterCursor001(const char* prm_name, MagicMeter* prm_pMagicMeter) :
        DefaultBoardActor(prm_name, "MagicMeter") {
    _class_name = "MagicMeterCursor001";
    _pMagicMeter = prm_pMagicMeter;
}
void MagicMeterCursor001::initialize() {
    _X = _pMagicMeter->_X + _pMagicMeter->_width*_pMagicMeter->_ringMagics.getCurrentIndex();
    _Y = _pMagicMeter->_Y;
    _pUvFlipper->setActivePtnNo(0);
}

void MagicMeterCursor001::onActive() {

}

void MagicMeterCursor001::processBehavior() {
    _pKurokoA->behave();
    _pUvFlipper->behave();
}

void MagicMeterCursor001::processJudgement() {
}

void MagicMeterCursor001::moveTo(int prm_magic_mater_index) {
    coord tX = _pMagicMeter->_X + _pMagicMeter->_width*prm_magic_mater_index;
    coord tY = _pMagicMeter->_Y;
    _pKurokoA->setMvAng(tX, tY);
    _pKurokoA->execSmoothMvVeloSequence(0, GgafDxUtil::getDistance(_X, _Y, tX, tY),
                                        8, 0.1, 0.4);
}

MagicMeterCursor001::~MagicMeterCursor001() {
}
