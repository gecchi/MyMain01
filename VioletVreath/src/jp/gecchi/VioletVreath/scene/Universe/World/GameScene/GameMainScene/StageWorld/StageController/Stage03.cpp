#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

Stage03::Stage03(const char* prm_name) : Stage(prm_name) {
    _class_name = "Stage03";
}

void Stage03::initialize() {
    CmRandomNumberGenerator::getInstance()->changeSeed(P_MYSHIP->_Y);
}

void Stage03::processBehavior() {
}

Stage03::~Stage03() {
}
