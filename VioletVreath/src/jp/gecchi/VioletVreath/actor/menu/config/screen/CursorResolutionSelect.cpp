#include "CursorResolutionSelect.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxUvFlipper.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;


CursorResolutionSelect::CursorResolutionSelect(const char* prm_name) : DefaultBoardActor(prm_name, "Cursor001") {
    _class_name = "CursorResolutionSelect";
}
void CursorResolutionSelect::initialize() {
    getUvFlipper()->exec(FLIP_OSCILLATE_LOOP, 10);
}

void CursorResolutionSelect::onActive() {
}

void CursorResolutionSelect::processBehavior() {
    getUvFlipper()->behave();
}

void CursorResolutionSelect::processJudgement() {
}

CursorResolutionSelect::~CursorResolutionSelect() {
}
