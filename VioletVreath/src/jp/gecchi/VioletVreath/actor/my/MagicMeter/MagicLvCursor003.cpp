#include "MagicLvCursor003.h"

#include "jp/ggaf/dx/actor/supporter/AlphaFader.h"
#include "jp/ggaf/dx/actor/supporter/Scaler.h"
#include "jp/ggaf/dx/actor/supporter/UvFlipper.h"
#include "jp/gecchi/VioletVreath/actor/my/MagicMeter.h"
#include "jp/gecchi/VioletVreath/actor/my/MagicMeter/magic/Magic.h"
#include "jp/ggaf/dx/actor/supporter/LocoVehicle.h"



using namespace GgafLib;
using namespace VioletVreath;


MagicLvCursor003::MagicLvCursor003(const char* prm_name, MagicMeter* prm_pMagicMeter, Magic* prm_pMagic) :
        MagicLvCursor(prm_name, "MagicLvCursor003", prm_pMagicMeter, prm_pMagic) {
    _class_name = "MagicLvCursor003";
    pMagicMeter_ = prm_pMagicMeter;
    pMagic_ = prm_pMagic;
    magic_index_ = pMagicMeter_->lstMagic_.indexOf(pMagic_);
    if (magic_index_ < 0) {
        throwCriticalException("prm_pMagic("<<prm_pMagic->getName()<<")は"<<
                                   "MagicMeterに登録されていません。");
    }
}

void MagicLvCursor003::initialize() {
    MagicLvCursor::initialize();
    GgafDx::UvFlipper* pUvFlipper = getUvFlipper();
    pUvFlipper->setFlipPtnRange(0, 3);
    pUvFlipper->exec(NOT_ANIMATED);
    getScaler()->setRange(1000, 10000);
}

void MagicLvCursor003::processPreDraw() {
    //MagicLvCursor::processPreDraw(); 及び、MagicLvCursor::processAfterDraw()
    //では、Y座標ロールの追従と、ロールオープン・クローズに伴う半透明処理を行なっている。
    //しかし、本カーソル（"CASTING"などの文字）ロールが閉じても消さないようにするため、
    //オーバーライドし、半透明処理を削ることにする。
    //Y座標ロール追従は行うので、その部分のみ実装を行うことにする。
    //MagicLvCursor::processPreDraw(); 及び、MagicLvCursor::processAfterDraw() の処理を変更したら、
    //TODO:ここも変更せよ。
    tmp_y_ = _y; //退避
    _y += (1.0 * pMagicMeter_->height_ * (point_lv_+1) * (1.0 - pMagicMeter_->r_roll_[magic_index_]));
    DefaultBoardActor::processPreDraw();
}

void MagicLvCursor003::processAfterDraw() {
    DefaultBoardActor::processAfterDraw();
    _y = tmp_y_; //復帰
}

void MagicLvCursor003::markOff() {
    getUvFlipper()->stop();
    getAlphaFader()->reset();
    setAlpha(0);
}

void MagicLvCursor003::markOnLevelUpCast(int prm_lv) {
    setAlpha(0);
    getAlphaFader()->transitionLinearUntil(1.0, 20);
    moveTo(prm_lv);
    GgafDx::UvFlipper* pUvFlipper = getUvFlipper();
    pUvFlipper->setFlipPtnRange(0,3);
    pUvFlipper->setActivePtnToTop();
    pUvFlipper->exec(FLIP_ORDER_LOOP, 1);
    setScale(10000);
    getScaler()->transitionLinearUntil(1000, 20);
    setRzFaceAng(D180ANG);
    getLocoVehicle()->turnRzFaceAngTo(0, D180ANG/20, 0, TURN_COUNTERCLOCKWISE);
}

void MagicLvCursor003::markOnLevelDownCast(int prm_lv) {
    setAlpha(1.0);
    getAlphaFader()->transitionLinearUntil(0, 20);
    moveTo(prm_lv);
    GgafDx::UvFlipper* pUvFlipper = getUvFlipper();
    pUvFlipper->setFlipPtnRange(8, 11);
    pUvFlipper->setActivePtnToTop();
    pUvFlipper->exec(FLIP_ORDER_LOOP, 1);
    setScale(1000);
    getScaler()->transitionLinearUntil(10000, 20);
}

void MagicLvCursor003::markOnInvoke(int prm_lv) {
    moveTo(prm_lv);
    GgafDx::UvFlipper* pUvFlipper = getUvFlipper();
    pUvFlipper->setFlipPtnRange(4, 7);
    pUvFlipper->setActivePtnToTop();
    pUvFlipper->exec(FLIP_ORDER_LOOP, 1);
}

void MagicLvCursor003::markOnEffect(int prm_lv) {
    setAlpha(1.0);
    getAlphaFader()->transitionLinearUntil(0, 20);
    moveTo(prm_lv);
    GgafDx::UvFlipper* pUvFlipper = getUvFlipper();
    pUvFlipper->setFlipPtnRange(8, 11);
    pUvFlipper->setActivePtnToTop();
    pUvFlipper->exec(FLIP_ORDER_LOOP, 1);
    setScale(1000);
    getScaler()->transitionLinearUntil(10000, 20);
}

MagicLvCursor003::~MagicLvCursor003() {
}
