#include "VvvGrid.h"

using namespace GgafLib;
using namespace VVViewer;

VvvGrid::VvvGrid(const char* prm_name) :
        GgafLib::DefaultSpriteActor(prm_name, "Grid") {
}

void VvvGrid::initialize() {
    setAlpha(0.6);
    setPosition(0,0);
}

void VvvGrid::processBehavior() {
}

VvvGrid::~VvvGrid() {
}
