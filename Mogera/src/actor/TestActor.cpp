#include "stdafx.h"
#include "actor/TestActor.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "util/MgrUtil.h"

using namespace Mogera;

TestActor::TestActor(const char* prm_name) :
        GgafLib::DefaultBoardActor(prm_name, "Grid") {
}

void TestActor::initialize() {
    setSpecialDrawDepth(MAX_DRAW_DEPTH_LEVEL);
    position(C_x, C_y);
    setAlign(ALIGN_CENTER, VALIGN_MIDDLE);
//    _pKuroko->setFaceAngVelo(AXIS_Z, D_ANG(1));
}

void TestActor::processBehavior() {
//    _pKuroko->behave(); //•ˆß‚ğŠˆ“®‚³‚¹‚éiZ²‰ñ“]‚·‚éj
}

TestActor::~TestActor() {
}
