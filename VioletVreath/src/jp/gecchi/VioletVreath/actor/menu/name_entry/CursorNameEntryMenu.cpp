#include "stdafx.h"
#include "CursorNameEntryMenu.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxUvFlipper.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;


CursorNameEntryMenu::CursorNameEntryMenu(const char* prm_name) : DefaultBoardActor(prm_name, "Cursor001") {
    _class_name = "CursorNameEntryMenu";
}

void CursorNameEntryMenu::initialize() {
    getUvFlipper()->exec(FLIP_OSCILLATE_LOOP, 10);
}

void CursorNameEntryMenu::onActive() {
}

void CursorNameEntryMenu::processBehavior() {
    getUvFlipper()->behave();
}

void CursorNameEntryMenu::processJudgement() {
}

CursorNameEntryMenu::~CursorNameEntryMenu() {
}
