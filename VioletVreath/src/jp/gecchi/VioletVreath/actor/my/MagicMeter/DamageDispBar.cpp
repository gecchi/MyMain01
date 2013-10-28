#include "stdafx.h"
#include "DamageDispBar.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxUvFlipper.h"
#include "jp/ggaf/lib/util/PxQuantity.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/MyShipScene.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

#define DAMAGE_DISP_DELAY (3*60)
DamageDispBar::DamageDispBar(const char* prm_name, GgafLib::GraphBarActor* prm_pTargetSourceBar)
      : GraphBarActor(prm_name, "CostDispBar") {
    _class_name = "DamageDispBar";
    pSourceBar_ = prm_pTargetSourceBar;
    damege_disp_timer_ = 0;
}

void DamageDispBar::initialize() {
    _pUvFlipper->exec(NOT_ANIMATED); //アニメ順序
    setAlpha(0.7);
}

void DamageDispBar::onReset() {
    positionAs(pSourceBar_);
    _sx = pSourceBar_->_sx;
    setQty(0);
    _pUvFlipper->setActivePtn(0);//赤
}

void DamageDispBar::onActive() {
    positionAs(pSourceBar_);
    _sx = pSourceBar_->_sx;
    setQty(0);
    _pUvFlipper->setActivePtn(0);//赤
}

void DamageDispBar::processBehavior() {
    if (damege_disp_timer_ > 0) {

        _x = pSourceBar_->_x + PX_C(pSourceBar_->getBarPx()); //pSourceBar_先端の座標

        _pUvFlipper->behave();

        damege_disp_timer_--;
    } else {
        //0へ向かう
        if (getQty() > 0) {
            incQty(-100);
            if (getQty() < 0) {
                setQty(0);
            }
        }
    }
}

void DamageDispBar::processJudgement() {
}

void DamageDispBar::onInactive() {
}

void DamageDispBar::addDamage(int prm_val) {
    incQty(prm_val);
    damege_disp_timer_ = DAMAGE_DISP_DELAY; //表示時間リセット
}

DamageDispBar::~DamageDispBar() {
}
