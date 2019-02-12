#include "CursorConfig001.h"

#include "jp/ggaf/dx/actor/supporter/UvFlipper.h"



using namespace GgafLib;
using namespace VioletVreath;


CursorConfig001::CursorConfig001(const char* prm_name) : DefaultBoardActor(prm_name, "Cursor001") {
    _class_name = "CursorConfig001";
}
void CursorConfig001::initialize() {
    getUvFlipper()->exec(FLIP_OSCILLATE_LOOP, 10);
}

void CursorConfig001::onActive() {
}

void CursorConfig001::processBehavior() {
    getUvFlipper()->behave();
}

void CursorConfig001::processJudgement() {
}

CursorConfig001::~CursorConfig001() {
}
