#include "MousePointer.h"

#include "jp/ggaf/dx/actor/supporter/AlphaFader.h"
#include "jp/ggaf/dx/actor/supporter/Scaler.h"
#include "jp/ggaf/dx/actor/supporter/SeTransmitterForActor.h"
#include "jp/ggaf/dx/actor/supporter/UvFlipper.h"
#include "jp/ggaf/dx/actor/supporter/LocoVehicle.h"
#include "jp/ggaf/dx/util/Input.h"
#include "jp/ggaf/dx/util/curve/VehicleLeader.h"
#include "jp/ggaf/lib/actor/DefaultGeometricActor.h"
#include "jp/ggaf/lib/util/WorldCollisionChecker.h"
#include "jp/ggaf/lib/util/ViewCollisionChecker.h"
#include "jp/ggaf/lib/util/VirtualButton.h"
#include "jp/gecchi/VioletVreath/Caretaker.h"

using namespace GgafLib;
using namespace VioletVreath;


MousePointer::MousePointer(const char* prm_name) :
        MousePointerActor(prm_name, "MousePointer") {
    _class_name = "MousePointer";

    setAlign(ALIGN_CENTER, VALIGN_MIDDLE);
    ViewCollisionChecker* pChecker = getViewCollisionChecker();
    pChecker->addCollisionArea(1);
    pChecker->setColliSquare(0, PX_C(16));
    setHitAble(true);
}

void MousePointer::onCreateModel() {
}

void MousePointer::initialize() {
}

void MousePointer::onActive() {
}

void MousePointer::processBehavior() {
    getUvFlipper()->behave();
}

void MousePointer::processJudgement() {
}

void MousePointer::onHit(const GgafCore::Actor* prm_pOtherActor) {
    MousePointerActor::onHit(prm_pOtherActor);
}

void MousePointer::onInactive() {
}

MousePointer::~MousePointer() {
}

