#include "MyVreath.h"



using namespace GgafLib;
using namespace VioletVreath;

MyVreath::MyVreath(const char* prm_name) :
        DefaultMeshActor(prm_name, "wave") {
    _class_name = "MyVreath";
}

void MyVreath::initialize() {
}

void MyVreath::processBehavior() {
}

void MyVreath::processJudgement() {
}

void MyVreath::onHit(const GgafCore::Checker* prm_pThisHitChecker, const GgafCore::Checker* prm_pOppHitChecker) {
    sayonara();
}

void MyVreath::onInactive() {
}

MyVreath::~MyVreath() {
}

