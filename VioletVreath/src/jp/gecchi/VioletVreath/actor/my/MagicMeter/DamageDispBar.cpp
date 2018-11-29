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
    setVal(0);
    getUvFlipper()->setActivePtn(0);//赤
}

void DamageDispBar::onActive() {
    setPositionAt(pSourceBar_);
    setHeight(pSourceBar_->getHeight());
    setVal(0);
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
            coord damage_width = _x - (pSourceBar_->_x + pSourceBar_->getCoordWidth());
            if (damage_width > 0) {
                setValByCoordWidth(damage_width);
            } else {
                setVal(0);
                setAlpha(0);
            }
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
            damege_disp_timer_ = 20; //20F以内は連続ダメージと考えて加算表示する
        }
        coord total_damage_width = cnvVal2CoordWidth(prm_before_val - prm_after_val + getVal());
        setValByCoordWidth(total_damage_width);
    } else {
        damege_disp_timer_ = 60; //赤表示時間(間隔が開いてから)
        //ALIGN_RIGHT であるので、右端の x 座標を求め更新。
        coord before_bar_width = cnvVal2CoordWidth(prm_before_val);
        _x = pSourceBar_->_x + before_bar_width;
        is_damege_disp_ = true;
        //初回のみこの表示で良い
        coord damage_width = cnvVal2CoordWidth(prm_before_val - prm_after_val);
        setValByCoordWidth(damage_width);
    }

}

DamageDispBar::~DamageDispBar() {
}
