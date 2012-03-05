#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;


MagicMeterCursor002::MagicMeterCursor002(const char* prm_name, MagicMeter* prm_pMagicMeter, Magic* prm_pMagic) :
        DefaultBoardActor(prm_name, "MagicMeter") {
    _class_name = "MagicMeterCursor002";
    pMagicMeter_ = prm_pMagicMeter;
    pMagic_ = prm_pMagic;
    magic_index_ = pMagicMeter_->ringMagics_.indexOf(pMagic_);
    if (magic_index_ < 0) {
        throwGgafCriticalException("MagicMeterCursor002::MagicMeterCursor002 prm_pMagic("<<prm_pMagic->getName()<<")は"<<
                                   "MagicMeterに登録されていません。");
    }
}
void MagicMeterCursor002::initialize() {
    _X = tX_ = pMagicMeter_->_X + (pMagicMeter_->width_ * magic_index_);
    _Y = tY_ = pMagicMeter_->_Y;
    tmp_Y_ = _Y;
    _pUvFlipper->setActivePtnNo(0);
    _Z = 1;
}

void MagicMeterCursor002::onActive() {

}

void MagicMeterCursor002::processBehavior() {
    setAlpha(pMagic_->rr_);
    _Z = 1;
    if (_pKurokoA->isMoveingSmooth() == false) {
        _X = tX_;
        _Y = tY_;
    }
    _pKurokoA->behave();
    _pUvFlipper->behave();
    _pFader->behave();
}

void MagicMeterCursor002::processJudgement() {
}

void MagicMeterCursor002::processPreDraw() {
    //ロールを考慮せずにLVカーソル移動させ、ここで、ロール分を補正
    tmp_Y_ = _Y;
    _Y += (pMagicMeter_->height_ * (pMagicMeter_->paCursorLv_[magic_index_]+1) * (1.0-pMagic_->rr_));
    DefaultBoardActor::processPreDraw();
}

void MagicMeterCursor002::processAfterDraw() {
    DefaultBoardActor::processAfterDraw();
    _Y = tmp_Y_;
}

void MagicMeterCursor002::beginBlinking() {
    //_pFader->beat(8, 0, 4, 4, -1); //ピカピカしっぱなし
}

void MagicMeterCursor002::stopBlinking() {
    //_pFader->beat(8, 0, 4, 4, 1); //ピカピカ終了
    setAlpha(pMagic_->rr_);
}

void MagicMeterCursor002::moveToLv(int prm_lv) {
    tX_ = _X;
    tY_ = pMagicMeter_->_Y - (pMagicMeter_->height_*(prm_lv+1));
    _pKurokoA->setMvAng(tX_, tY_);
    _pKurokoA->execSmoothMvVeloSequence(0, GgafDxUtil::getDistance(_X, _Y, tX_, tY_),
                                        10, 0.2, 0.4); //ロールを考慮せずにとりあえず移動
}

MagicMeterCursor002::~MagicMeterCursor002() {
}
