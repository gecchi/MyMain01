#include "stdafx.h"
#include "MpBar.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxUvFlipper.h"
#include "jp/ggaf/lib/util/PxQuantity.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

MpBar::MpBar(const char* prm_name)
      : CappedGraphBarActor(prm_name, "TurboMeter") {
    _class_name = "MpBar";
}

void MpBar::initialize() {
//    getUvFlipper()->exec(FLIP_ORDER_LOOP, 10); //�A�j������
}

MpBar::~MpBar() {
}
