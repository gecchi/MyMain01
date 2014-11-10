#include "CursorPauseMenu.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxUvFlipper.h"
#include "jp/ggaf/dxcore/util/GgafDxInput.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;


CursorPauseMenu::CursorPauseMenu(const char* prm_name) : DefaultBoardActor(prm_name, "Cursor001") {
    _class_name = "CursorPauseMenu";
}
void CursorPauseMenu::initialize() {
    getUvFlipper()->exec(FLIP_OSCILLATE_LOOP, 10);
}

void CursorPauseMenu::onActive() {
}

void CursorPauseMenu::processBehavior() {
    if (GgafDxCore::GgafDxInput::isBeingPressedKey(DIK_P)) {
        _TRACE_("Cursor:"<<getBehaveingFrame()<<":_x,_y,_z="<<_x<<","<<_y<<","<<_z<<"");
    }
    getUvFlipper()->behave();
}

void CursorPauseMenu::processJudgement() {
}

CursorPauseMenu::~CursorPauseMenu() {
}
