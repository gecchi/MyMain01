#include "CursorSelectMenu.h"

#include "jp/ggaf/dx/actor/supporter/UvFlipper.h"



using namespace GgafLib;
using namespace VioletVreath;


CursorSelectMenu::CursorSelectMenu(const char* prm_name) : DefaultBoardActor(prm_name, "Cursor001") {
    _class_name = "CursorSelectMenu";
}
void CursorSelectMenu::initialize() {
    getUvFlipper()->exec(FLIP_OSCILLATE_LOOP, 10);
}

void CursorSelectMenu::onActive() {
}

void CursorSelectMenu::processBehavior() {
    getUvFlipper()->behave();
}

void CursorSelectMenu::processJudgement() {
}

CursorSelectMenu::~CursorSelectMenu() {
}
