#include "stdafx.h"
#include "VreathBar.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxUvFlipper.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

VreathBar::VreathBar(const char* prm_name)
      : GraphCappedBarActor(prm_name, "TurboMeter") {
    _class_name = "VreathBar";
}

void VreathBar::initialize() {
//    _pUvFlipper->exec(FLIP_ORDER_LOOP, 10); //�A�j������
}

VreathBar::~VreathBar() {
}

