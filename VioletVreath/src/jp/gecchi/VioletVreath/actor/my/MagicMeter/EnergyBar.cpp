#include "stdafx.h"
#include "EnergyBar.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxUvFlipper.h"
#include "jp/ggaf/lib/util/AmountGraph.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

EnergyBar::EnergyBar(const char* prm_name, AmountGraph* prm_pAmount)
      : GraphBar(prm_name, "TurboMeter", prm_pAmount) {
    _class_name = "EnergyBar";
}

void EnergyBar::initialize() {
//    _pUvFlipper->exec(FLIP_ORDER_LOOP, 10); //�A�j������
}


EnergyBar::~EnergyBar() {
}
