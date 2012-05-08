#include "stdafx.h"
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
    tmp_alpha_ = getAlpha();
}

void MagicLvCursor::initialize() {
    setAlign(ALIGN_CENTER, VALIGN_MIDDLE);
    //MagicMeterの座標が定まってから行うこと
    _X = tX_ = pMagicMeter_->_X + (pMagicMeter_->width_ * magic_index_) + (pMagicMeter_->width_ / 2);
    _Y = tY_ = pMagicMeter_->_Y - (pMagicMeter_->height_*(point_lv_+1)) + (pMagicMeter_->height_ / 2);
    _pUvFlipper->setFlipMethod(FLIP_ORDER_LOOP, 1);
}

void MagicLvCursor::processBehavior() {

    if (_pKurokoA->isJustFinishSmoothMvSequence()) {
        //理想位置に補正
        _X = tX_;
        _Y = tY_;
    }
    _pKurokoA->behave();
    _pUvFlipper->behave();
    _pFader->behave();
}
void MagicLvCursor::processPreDraw() {
    //カーソル関連は
    //少し早めに薄くなる（消える）ようにした
    //基本は_pFader、描画時のみロール同期の半透明を考慮
    float alpha_r = pMagicMeter_->paFloat_rr_[magic_index_] * 2 - 1.0f;
    if (alpha_r < 0.0f) {
        alpha_r = 0.0f;
    }
    tmp_alpha_ = getAlpha();//退避
    setAlpha(alpha_r*tmp_alpha_);
    //ここで、ロール分Y座標を補正
    tmp_Y_ = _Y; //退避
    _Y += (1.0 * pMagicMeter_->height_ * (point_lv_+1) * (1.0 - pMagicMeter_->paFloat_rr_[magic_index_]));
    DefaultBoardSetActor::processPreDraw();
}

void MagicLvCursor::processAfterDraw() {
    DefaultBoardSetActor::processAfterDraw();
    _Y = tmp_Y_; //復帰
    setAlpha(tmp_alpha_); //復帰
}

void MagicLvCursor::moveTo(int prm_lv) {
    _pKurokoA->_smooth_mv_velo_seq_flg = false;
    _pKurokoA->setMvVelo(0);
    _pKurokoA->setMvAcce(0);
    point_lv_ = prm_lv;
    _X = tX_ = pMagicMeter_->_X + (pMagicMeter_->width_ * magic_index_) + (pMagicMeter_->width_ / 2);
    _Y = tY_ = pMagicMeter_->_Y - (pMagicMeter_->height_*(point_lv_+1)) + (pMagicMeter_->height_ / 2);
}

void MagicLvCursor::moveSmoothTo(int prm_lv, int prm_target_frames, float prm_p1, float prm_p2) {
    //Y座標のロール（スライド表示）の分考慮せずにY座標のLVカーソル移動計算を行っている。
    //processPreDraw()でロール分を補正する。
    point_lv_ = prm_lv;
    tX_ = pMagicMeter_->_X + (pMagicMeter_->width_ * magic_index_) + (pMagicMeter_->width_ / 2);
    tY_ = pMagicMeter_->_Y - (pMagicMeter_->height_*(point_lv_+1)) + (pMagicMeter_->height_ / 2);
    _pKurokoA->setMvAng(tX_, tY_);
    _pKurokoA->execSmoothMvSequence(0, GgafDxUtil::getDistance(_X, _Y, tX_, tY_),
                                    prm_target_frames, prm_p1, prm_p2); //ロールを考慮せずにとりあえず移動
}

MagicLvCursor::~MagicLvCursor() {
}
