#include "CursorConfig004.h"

#include "jp/ggaf/dx/actor/supporter/UvFlipper.h"



using namespace GgafLib;
using namespace VioletVreath;

CursorConfig004::CursorConfig004(const char* prm_name) : DefaultBoardActor(prm_name, "Cursor001") {
    _class_name = "CursorConfig004";
}
void CursorConfig004::initialize() {
    getUvFlipper()->exec(FLIP_OSCILLATE_LOOP, 10);
}

void CursorConfig004::onActive() {
}

void CursorConfig004::processBehavior() {
    getUvFlipper()->behave();
}

void CursorConfig004::processJudgement() {
}

CursorConfig004::~CursorConfig004() {
}
