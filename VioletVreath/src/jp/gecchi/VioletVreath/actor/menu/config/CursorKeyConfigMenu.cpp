#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;


CursorKeyConfigMenu::CursorKeyConfigMenu(const char* prm_name) : DefaultBoardActor(prm_name, "Cursor001") {
    _class_name = "CursorKeyConfigMenu";
}
void CursorKeyConfigMenu::initialize() {
    _pUvFlipper->exec(FLIP_OSCILLATE_LOOP, 10);
}

void CursorKeyConfigMenu::onActive() {
}

void CursorKeyConfigMenu::processBehavior() {
    _pUvFlipper->behave();
}

void CursorKeyConfigMenu::processJudgement() {
}

CursorKeyConfigMenu::~CursorKeyConfigMenu() {
}
