#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;


CursorConfirmMenu::CursorConfirmMenu(const char* prm_name) : DefaultBoardActor(prm_name, "Cursor001") {
    _class_name = "CursorConfirmMenu";
}
void CursorConfirmMenu::initialize() {
    _pUvFlipper->exec(FLIP_OSCILLATE_LOOP, 10);
}

void CursorConfirmMenu::onActive() {
}

void CursorConfirmMenu::processBehavior() {
    _pUvFlipper->behave();
}

void CursorConfirmMenu::processJudgement() {
}

CursorConfirmMenu::~CursorConfirmMenu() {
}
