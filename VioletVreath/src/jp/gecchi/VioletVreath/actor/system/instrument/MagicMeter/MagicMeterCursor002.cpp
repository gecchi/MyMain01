#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;


MagicMeterCursor002::MagicMeterCursor002(const char* prm_name, MagicMeter* prm_pMagicMeter, Magic* prm_pMagic) :
        DefaultBoardActor(prm_name, "MagicMeterCursor002") {
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
    setAlign(ALIGN_CENTER, VALIGN_MIDDLE);
    _X = tX_ = pMagicMeter_->_X + (pMagicMeter_->width_ * magic_index_) + (pMagicMeter_->width_ / 2);
    _Y = tY_ = pMagicMeter_->_Y + (pMagicMeter_->height_ / 2);
    tmp_Y_ = _Y;
    _pUvFlipper->setActivePtn(0);
    _pUvFlipper->forcePtnRange(0,2);
    _Z = 2;
}

void MagicMeterCursor002::onActive() {

}

void MagicMeterCursor002::processBehavior() {

    _Z = 2;
    if (_pKurokoA->isMoveingSmooth() == false) {
        _X = tX_;
        _Y = tY_;
    }
    _pKurokoA->behave();
    _pUvFlipper->behave();
    _pFader->behave();

    if (_pFader->_method == GgafDxAlphaFadingMethod::NO_ALPHAFADE) {
        setAlpha(pMagicMeter_->paFloat_rr_[magic_index_]);
    }
}

void MagicMeterCursor002::processJudgement() {
}

void MagicMeterCursor002::processPreDraw() {
    //ロールを考慮せずにLVカーソル移動させているので、ここで、ロール分Y座標を補正
    tmp_Y_ = _Y;
    _Y += (pMagicMeter_->height_ * (pMagicMeter_->paLv_cursor_point_[magic_index_]+1) * (1.0 - pMagicMeter_->paFloat_rr_[magic_index_]));
    DefaultBoardActor::processPreDraw();
}

void MagicMeterCursor002::processAfterDraw() {
    DefaultBoardActor::processAfterDraw();
    _Y = tmp_Y_;
}


void MagicMeterCursor002::disable() {
    _pUvFlipper->forcePtnRange(3,3); //ロック表示
    _pUvFlipper->setActivePtn(3);
}


void MagicMeterCursor002::enable() {
    _pUvFlipper->forcePtnRange(0,2);
    _pUvFlipper->setActivePtn(0);
}

void MagicMeterCursor002::beginBlinking() {
    _pFader->beat(6, 0, 3, 3, 10); //ピカピカ
}

void MagicMeterCursor002::stopBlinking() {
    _pFader->beat(8, 0, 4, 4, 1); //ピカピカ終了
    setAlpha(pMagicMeter_->paFloat_rr_[magic_index_]);
}

void MagicMeterCursor002::moveToLv(int prm_lv) {
    //ロールのY座標を考慮せずにLVカーソル移動。processPreDraw()でロール分を補正する。
    tX_ = _X;
    tY_ = pMagicMeter_->_Y - (pMagicMeter_->height_*(prm_lv+1)) + (pMagicMeter_->height_ / 2);
    _pKurokoA->setMvAng(tX_, tY_);
    _pKurokoA->execSmoothMvSequence(0, GgafDxUtil::getDistance(_X, _Y, tX_, tY_),
                                        10, 0.2, 0.4); //ロールを考慮せずにとりあえず移動
}

MagicMeterCursor002::~MagicMeterCursor002() {
}
