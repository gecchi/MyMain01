#include "stdafx.h"
#include "SupCursorScreenConfigMenu.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxUvFlipper.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

SupCursorScreenConfigMenu::SupCursorScreenConfigMenu(const char* prm_name) : DefaultBoardActor(prm_name, "Cursor001") {
    _class_name = "SupCursorScreenConfigMenu";
}
void SupCursorScreenConfigMenu::initialize() {
    _pUvFlipper->exec(FLIP_OSCILLATE_LOOP, 10);
}

void SupCursorScreenConfigMenu::onActive() {
}

void SupCursorScreenConfigMenu::processBehavior() {
    _pUvFlipper->behave();
}

void SupCursorScreenConfigMenu::processJudgement() {
}

SupCursorScreenConfigMenu::~SupCursorScreenConfigMenu() {
}
