#include "PointerTest.h"

#include "jp/ggaf/dx/actor/supporter/AlphaFader.h"
#include "jp/ggaf/dx/actor/supporter/Scaler.h"
#include "jp/ggaf/dx/actor/supporter/VecVehicle.h"
#include "jp/ggaf/dx/actor/supporter/SeTransmitterForActor.h"
#include "jp/ggaf/dx/actor/supporter/UvFlipper.h"
#include "jp/ggaf/lib/util/CollisionChecker.h"
#include "jp/ggaf/dx/util/curve/VehicleLeader.h"
#include "jp/ggaf/lib/actor/DefaultGeometricActor.h"
#include "jp/ggaf/dx/util/Input.h"
#include "actor/PointerTest.h"
#include "MgrCaretaker.h"
#include "jp/ggaf/lib/util/VirtualButton.h"


using namespace GgafLib;
using namespace Mogera;


PointerTest::PointerTest(const char* prm_name) :
        PointerActor(prm_name, "Cur") {
    _class_name = "PointerTest";
}

void PointerTest::onCreateModel() {
}

void PointerTest::initialize() {
}

void PointerTest::onActive() {
}

void PointerTest::processBehavior() {
    VirtualButton* pVb = P_CARETAKER->getSpacetime()->pVb_;
    getUvFlipper()->behave();
//    getScaler()->behave();
}

void PointerTest::processJudgement() {
}

void PointerTest::onHit(const GgafCore::Actor* prm_pOtherActor) {

}

void PointerTest::onInactive() {
}

PointerTest::~PointerTest() {
}


