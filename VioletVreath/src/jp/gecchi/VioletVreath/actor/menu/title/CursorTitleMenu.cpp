#include "CursorTitleMenu.h"

#include "jp/ggaf/dx/actor/supporter/UvFlipper.h"



using namespace GgafLib;
using namespace VioletVreath;


CursorTitleMenu::CursorTitleMenu(const char* prm_name) : DefaultBoardActor(prm_name, "Cursor001") {
    _class_name = "CursorTitleMenu";
}
void CursorTitleMenu::initialize() {
    getUvFlipper()->exec(FLIP_OSCILLATE_LOOP, 10);
    setMaterialColor(0.2, 1.0, 0.2);
}

void CursorTitleMenu::onActive() {
}

void CursorTitleMenu::processBehavior() {
    getUvFlipper()->behave();
}

void CursorTitleMenu::processJudgement() {
}

CursorTitleMenu::~CursorTitleMenu() {
}
