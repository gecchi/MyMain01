#include "DamageDispBar.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxUvFlipper.h"
#include "jp/ggaf/lib/util/Quantity.hpp"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/MyShipScene.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

DamageDispBar::DamageDispBar(const char* prm_name, GgafLib::GraphBarActor* prm_pTargetSourceBar)
      : GraphBarActor(prm_name, "CostDispBar") {
    _class_name = "DamageDispBar";
    pSourceBar_ = prm_pTargetSourceBar;
    damege_disp_timer_ = 0;
    velo_clear_damege_ = -100;
    is_damege_disp_ = false;
}

void DamageDispBar::initialize() {
    getUvFlipper()->exec(NOT_ANIMATED); //�A�j������
    setAlpha(0.7);
}

void DamageDispBar::onReset() {
    placeAs(pSourceBar_);
    _sx = pSourceBar_->_sx;
    setVal(0);
    getUvFlipper()->setActivePtn(0);//��
}

void DamageDispBar::onActive() {
    placeAs(pSourceBar_);
    _sx = pSourceBar_->_sx;
    setVal(0);
    getUvFlipper()->setActivePtn(0);//��
}

void DamageDispBar::processBehavior() {
}

void DamageDispBar::processJudgement() {
    if (is_damege_disp_) {
        _x = pSourceBar_->_x + PX_C(pSourceBar_->getBarPx()); //pSourceBar_��[�̍��W
        getUvFlipper()->behave();
        damege_disp_timer_--;
        if (damege_disp_timer_ <= 0) {
            is_damege_disp_ = false;
        }
    } else {
        //0�֌�����
        if (getVal() > 0) {
            incVal(velo_clear_damege_);
            if (getVal() < 0) {
                setVal(0);
            }
        }
    }
}

void DamageDispBar::onInactive() {
}

void DamageDispBar::addDamage(int prm_val) {
    if (is_damege_disp_) {
        if (damege_disp_timer_ <= 20) {
            damege_disp_timer_ = 20; //�ԕ\������(�قژA���_���[�W)
        }
    } else {
        damege_disp_timer_ = 60; //�ԕ\������(�Ԋu���J���Ă���)
    }
    is_damege_disp_ = true;
    incVal(prm_val);
    velo_clear_damege_ = -1* ((getVal() / 20) + 1); //20�t���[���ł��邷����ƐԂ�������
}

DamageDispBar::~DamageDispBar() {
}
