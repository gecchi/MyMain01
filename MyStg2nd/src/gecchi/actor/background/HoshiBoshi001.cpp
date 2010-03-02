#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

HoshiBoshi001::HoshiBoshi001(const char* prm_name) :
DefaultPointSpriteActor(prm_name, "test") {
    _class_name = "HoshiBoshi001";
}

void HoshiBoshi001::initialize() {
    setHitAble(false);
}

void HoshiBoshi001::onActive() {
    _pUvFlipper->setFlipMethod(FLIP_ORDER_LOOP, 10);
}

void HoshiBoshi001::processBehavior() {
    _pUvFlipper->behave();
}

void HoshiBoshi001::processJudgement() {
}

HoshiBoshi001::~HoshiBoshi001() {
}
