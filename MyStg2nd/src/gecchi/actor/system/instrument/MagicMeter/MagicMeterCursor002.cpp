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
    _pMagic = prm_pMagic;
    _magic_index = _pMagicMeter->_ringMagics.indexOf(_pMagic);
    if (_magic_index < 0) {
        throwGgafCriticalException("MagicMeterCursor002::MagicMeterCursor002 prm_pMagic("<<prm_pMagic->getName()<<")は"<<
                                   "MagicMeterに登録されていません。");
    }
}
void MagicMeterCursor002::initialize() {
    _X = _pMagicMeter->_X + (_pMagicMeter->_width * _magic_index);
    _Y = _pMagicMeter->_Y;
    _tmp_Y = _Y;
    _pUvFlipper->setActivePtnNo(0);
	_Z = 1;
}

void MagicMeterCursor002::onActive() {

}

void MagicMeterCursor002::processBehavior() {
    setAlpha(_pMagic->_rr);
    _Z = 1;
    _pKurokoA->behave();
    _pUvFlipper->behave();
    _pFader->behave();
}

void MagicMeterCursor002::processJudgement() {
}

void MagicMeterCursor002::processPreDraw() {
    //ロールを考慮せずにLVカーソル移動させ、ここで、ロール分を補正
    _tmp_Y = _Y;
    _Y += (_pMagicMeter->_height * (_pMagicMeter->_paCursorLv[_magic_index]+1) * (1.0-_pMagic->_rr));
    DefaultBoardActor::processPreDraw();
}

void MagicMeterCursor002::processAfterDraw() {
    DefaultBoardActor::processAfterDraw();
    _Y = _tmp_Y;
}

void MagicMeterCursor002::beginBlinking() {
    //_pFader->beat(8, 0, 4, 4, -1); //ピカピカしっぱなし
}

void MagicMeterCursor002::stopBlinking() {
    //_pFader->beat(8, 0, 4, 4, 1); //ピカピカ終了
	setAlpha(_pMagic->_rr);
}

void MagicMeterCursor002::moveToLv(int prm_lv) {
    coord tX = _X;
    coord tY = _pMagicMeter->_Y - (_pMagicMeter->_height*(prm_lv+1));
    _pKurokoA->setMvAng(tX, tY);
    _pKurokoA->execSmoothMvVeloSequence(0, GgafDxUtil::getDistance(_X, _Y, tX, tY),
                                        20, 0.2, 0.4); //ロールを考慮せずにとりあえず移動
}

MagicMeterCursor002::~MagicMeterCursor002() {
}
