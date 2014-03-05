#include "stdafx.h"
#include "CursorConfig005.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxUvFlipper.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

CursorConfig005::CursorConfig005(const char* prm_name) : DefaultBoardActor(prm_name, "Cursor001") {
    _class_name = "CursorConfig005";
}
void CursorConfig005::initialize() {
    _pUvFlipper->exec(FLIP_OSCILLATE_LOOP, 10);
}

void CursorConfig005::onActive() {
}

void CursorConfig005::processBehavior() {
    _pUvFlipper->behave();
}

void CursorConfig005::processJudgement() {
}

CursorConfig005::~CursorConfig005() {
}
