#include "CursorConfig002.h"

#include "jp/ggaf/dx/actor/supporter/UvFlipper.h"



using namespace GgafLib;
using namespace VioletVreath;

CursorConfig002::CursorConfig002(const char* prm_name) : DefaultBoardActor(prm_name, "Cursor001") {
    _class_name = "CursorConfig002";
}
void CursorConfig002::initialize() {
    getUvFlipper()->exec(FLIP_OSCILLATE_LOOP, 10);
}

void CursorConfig002::onActive() {
}

void CursorConfig002::processBehavior() {
    getUvFlipper()->behave();
}

void CursorConfig002::processJudgement() {
}

CursorConfig002::~CursorConfig002() {
}
