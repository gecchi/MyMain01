#include "SingleLaserTestActor.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

SingleLaserTestActor::SingleLaserTestActor(const char* prm_name) :
        SingleLaser(prm_name, "_chk_SingleLaserTestModel", nullptr) {
    _class_name = "SingleLaserTestActor";
}

void SingleLaserTestActor::initialize() {
    setHitAble(false);
}
void SingleLaserTestActor::onReset() {
}

void SingleLaserTestActor::onActive() {
}

void SingleLaserTestActor::processBehavior() {
}

void SingleLaserTestActor::processJudgement() {
}

void SingleLaserTestActor::onHit(const GgafActor* prm_pOtherActor) {
}


SingleLaserTestActor::~SingleLaserTestActor() {
}
