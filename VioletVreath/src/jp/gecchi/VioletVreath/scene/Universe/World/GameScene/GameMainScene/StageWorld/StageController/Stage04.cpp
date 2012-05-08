#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

Stage04::Stage04(const char* prm_name) : Stage(prm_name) {
    _class_name = "Stage04";
}

void Stage04::initialize() {
    CmRandomNumberGenerator::getInstance()->changeSeed(P_MYSHIP->_Y);
}

void Stage04::processBehavior() {
}

Stage04::~Stage04() {
}
