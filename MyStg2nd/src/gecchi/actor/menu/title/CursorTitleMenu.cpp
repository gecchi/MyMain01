#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace MyStg2nd;


CursorTitleMenu::CursorTitleMenu(const char* prm_name) : DefaultBoardActor(prm_name, "Cursor001") {
    _class_name = "CursorTitleMenu";
}
void CursorTitleMenu::initialize() {
    _pUvFlipper->setFlipMethod(FLIP_OSCILLATE_LOOP, 10);
}

void CursorTitleMenu::onActive() {
}

void CursorTitleMenu::processBehavior() {
    _pUvFlipper->behave();
}

void CursorTitleMenu::processJudgement() {
}

CursorTitleMenu::~CursorTitleMenu() {
}
