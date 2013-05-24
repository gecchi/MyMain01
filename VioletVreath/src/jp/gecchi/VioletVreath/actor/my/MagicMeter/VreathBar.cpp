#include "stdafx.h"
#include "VreathBar.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxUvFlipper.h"
#include "jp/ggaf/lib/util/AmountGraph.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

VreathBar::VreathBar(const char* prm_name, AmountGraph* prm_pAmount)
      : GraphBar(prm_name, "TurboMeter", prm_pAmount) {
    _class_name = "VreathBar";
    pAmount_ = prm_pAmount;
}

void VreathBar::initialize() {
    _pUvFlipper->exec(FLIP_ORDER_LOOP, 10); //�A�j������
}

void VreathBar::onReset() {
    _SX = R_SC(pAmount_->getPx() * rate_org_width_); //�������ɔ{���ŐL�΂�
}

void VreathBar::onActive() {
}

void VreathBar::processBehavior() {
    _SX = R_SC(pAmount_->getPx() * rate_org_width_); //�������ɔ{���ŐL�΂�
    _pUvFlipper->behave();
}

void VreathBar::processJudgement() {
}

void VreathBar::onInactive() {
}

VreathBar::~VreathBar() {
}

