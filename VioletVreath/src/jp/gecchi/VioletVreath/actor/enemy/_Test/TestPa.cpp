#include "TestPa.h"

#include "jp/ggaf/dx/actor/supporter/SeTransmitterForActor.h"
#include "jp/ggaf/dx/actor/supporter/LocusVehicle.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"

using namespace GgafLib;
using namespace VioletVreath;

TestPa::TestPa(const char* prm_name)
      : TestEnemy(prm_name, "TestPa", StatusReset(TestPa)) {
    _class_name = "TestPa";
}

void TestPa::onActive() {
    getStatus()->reset();
}

void TestPa::processBehavior() {
    getLocusVehicle()->behave();
    dispStamina();
}

void TestPa::processJudgement() {
    if (isOutOfSpacetime()) {
        sayonara();
    }
}

TestPa::~TestPa() {
}
