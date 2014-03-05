#include "stdafx.h"
#include "CursorConfig002.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxUvFlipper.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

CursorConfig002::CursorConfig002(const char* prm_name) : DefaultBoardActor(prm_name, "Cursor001") {
    _class_name = "CursorConfig002";
}
void CursorConfig002::initialize() {
    _pUvFlipper->exec(FLIP_OSCILLATE_LOOP, 10);
}

void CursorConfig002::onActive() {
}

void CursorConfig002::processBehavior() {
    _pUvFlipper->behave();
}

void CursorConfig002::processJudgement() {
}

CursorConfig002::~CursorConfig002() {
}
