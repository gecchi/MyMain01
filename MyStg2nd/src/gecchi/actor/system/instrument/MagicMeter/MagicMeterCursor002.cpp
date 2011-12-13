#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace MyStg2nd;


MagicMeterCursor002::MagicMeterCursor002(const char* prm_name, MagicMeter* prm_pMagicMeter, Magic* prm_pMagic) :
        DefaultBoardActor(prm_name, "MagicMeter") {
    _class_name = "MagicMeterCursor002";
    _pMagicMeter = prm_pMagicMeter;
    _magic_index = _pMagicMeter->_ringMagics.indexOf(_pMagic);
    _pMagic = prm_pMagic;

}
void MagicMeterCursor002::initialize() {
    _X = _pMagicMeter->_X + (_pMagicMeter->_width * _magic_index);
    _Y = _pMagicMeter->_Y;
    _tmp_Y = _Y;
    _pUvFlipper->setActivePtnNo(0);
}

void MagicMeterCursor002::onActive() {

}

void MagicMeterCursor002::processBehavior() {

    _pKurokoA->behave();
    _pUvFlipper->behave();
}

void MagicMeterCursor002::processJudgement() {
}

void MagicMeterCursor002::processPreDraw() {
//    if (_pMagic->_rr > 0.0) {
//        _tmp_Y = _Y;
//        _Y -= (_pMagicMeter->_height*(_pMagicMeter->_paCursorLv[_magic_index]+1)*(1.0-_pMagic->_rr));
//    //    _Y -= (_pMagicMeter->_height*(_pMagicMeter->_paCursorLv[i]+1)*_pMagic->_rr); //ƒ[ƒ‹·•ª
//    }

}

void MagicMeterCursor002::processAfterDraw() {
//    _Y = _tmp_Y;
}



void MagicMeterCursor002::moveToLv(int prm_lv) {
    coord tX = _X;
    coord tY = _pMagicMeter->_Y - (_pMagicMeter->_height*(prm_lv+1));
    _TRACE_("_magic_index="<<_magic_index<<" (tX, tY)="<<tX<<","<<tY);
    _pKurokoA->setMvAng(tX, tY);
    _pKurokoA->execSmoothMvVeloSequence(0, GgafDxUtil::getDistance(_X, _Y, tX, tY),
                                        8, 0.1, 0.4);

}

MagicMeterCursor002::~MagicMeterCursor002() {
}
