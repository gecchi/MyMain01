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
    magic_index_ = pMagicMeter_->ringMagics_.indexOf(pMagic_);
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
}

void MagicLvCursor003::processPreDraw() {
    //"CASTING" はロールが閉じても消さないようにする。
    tmp_alpha_ = getAlpha();
    if (_pUvFlipper->_uvflip_method == NOT_ANIMATED) {
        setAlpha(0);
    }
    //ここで、ロール分Y座標を補正（・・・ここはMagicLvCursor::processPreDraw()と同じ）
    tmp_Y_ = _Y; //退避
    _Y += (1.0 * pMagicMeter_->height_ * (point_lv_+1) * (1.0 - pMagicMeter_->paFloat_rr_[magic_index_]));
    DefaultBoardSetActor::processPreDraw();
}

void MagicLvCursor003::markOff() {
    setAlpha(0);
}

void MagicLvCursor003::markOnLevelUpCast(int prm_lv) {
    setAlpha(1);
    moveTo(prm_lv);
    _pUvFlipper->forcePtnRange(0,3);
    _pUvFlipper->setActivePtn(0);
    _pUvFlipper->setFlipMethod(FLIP_ORDER_LOOP, 3);
}

void MagicLvCursor003::markOnLevelDownCast(int prm_lv) {
    setAlpha(1);
    moveTo(prm_lv);
    _pUvFlipper->forcePtnRange(0,3);
    _pUvFlipper->setActivePtn(0);
    _pUvFlipper->setFlipMethod(FLIP_ORDER_NOLOOP, 3);
}

void MagicLvCursor003::markOnInvoke(int prm_lv) {
    moveTo(prm_lv);
    _pUvFlipper->forcePtnRange(4,7);
    _pUvFlipper->setActivePtn(4);
    _pUvFlipper->setFlipMethod(FLIP_ORDER_LOOP, 3);
}

MagicLvCursor003::~MagicLvCursor003() {
}
