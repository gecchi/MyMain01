#include "VvvGrid2.h"

#include "VvvCaretaker.h"
#include "scene/VvvSpacetime.h"
#include "actor/VvvCamera.h"

using namespace GgafLib;
using namespace VVViewer;

VvvGrid2::VvvGrid2(const char* prm_name) :
        GgafLib::DefaultBoardActor(prm_name, "Grid2") {
}

void VvvGrid2::initialize() {
    //setAlpha(0.6);
    //setAlign(ALIGN_CENTER, VALIGN_MIDDLE);
    setPosition(0,0);
}

void VvvGrid2::processBehavior() {
}

VvvGrid2::~VvvGrid2() {
}
