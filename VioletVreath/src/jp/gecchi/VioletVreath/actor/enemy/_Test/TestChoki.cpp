#include "TestChoki.h"

#include "jp/ggaf/dx/actor/supporter/LocusVehicle.h"
#include "jp/ggaf/dx/actor/supporter/SeTransmitterForActor.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"

using namespace GgafLib;
using namespace VioletVreath;

TestChoki::TestChoki(const char* prm_name) : TestEnemy(prm_name, "TestChoki", StatusReset(TestChoki)) {
    _class_name = "TestChoki";
}

void TestChoki::onActive() {
    getStatus()->reset();
}

void TestChoki::processBehavior() {
    getLocusVehicle()->behave();
    dispStamina();
}

void TestChoki::processJudgement() {
    if (isOutOfSpacetime()) {
        sayonara();
    }
}

TestChoki::~TestChoki() {
}
