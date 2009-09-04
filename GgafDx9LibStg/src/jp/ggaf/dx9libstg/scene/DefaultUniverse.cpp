#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;

DefaultUniverse::DefaultUniverse(const char* prm_name) : GgafDx9Universe(prm_name) {
    _class_name = "DefaultUniverse";
}

void DefaultUniverse::nextFrame() {
    GgafDx9Core::GgafDx9Universe::nextFrame();
}

DefaultUniverse::~DefaultUniverse() {
}
