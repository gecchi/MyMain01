#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

HoshiBoshi001::HoshiBoshi001(const char* prm_name) : DefaultPointSpriteSetActor(", "test") {
    _class_name = "HoshiBoshi001";
}

void HoshiBoshi001::initialize() {
    setHitAble(false);
}

void HoshiBoshi001::onActive() {
}

void HoshiBoshi001::processBehavior() {
}

void HoshiBoshi001::processJudgement() {
}

HoshiBoshi001::~HoshiBoshi001() {
}
