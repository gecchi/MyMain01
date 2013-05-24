#include "stdafx.h"
#include "CursorConfigMenu.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxUvFlipper.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;


CursorConfigMenu::CursorConfigMenu(const char* prm_name) : DefaultBoardActor(prm_name, "Cursor001") {
    _class_name = "CursorConfigMenu";
}
void CursorConfigMenu::initialize() {
    _pUvFlipper->exec(FLIP_OSCILLATE_LOOP, 10);
}

void CursorConfigMenu::onActive() {
}

void CursorConfigMenu::processBehavior() {
    _pUvFlipper->behave();
}

void CursorConfigMenu::processJudgement() {
}

CursorConfigMenu::~CursorConfigMenu() {
}
