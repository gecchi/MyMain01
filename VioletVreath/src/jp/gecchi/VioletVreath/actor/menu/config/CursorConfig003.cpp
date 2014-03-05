#include "stdafx.h"
#include "CursorConfig003.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxUvFlipper.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

CursorConfig003::CursorConfig003(const char* prm_name) : DefaultBoardActor(prm_name, "Cursor001") {
    _class_name = "CursorConfig003";
}
void CursorConfig003::initialize() {
    _pUvFlipper->exec(FLIP_OSCILLATE_LOOP, 10);
}

void CursorConfig003::onActive() {
}

void CursorConfig003::processBehavior() {
    _pUvFlipper->behave();
}

void CursorConfig003::processJudgement() {
}

CursorConfig003::~CursorConfig003() {
}
