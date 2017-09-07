#include "VreathBar.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxUvFlipper.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

VreathBar::VreathBar(const char* prm_name)
      : FramedHorizontalBarActor(prm_name, "TurboMeter") {
    _class_name = "VreathBar";
}

void VreathBar::initialize() {
    setAlign(ALIGN_LEFT, VALIGN_MIDDLE);
//    getUvFlipper()->exec(FLIP_ORDER_LOOP, 10); //ƒAƒjƒ‡˜
}

VreathBar::~VreathBar() {
}

