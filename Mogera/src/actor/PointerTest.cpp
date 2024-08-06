#include "PointerTest.h"

#include "jp/ggaf/dx/actor/supporter/AlphaFader.h"
#include "jp/ggaf/dx/actor/supporter/Scaler.h"
#include "jp/ggaf/dx/actor/supporter/LocusVehicle.h"
#include "jp/ggaf/dx/actor/supporter/SeTransmitterForActor.h"
#include "jp/ggaf/dx/actor/supporter/UvFlipper.h"
#include "jp/ggaf/lib/util/WorldCollisionChecker.h"
#include "jp/ggaf/dx/util/curve/VehicleLeader.h"
#include "jp/ggaf/lib/actor/DefaultGeometricActor.h"
#include "jp/ggaf/dx/util/Input.h"
#include "actor/PointerTest.h"
#include "MgrCaretaker.h"
#include "jp/ggaf/lib/util/VirtualButton.h"
#include "jp/ggaf/lib/util/ViewCollisionChecker.h"

using namespace GgafLib;
using namespace Mogera;


PointerTest::PointerTest(const char* prm_name) :
        MousePointerActor(prm_name, "Cur") {
    _class_name = "PointerTest";

    setAlign(ALIGN_CENTER, VALIGN_MIDDLE);
    ViewCollisionChecker* pChecker = getViewCollisionChecker();
    pChecker->addCollisionArea(1);
    //pChecker->setColliAABox(0, 0.8);
    pChecker->setColliSquare(0, PX_C(16));
    setHitAble(true);

}

void PointerTest::onCreateModel() {
}

void PointerTest::initialize() {
}

void PointerTest::onActive() {
}

void PointerTest::processBehavior() {
    VirtualButton* pVb = pCARETAKER->getSpacetime()->pVb_;
//    getUvFlipper()->behave();
//    getScaler()->behave();
}

void PointerTest::processJudgement() {
}

void PointerTest::onHit(const GgafCore::Actor* prm_pOtherActor) {
_TRACE_("マウスがひっとおお！！！！！！！！！！！！！！！！！！！！！！！！！！！！");
}

void PointerTest::onInactive() {
}

PointerTest::~PointerTest() {
}

