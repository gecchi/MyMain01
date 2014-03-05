#include "stdafx.h"
#include "CursorConfig004.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxUvFlipper.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

CursorConfig004::CursorConfig004(const char* prm_name) : DefaultBoardActor(prm_name, "Cursor001") {
    _class_name = "CursorConfig004";
}
void CursorConfig004::initialize() {
    _pUvFlipper->exec(FLIP_OSCILLATE_LOOP, 10);
}

void CursorConfig004::onActive() {
}

void CursorConfig004::processBehavior() {
    _pUvFlipper->behave();
}

void CursorConfig004::processJudgement() {
}

CursorConfig004::~CursorConfig004() {
}
