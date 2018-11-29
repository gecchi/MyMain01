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
    getUvFlipper()->exec(NOT_ANIMATED); //�A�j������
    setAlpha(1.0);
    setAlign(ALIGN_RIGHT);
}

void DamageDispBar::onReset() {
    setPositionAt(pSourceBar_);
    setHeight(pSourceBar_->getHeight());
    setVal(0);
    getUvFlipper()->setActivePtn(0);//��
}

void DamageDispBar::onActive() {
    setPositionAt(pSourceBar_);
    setHeight(pSourceBar_->getHeight());
    setVal(0);
    getUvFlipper()->setActivePtn(0);//��
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
            damege_disp_timer_ = 20; //20F�ȓ��͘A���_���[�W�ƍl���ĉ��Z�\������
        }
        coord total_damage_width = cnvVal2CoordWidth(prm_before_val - prm_after_val + getVal());
        setValByCoordWidth(total_damage_width);
    } else {
        damege_disp_timer_ = 60; //�ԕ\������(�Ԋu���J���Ă���)
        //ALIGN_RIGHT �ł���̂ŁA�E�[�� x ���W�����ߍX�V�B
        coord before_bar_width = cnvVal2CoordWidth(prm_before_val);
        _x = pSourceBar_->_x + before_bar_width;
        is_damege_disp_ = true;
        //����݂̂��̕\���ŗǂ�
        coord damage_width = cnvVal2CoordWidth(prm_before_val - prm_after_val);
        setValByCoordWidth(damage_width);
    }

}

DamageDispBar::~DamageDispBar() {
}
