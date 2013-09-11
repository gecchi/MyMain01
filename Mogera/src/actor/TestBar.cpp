#include "stdafx.h"
#include "TestBar.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxUvFlipper.h"
#include "jp/ggaf/lib/util/AmountGraph.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace Mogera;

TestBar::TestBar(const char* prm_name, AmountGraph* prm_pAmount)
      : GraphBarActor(prm_name, "TestBar", prm_pAmount) {
    _class_name = "TestBar";
}

void TestBar::initialize() {
    setScaleR(2.0);
//    _pUvFlipper->exec(FLIP_ORDER_LOOP, 10); //ƒAƒjƒ‡˜
}

TestBar::~TestBar() {
}

