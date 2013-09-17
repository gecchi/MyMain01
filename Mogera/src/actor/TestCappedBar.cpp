#include "stdafx.h"
#include "TestCappedBar.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxUvFlipper.h"
#include "jp/ggaf/lib/util/PxQuantity.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoA.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace Mogera;

TestCappedBar::TestCappedBar(const char* prm_name)
      : GraphCappedBarActor(prm_name, "TestBar") {
    _class_name = "TestCappedBar";
    setAlpha(0.8);
}

void TestCappedBar::initialize() {
    setScaleR(2.0);
//    _pKurokoA->setFaceAngVelo(AXIS_Z, D_ANG(1));
//    _pUvFlipper->exec(FLIP_ORDER_LOOP, 10); //ƒAƒjƒ‡˜
}
void TestCappedBar::processBehavior() {
//    _pKurokoA->behave();
//    _pUvFlipper->behave();
}
TestCappedBar::~TestCappedBar() {
}

