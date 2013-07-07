#include "stdafx.h"
#include "MyVreath.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

MyVreath::MyVreath(const char* prm_name) :
        DefaultMeshActor(prm_name, "wave", nullptr) {
    _class_name = "MyVreath";
}

void MyVreath::initialize() {
}

void MyVreath::processBehavior() {
}

void MyVreath::processJudgement() {
}

void MyVreath::onHit(GgafActor* prm_pOtherActor) {
    sayonara();
}

void MyVreath::onInactive() {
}

MyVreath::~MyVreath() {
}

