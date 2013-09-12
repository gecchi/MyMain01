#include "stdafx.h"
#include "DamageDispBar.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxUvFlipper.h"
#include "jp/ggaf/lib/util/PxQuantity.h"
#include "jp/gecchi/VioletVreath/actor/my/MagicMeter/GraphBar.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/MyShipScene.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

DamageDispBar::DamageDispBar(const char* prm_name, GraphBar* prm_pSourceBar, PxQuantity* prm_pDamageValue)
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
    _pUvFlipper->exec(NOT_ANIMATED); //アニメ順序
    setAlpha(0.7);
}

void DamageDispBar::onReset() {
    setScaleR(0); //横方向に倍率で伸ばす
    for (int i = 0; i < DISP_DELAY; i++) {
        aInt_my_ship_stamina_history_[i] = P_MYSHIP->_pStatus->get(STAT_Stamina);
        aInt_my_ship_damage_history_[i] = 0;
    }
    p_ = 0;
    pPxQuantity_->set(0);
}

void DamageDispBar::onActive() {
}

void DamageDispBar::processBehavior() {

    aInt_my_ship_stamina_history_[p_] = P_MYSHIP->_pStatus->get(STAT_Stamina);
    aInt_my_ship_damage_history_[p_] = aInt_my_ship_stamina_history_[(int)(p_-1 < 0 ? DISP_DELAY-1 : p_-1)] - aInt_my_ship_stamina_history_[p_];
    pPxQuantity_->inc(aInt_my_ship_damage_history_[p_] );
    pPxQuantity_->dec(aInt_my_ship_damage_history_[(int)(p_+1 == DISP_DELAY ? 0 : p_+1)]);
    //p_+1、の意味は、最古(DISP_DELAYフレーム前)のダメージ
    p_++;
    if (p_ == DISP_DELAY) {
        p_ = 0;
    }
    if ( pPxQuantity_->getPx() > 0) {
        //正の値はダメージ有り表す。主メーター右端から右に向かって赤でダメージ分の値を示すようにする。
        _pUvFlipper->setActivePtn(0);
        setAlpha(0.7);
        _X = pSourceBar_->_X + PX_C(pSourceBar_->pPxQuantity_->getPx()); //元メータの右先端
        setScaleR(1.0*pPxQuantity_->getPx() * rate_org_width_, 1.0); //右方向に倍率で伸ばす
    } else {
        setAlpha(0);
//        //負の値は回復を表す。主メーター右端から左に向かって青でダメージ回復の値を示すようにする。
//        _pUvFlipper->setActivePtn(1);
//        pixcoord px = pSourceBar_->pPxQuantity_->getPx() -  (-pPxQuantity_->getPx());
//        if (px > 0) {
//            _X = pSourceBar_->_X - PX_C(px);
//            setScaleR(-1.0*pPxQuantity_->getPx() / org_width_, 1.0); //左方向(pPxQuantity_->getPx()が負)に倍率で伸ばす
//        } else {
//            //元メーターからははみ出ないようにする
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
