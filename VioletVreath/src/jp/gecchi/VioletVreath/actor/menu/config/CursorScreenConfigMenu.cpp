#include "stdafx.h"
#include "CursorScreenConfigMenu.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxUvFlipper.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

CursorScreenConfigMenu::CursorScreenConfigMenu(const char* prm_name) : DefaultBoardActor(prm_name, "Cursor001") {
    _class_name = "CursorScreenConfigMenu";
}
void CursorScreenConfigMenu::initialize() {
    _pUvFlipper->exec(FLIP_OSCILLATE_LOOP, 10);
}

void CursorScreenConfigMenu::onActive() {
}

void CursorScreenConfigMenu::processBehavior() {
    _pUvFlipper->behave();
}

void CursorScreenConfigMenu::processJudgement() {
}

CursorScreenConfigMenu::~CursorScreenConfigMenu() {
}
