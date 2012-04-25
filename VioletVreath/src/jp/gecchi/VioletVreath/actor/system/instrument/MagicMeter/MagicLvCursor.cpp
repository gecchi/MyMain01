#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;




MagicLvCursor::MagicLvCursor(const char* prm_name, const char* prm_model, MagicMeter* prm_pMagicMeter, Magic* prm_pMagic) :
        DefaultBoardSetActor(prm_name, prm_model) {
    _class_name = "MagicLvCursor";
    pMagicMeter_ = prm_pMagicMeter;
    pMagic_ = prm_pMagic;
    magic_index_ = pMagicMeter_->ringMagics_.indexOf(pMagic_);
    if (magic_index_ < 0) {
        throwGgafCriticalException("MagicLvCursor::MagicLvCursor prm_pMagic("<<prm_pMagic->getName()<<")は"<<
                                   "MagicMeterに登録されていません。");
    }
    point_lv_ = 0;
    tmp_Y_ = _Y;
}

void MagicLvCursor::initialize() {
    setAlign(ALIGN_CENTER, VALIGN_MIDDLE);
    //MagicMeterの座標が定まってから行うこと
    _X = tX_ = pMagicMeter_->_X + (pMagicMeter_->width_ * magic_index_) + (pMagicMeter_->width_ / 2);
    _Y = tY_ = pMagicMeter_->_Y - (pMagicMeter_->height_*(point_lv_+1)) + (pMagicMeter_->height_ / 2);
    _pUvFlipper->setFlipMethod(FLIP_ORDER_LOOP, 1);
}

void MagicLvCursor::processBehavior() {
    if (_pKurokoA->isMoveingSmooth() == false) {
        _X = tX_;
        _Y = tY_;
    }
    _pKurokoA->behave();
    _pUvFlipper->behave();
    //_pFader->behave();
}
void MagicLvCursor::processPreDraw() {
    setAlpha(pMagicMeter_->paFloat_rr_[magic_index_]);
    //ロールを考慮せずにLVカーソル移動させているので、ここで、ロール分Y座標を補正
    tmp_Y_ = _Y;
    _Y += (pMagicMeter_->height_ * (point_lv_+1) * (1.0 - pMagicMeter_->paFloat_rr_[magic_index_]));
    DefaultBoardSetActor::processPreDraw();
}
void MagicLvCursor::processAfterDraw() {
    DefaultBoardSetActor::processAfterDraw();
    _Y = tmp_Y_;
}
void MagicLvCursor::setLv(int prm_lv) {
    point_lv_ = prm_lv;
    tX_ = _X;
    tY_ = _Y = pMagicMeter_->_Y - (pMagicMeter_->height_*(point_lv_+1)) + (pMagicMeter_->height_ / 2);
}
void MagicLvCursor::moveTo(int prm_lv, int prm_target_frames, float prm_p1, float prm_p2) {
    //ロールのY座標を考慮せずにLVカーソル移動。processPreDraw()でロール分を補正する。
    point_lv_ = prm_lv;
    tX_ = _X;
    tY_ = pMagicMeter_->_Y - (pMagicMeter_->height_*(point_lv_+1)) + (pMagicMeter_->height_ / 2);
    _pKurokoA->setMvAng(tX_, tY_);
    _pKurokoA->execSmoothMvSequence(0, GgafDxUtil::getDistance(_X, _Y, tX_, tY_),
                                    prm_target_frames, prm_p1, prm_p2); //ロールを考慮せずにとりあえず移動
}
MagicLvCursor::~MagicLvCursor() {
}
