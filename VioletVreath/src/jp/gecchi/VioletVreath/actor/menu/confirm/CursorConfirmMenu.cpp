#include "stdafx.h"
#include "CursorConfirmMenu.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxUvFlipper.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;


CursorConfirmMenu::CursorConfirmMenu(const char* prm_name) : DefaultBoardActor(prm_name, "Cursor001") {
    _class_name = "CursorConfirmMenu";
}
void CursorConfirmMenu::initialize() {
    getUvFlipper()->exec(FLIP_OSCILLATE_LOOP, 10);
}

void CursorConfirmMenu::onActive() {
}

void CursorConfirmMenu::processBehavior() {
    getUvFlipper()->behave();
}

void CursorConfirmMenu::processJudgement() {
}

CursorConfirmMenu::~CursorConfirmMenu() {
}
