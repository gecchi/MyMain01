#include <jp/gecchi/VioletVreath/actor/menu/MousePointer.h>
#include "jp/ggaf/dx/actor/supporter/AlphaFader.h"
#include "jp/ggaf/dx/actor/supporter/Scaler.h"
#include "jp/ggaf/dx/actor/supporter/SeTransmitterForActor.h"
#include "jp/ggaf/dx/actor/supporter/UvFlipper.h"
#include "jp/ggaf/dx/actor/supporter/VecVehicle.h"
#include "jp/ggaf/dx/util/Input.h"
#include "jp/ggaf/dx/util/curve/VehicleLeader.h"
#include "jp/ggaf/lib/actor/DefaultGeometricActor.h"
#include "jp/ggaf/lib/util/CollisionChecker.h"
#include "jp/ggaf/lib/util/CollisionChecker2D_b.h"
#include "jp/ggaf/lib/util/VirtualButton.h"
#include "jp/gecchi/VioletVreath/Caretaker.h"

using namespace GgafLib;
using namespace VioletVreath;


MousePointer::MousePointer(const char* prm_name) :
        MousePointerActor(prm_name, "MousePointer") {
    _class_name = "MousePointer";

    setAlign(ALIGN_CENTER, VALIGN_MIDDLE);
    CollisionChecker2D_b* pChecker = getCollisionChecker();
    pChecker->createCollisionArea(1);
    //pChecker->setColliAABox(0, 0.8);
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
//    getScaler()->behave();
}

void MousePointer::processJudgement() {
}

void MousePointer::onHit(const GgafCore::Actor* prm_pOtherActor) {
_TRACE_("マウスがひっとおお！！！！！！！！！！！！！！！！！！！！！！！！！！！！");
MousePointerActor::onHit(prm_pOtherActor);
}

void MousePointer::onInactive() {
}

MousePointer::~MousePointer() {
}

