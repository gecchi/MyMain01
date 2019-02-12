#include "CursorNameEntryMenu.h"

#include "jp/ggaf/dx/actor/supporter/UvFlipper.h"



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
