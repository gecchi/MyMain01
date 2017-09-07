#include "MpBar.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxUvFlipper.h"
#include "jp/ggaf/lib/util/Quantity.hpp"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

MpBar::MpBar(const char* prm_name)
      : FramedHorizontalBarActor(prm_name, "TurboMeter") {
    _class_name = "MpBar";
}

void MpBar::initialize() {
    setAlign(ALIGN_LEFT, VALIGN_MIDDLE);
//    getUvFlipper()->exec(FLIP_ORDER_LOOP, 10); //ƒAƒjƒ‡˜
}

MpBar::~MpBar() {
}
