#include "stdafx.h"
#include "CursorPauseMenu.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxUvFlipper.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;


CursorPauseMenu::CursorPauseMenu(const char* prm_name) : DefaultBoardActor(prm_name, "Cursor001") {
    _class_name = "CursorPauseMenu";
}
void CursorPauseMenu::initialize() {
    _pUvFlipper->exec(FLIP_OSCILLATE_LOOP, 10);
}

void CursorPauseMenu::onActive() {
}

void CursorPauseMenu::processBehavior() {
    _pUvFlipper->behave();
}

void CursorPauseMenu::processJudgement() {
}

CursorPauseMenu::~CursorPauseMenu() {
}
