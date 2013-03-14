#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

DamageDispBar::DamageDispBar(const char* prm_name, GraphBar* prm_pSourceBar, AmountGraph* prm_pDamageValue)
      : GraphBar(prm_name, "CostDispBar", prm_pDamageValue) {
    _class_name = "DamageDispBar";
    pSourceBar_ = prm_pSourceBar;

    for (int i = 0; i < DISP_DELAY; i++) {
        aInt_my_ship_stamina_history_[i] = 0;
        aInt_my_ship_damage_history_[i] = 0;
    }
    p_ = 0;
}

void DamageDispBar::initialize() {
    _pUvFlipper->setFlipMethod(NOT_ANIMATED); //�A�j������
    setAlpha(0.7);
}

void DamageDispBar::onReset() {
    setScaleR(0); //�������ɔ{���ŐL�΂�
    for (int i = 0; i < DISP_DELAY; i++) {
        aInt_my_ship_stamina_history_[i] = P_MYSHIP->_pStatus->get(STAT_Stamina);
        aInt_my_ship_damage_history_[i] = 0;
    }
    p_ = 0;
    pAmount_->set(0);
}

void DamageDispBar::onActive() {
}

void DamageDispBar::processBehavior() {

    aInt_my_ship_stamina_history_[p_] = P_MYSHIP->_pStatus->get(STAT_Stamina);
    aInt_my_ship_damage_history_[p_] = aInt_my_ship_stamina_history_[(int)(p_-1 < 0 ? DISP_DELAY-1 : p_-1)] - aInt_my_ship_stamina_history_[p_];
    pAmount_->inc(aInt_my_ship_damage_history_[p_] );
    pAmount_->dec(aInt_my_ship_damage_history_[(int)(p_+1 == DISP_DELAY ? 0 : p_+1)]);
    //p_+1�A�̈Ӗ��́A�Ō�(DISP_DELAY�t���[���O)�̃_���[�W
    p_++;
    if (p_ == DISP_DELAY) {
        p_ = 0;
    }
    if ( pAmount_->getPx() > 0) {
        //���̒l�̓_���[�W�L��\���B�僁�[�^�[�E�[����E�Ɍ������ĐԂŃ_���[�W���̒l�������悤�ɂ���B
        _pUvFlipper->setActivePtn(0);
        setAlpha(0.7);
        _X = pSourceBar_->_X + PX_C(pSourceBar_->pAmount_->getPx()); //�����[�^�̉E��[
        setScaleR(1.0*pAmount_->getPx() * rate_org_width_, 1.0); //�E�����ɔ{���ŐL�΂�
    } else {
        setAlpha(0);
//        //���̒l�͉񕜂�\���B�僁�[�^�[�E�[���獶�Ɍ������ĐŃ_���[�W�񕜂̒l�������悤�ɂ���B
//        _pUvFlipper->setActivePtn(1);
//        pixcoord px = pSourceBar_->pAmount_->getPx() -  (-pAmount_->getPx());
//        if (px > 0) {
//            _X = pSourceBar_->_X - PX_C(px);
//            setScaleR(-1.0*pAmount_->getPx() / org_width_, 1.0); //������(pAmount_->getPx()����)�ɔ{���ŐL�΂�
//        } else {
//            //�����[�^�[����͂͂ݏo�Ȃ��悤�ɂ���
//            _X = pSourceBar_->_X;
//            _SX = pSourceBar_->_SX;
//        }
    }
    _pUvFlipper->behave();
}

void DamageDispBar::processJudgement() {
}

void DamageDispBar::onInactive() {
}

void DamageDispBar::addDamageVal(int prm_val) {
}

DamageDispBar::~DamageDispBar() {
}
