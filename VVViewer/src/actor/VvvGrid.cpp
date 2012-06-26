#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VVViewer;

VvvGrid::VvvGrid(const char* prm_name) :
        GgafLib::DefaultSpriteActor(prm_name, "Grid") {
}

void VvvGrid::initialize() {
    setAlpha(0.6);
    locate(0,0,0);
}

void VvvGrid::processBehavior() {
}

VvvGrid::~VvvGrid() {
}
