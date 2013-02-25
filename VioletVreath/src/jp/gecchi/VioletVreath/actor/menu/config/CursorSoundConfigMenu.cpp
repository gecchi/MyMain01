#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;


CursorSoundConfigMenu::CursorSoundConfigMenu(const char* prm_name) : DefaultBoardActor(prm_name, "Cursor001") {
    _class_name = "CursorSoundConfigMenu";
}
void CursorSoundConfigMenu::initialize() {
    _pUvFlipper->setFlipMethod(FLIP_OSCILLATE_LOOP, 10);
}

void CursorSoundConfigMenu::onActive() {
}

void CursorSoundConfigMenu::processBehavior() {
    _pUvFlipper->behave();
}

void CursorSoundConfigMenu::processJudgement() {
}

CursorSoundConfigMenu::~CursorSoundConfigMenu() {
}
