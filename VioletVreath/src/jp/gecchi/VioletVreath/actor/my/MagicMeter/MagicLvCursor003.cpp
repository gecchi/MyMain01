#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;


MagicLvCursor003::MagicLvCursor003(const char* prm_name, MagicMeter* prm_pMagicMeter, Magic* prm_pMagic) :
        MagicLvCursor(prm_name, "MagicLvCursor003", prm_pMagicMeter, prm_pMagic) {
    _class_name = "MagicLvCursor003";
    pMagicMeter_ = prm_pMagicMeter;
    pMagic_ = prm_pMagic;
    magic_index_ = pMagicMeter_->lstMagic_.indexOf(pMagic_);
    if (magic_index_ < 0) {
        throwGgafCriticalException("MagicLvCursor003::MagicLvCursor003 prm_pMagic("<<prm_pMagic->getName()<<")は"<<
                                   "MagicMeterに登録されていません。");
    }
}

void MagicLvCursor003::initialize() {
    MagicLvCursor::initialize();
    _pUvFlipper->forcePtnRange(0,3);
    _pUvFlipper->setActivePtn(3);
    _pUvFlipper->setFlipMethod(NOT_ANIMATED);

    _pScaler->forceScaleRange(1000, 10000);
}

void MagicLvCursor003::processPreDraw() {
    //MagicLvCursor::processPreDraw(); 及び、MagicLvCursor::processAfterDraw()
    //では、Y座標ロールの追従と、ロールオープン・クローズに伴う半透明処理を行なっている。
    //しかし、本カーソル（"CASTING"などの文字）ロールが閉じても消さないようにするため、
    //オーバーライドし、半透明処理を削ることにする。
    //Y座標ロール追従は行うので、その部分のみ実装を行うことにする。
    //MagicLvCursor::processPreDraw(); 及び、MagicLvCursor::processAfterDraw() の処理を変更したら、
    //ここも変更せよ。
    tmp_Y_ = _Y; //退避
    _Y += (1.0 * pMagicMeter_->height_ * (point_lv_+1) * (1.0 - pMagicMeter_->paFloat_rr_[magic_index_]));
    DefaultBoardActor::processPreDraw();
}

void MagicLvCursor003::processAfterDraw() {
    DefaultBoardActor::processAfterDraw();
    _Y = tmp_Y_; //復帰
}

void MagicLvCursor003::markOff() {
    _pUvFlipper->stopFlip();
    _pAFader->reset();
    _pAFader->setAlpha(0);
}

void MagicLvCursor003::markOnLevelUpCast(int prm_lv) {
    _pAFader->setAlpha(0);
    _pAFader->intoTargetAlphaLinerUntil(1.0, 20);
    moveTo(prm_lv);
    _pUvFlipper->forcePtnRange(0,3);
    _pUvFlipper->setActivePtn(0);
    _pUvFlipper->setFlipMethod(FLIP_ORDER_LOOP, 1);
    _pScaler->setScale(10000);
    _pScaler->intoTargetScaleLinerUntil(1000, 20);
}

void MagicLvCursor003::markOnLevelDownCast(int prm_lv) {
    _pAFader->setAlpha(1.0);
    _pAFader->intoTargetAlphaLinerUntil(0, 20);
    moveTo(prm_lv);
    _pUvFlipper->forcePtnRange(8, 11);
    _pUvFlipper->setActivePtn(8);
    _pUvFlipper->setFlipMethod(FLIP_ORDER_LOOP, 1);
    _pScaler->setScale(1000);
    _pScaler->intoTargetScaleLinerUntil(10000, 20);
}

void MagicLvCursor003::markOnInvoke(int prm_lv) {
    moveTo(prm_lv);
    _pUvFlipper->forcePtnRange(4, 7);
    _pUvFlipper->setActivePtn(4);
    _pUvFlipper->setFlipMethod(FLIP_ORDER_LOOP, 1);
}

void MagicLvCursor003::markOnEffect(int prm_lv) {
    _pAFader->setAlpha(1.0);
    _pAFader->intoTargetAlphaLinerUntil(0, 20);
    moveTo(prm_lv);
    _pUvFlipper->forcePtnRange(8, 11);
    _pUvFlipper->setActivePtn(8);
    _pUvFlipper->setFlipMethod(FLIP_ORDER_LOOP, 1);
    _pScaler->setScale(1000);
    _pScaler->intoTargetScaleLinerUntil(10000, 20);
}

MagicLvCursor003::~MagicLvCursor003() {
}
