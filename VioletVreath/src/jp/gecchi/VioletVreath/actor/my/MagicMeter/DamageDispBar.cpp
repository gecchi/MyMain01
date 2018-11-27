#include "DamageDispBar.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxUvFlipper.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/MyShipScene.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

DamageDispBar::DamageDispBar(const char* prm_name, GgafLib::FramedHorizontalBarActor* prm_pTargetSourceBar)
      : FramedHorizontalBarActor(prm_name, "CostDispBar") {
    _class_name = "DamageDispBar";
    pSourceBar_ = prm_pTargetSourceBar;
    damege_disp_timer_ = 0;
    is_damege_disp_ = false;
}

void DamageDispBar::initialize() {
    getUvFlipper()->exec(NOT_ANIMATED); //アニメ順序
    setAlpha(1.0);
    setAlign(ALIGN_RIGHT);
}

void DamageDispBar::onReset() {
    setPositionAt(pSourceBar_);
    setHeight(pSourceBar_->getHeight());
    setWidth(0);
    getUvFlipper()->setActivePtn(0);//赤
}

void DamageDispBar::onActive() {
    setPositionAt(pSourceBar_);
    setHeight(pSourceBar_->getHeight());
    setWidth(0);
    getUvFlipper()->setActivePtn(0);//赤
}

void DamageDispBar::processBehavior() {
    if (is_damege_disp_) {
        addAlpha(-1.0/60.0);
        getUvFlipper()->behave();
        damege_disp_timer_--;
        if (damege_disp_timer_ <= 0) {
            is_damege_disp_ = false;
            setVal(0);
            setAlpha(0);
        } else {
            pixcoord damage_width = C_PX(_x) - (C_PX(pSourceBar_->_x) + pSourceBar_->getPix());
            setValByPix(damage_width);
        }
    }


}

void DamageDispBar::processJudgement() {


}

void DamageDispBar::onInactive() {
}

void DamageDispBar::dispDamage(int prm_before_val, int prm_after_val) {
    setAlpha(1.0);
    if (is_damege_disp_) {
        if (damege_disp_timer_ <= 20) {
            damege_disp_timer_ = 20; //赤表示時間(ほぼ連続ダメージ)
        }
    } else {
        damege_disp_timer_ = 60; //赤表示時間(間隔が開いてから)
        //ALIGN_RIGHT であるので、右端の x 座標を求め更新。
        pixcoord after_bar_px = cnvVal2Pix(prm_after_val);
        _x = pSourceBar_->_x + PX_C(after_bar_px);
        is_damege_disp_ = true;
    }
    pixcoord damage_width = C_PX(_x) - (C_PX(pSourceBar_->_x) + pSourceBar_->getPix());
    setValByPix(damage_width);
}

DamageDispBar::~DamageDispBar() {
}
