#include "TestGu.h"

#include "jp/ggaf/dx/actor/supporter/SeTransmitterForActor.h"
#include "jp/ggaf/dx/actor/supporter/LocusVehicle.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"

using namespace GgafLib;
using namespace VioletVreath;

TestGu::TestGu(const char* prm_name)
      : TestEnemy(prm_name, "TestGu", StatusReset(TestGu)) {
    _class_name = "TestGu";
}

void TestGu::onActive() {
    getStatus()->reset();
}

void TestGu::processBehavior() {
    getLocusVehicle()->behave();
    dispStamina();
}

void TestGu::processJudgement() {
    if (isOutOfSpacetime()) {
        sayonara();
    }
}

TestGu::~TestGu() {
}
