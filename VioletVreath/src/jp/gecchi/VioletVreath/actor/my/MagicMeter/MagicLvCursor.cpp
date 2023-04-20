#include "MagicLvCursor.h"

#include "jp/ggaf/core/util/RingLinkedList.hpp"
#include "jp/ggaf/dx/actor/supporter/AlphaFader.h"
#include "jp/ggaf/dx/actor/supporter/LocoVehicle.h"
#include "jp/ggaf/dx/actor/supporter/Scaler.h"
#include "jp/ggaf/dx/actor/supporter/UvFlipper.h"
#include "jp/gecchi/VioletVreath/actor/my/MagicMeter.h"
#include "jp/gecchi/VioletVreath/actor/my/MagicMeter/magic/Magic.h"
#include "jp/ggaf/dx/actor/supporter/LocoVehicleMvAssistant.h"



using namespace GgafLib;
using namespace VioletVreath;


MagicLvCursor::MagicLvCursor(const char* prm_name, const char* prm_model, MagicMeter* prm_pMagicMeter, Magic* prm_pMagic) :
        DefaultBoardActor(prm_name, prm_model) {
    _class_name = "MagicLvCursor";
    pMagicMeter_ = prm_pMagicMeter;
    pMagic_ = prm_pMagic;
    magic_index_ = pMagicMeter_->lstMagic_.indexOf(pMagic_);
    if (magic_index_ < 0) {
        throwCriticalException("prm_pMagic("<<prm_pMagic->getName()<<")は"
                                   "MagicMeterに登録されていません。");
    }
    point_lv_ = 0;
    tmp_y_ = _y;
    tmp_alpha_ = getAlpha();
    tx_ = 0;
    ty_ = 0;
    setZWriteEnable(false);
}

void MagicLvCursor::initialize() {
    setAlign(ALIGN_CENTER, VALIGN_MIDDLE);
    //MagicMeterの座標が定まってから行うこと
    _x = tx_ = pMagicMeter_->_x + (pMagicMeter_->width_ * magic_index_) + (pMagicMeter_->width_ / 2);
    _y = ty_ = pMagicMeter_->_y - (pMagicMeter_->height_*(point_lv_+1)) + (pMagicMeter_->height_ / 2);
    getUvFlipper()->exec(FLIP_ORDER_LOOP, 1);
    getScaler()->setRange(1000, 3000);
}

void MagicLvCursor::processBehavior() {
    GgafDx::LocoVehicle* pLocoVehicle = getLocoVehicle();
    pLocoVehicle->behave();
    if (pLocoVehicle->asstMv()->hasJustFinishedSliding()) {
        //理想位置に補正
        _x = tx_;
        _y = ty_;
    }
    getUvFlipper()->behave();
    getAlphaFader()->behave();
    getScaler()->behave();
}
void MagicLvCursor::processPreDraw() {
    //カーソル関連は
    //少し早めに薄くなる（消える）ようにした
    //基本はpAFader_、描画時のみロール同期の半透明を考慮
    float rr = pMagicMeter_->r_roll_[magic_index_];
    float alpha_r = rr * 2 - 1.0f;
    if (alpha_r < 0.0f) {
        alpha_r = 0.0f;
    }
    tmp_alpha_ = getAlpha();//退避
    setAlpha(alpha_r*tmp_alpha_*pMagicMeter_->getAlpha());
    //ここで、ロール分Y座標を補正
    tmp_y_ = _y; //退避
    _y += (1.0 * pMagicMeter_->height_ * (point_lv_+1) * (1.0 - rr));
    DefaultBoardActor::processPreDraw();

    //Y座標ロール追従処理を変えたら、MagicLvCursor003::processPreDraw() も同様の変更を！
}

void MagicLvCursor::processAfterDraw() {
    DefaultBoardActor::processAfterDraw();
    _y = tmp_y_; //復帰
    setAlpha(tmp_alpha_); //復帰
    //Y座標ロール追従処理を変えたら、MagicLvCursor003::processAfterDraw() も同様の変更を！
}

void MagicLvCursor::moveTo(int prm_lv) {
    GgafDx::LocoVehicle* pLocoVehicle = getLocoVehicle();
    pLocoVehicle->asstMv()->stopSliding();
    pLocoVehicle->stop();
    point_lv_ = prm_lv;
    _x = tx_ = pMagicMeter_->_x + (pMagicMeter_->width_ * magic_index_) + (pMagicMeter_->width_ / 2);
    _y = ty_ = pMagicMeter_->_y - (pMagicMeter_->height_*(point_lv_+1)) + (pMagicMeter_->height_ / 2);
}

void MagicLvCursor::moveSmoothTo(int prm_lv, frame prm_target_frames, float prm_p1, float prm_p2) {
    GgafDx::LocoVehicle* pLocoVehicle = getLocoVehicle();
    pLocoVehicle->stop();
    //Y座標のロール（スライド表示）の分考慮せずにY座標のLVカーソル移動計算を行っている。
    //processPreDraw()でロール分を補正する。
    point_lv_ = prm_lv;
    tx_ = pMagicMeter_->_x + (pMagicMeter_->width_ * magic_index_) + (pMagicMeter_->width_ / 2);
    ty_ = pMagicMeter_->_y - (pMagicMeter_->height_*(point_lv_+1)) + (pMagicMeter_->height_ / 2);
    pLocoVehicle->setMvAngTwd(tx_, ty_);
    pLocoVehicle->asstMv()->slideByDt(UTIL::getDistance(_x, _y, tx_, ty_), (int)prm_target_frames,
                                     prm_p1, prm_p2, 0, true); //ロールを考慮せずにとりあえず移動
}

void MagicLvCursor::blink() {
    getAlphaFader()->beat(6, 3, 0, 3, 7.5); //ピカピカ、+0.5は最後は表示終了為
    getScaler()->beat(12, 6, 0, 6, 3);
}

MagicLvCursor::~MagicLvCursor() {
}
