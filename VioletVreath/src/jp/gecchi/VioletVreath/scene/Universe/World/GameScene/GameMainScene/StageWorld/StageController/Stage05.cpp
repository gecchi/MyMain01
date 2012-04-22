#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

Stage05::Stage05(const char* prm_name) : Stage(prm_name) {
    _class_name = "Stage05";
}

void Stage05::initialize() {
    CmRandomNumberGenerator::getInstance()->changeSeed(P_MYSHIP->_Y);
}

void Stage05::processBehavior() {
}

Stage05::~Stage05() {
}
