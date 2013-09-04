#include "stdafx.h"
#include "actor/TestActor.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoA.h"
#include "util/MgrUtil.h"

using namespace Mogera;

TestActor::TestActor(const char* prm_name) :
        GgafLib::DefaultBoardActor(prm_name, "Grid") {
}

void TestActor::initialize() {
    position(C_X, C_Y);
    setAlign(ALIGN_CENTER, VALIGN_MIDDLE);
//    _pKurokoA->setFaceAngVelo(AXIS_Z, D_ANG(1));
}

void TestActor::processBehavior() {
//    _pKurokoA->behave(); //•ˆßA‚ğŠˆ“®‚³‚¹‚éiZ²‰ñ“]‚·‚éj
}

TestActor::~TestActor() {
}
