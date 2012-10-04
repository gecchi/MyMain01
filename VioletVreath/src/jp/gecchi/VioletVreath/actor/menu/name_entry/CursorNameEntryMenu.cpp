#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;


CursorNameEntryMenu::CursorNameEntryMenu(const char* prm_name) : DefaultBoardActor(prm_name, "Cursor001") {
    _class_name = "CursorNameEntryMenu";
}
void CursorNameEntryMenu::initialize() {
    _pUvFlipper->setFlipMethod(FLIP_OSCILLATE_LOOP, 10);
}

void CursorNameEntryMenu::onActive() {
}

void CursorNameEntryMenu::processBehavior() {
    _pUvFlipper->behave();
}

void CursorNameEntryMenu::processJudgement() {
}

CursorNameEntryMenu::~CursorNameEntryMenu() {
}
