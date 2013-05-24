#include "stdafx.h"
#include "CursorTitleMenu.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxUvFlipper.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;


CursorTitleMenu::CursorTitleMenu(const char* prm_name) : DefaultBoardActor(prm_name, "Cursor001") {
    _class_name = "CursorTitleMenu";
}
void CursorTitleMenu::initialize() {
    _pUvFlipper->exec(FLIP_OSCILLATE_LOOP, 10);
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
