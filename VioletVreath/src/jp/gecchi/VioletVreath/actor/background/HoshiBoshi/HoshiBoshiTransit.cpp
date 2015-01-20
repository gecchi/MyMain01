#include "HoshiBoshiTransit.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxUvFlipper.h"
#include "jp/gecchi/VioletVreath/scene/Universe.h"
#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/MyShipScene.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

HoshiBoshiTransit::HoshiBoshiTransit(const char* prm_name) :
        HoshiBoshi(prm_name, "HoshiBoshiTransit") {
    _class_name = "HoshiBoshiTransit";
}

void HoshiBoshiTransit::initialize() {
    setFarRate(10.0f);
    setCriteriaActor(P_MYSHIP);
}

void HoshiBoshiTransit::onActive() {
    getUvFlipper()->exec(FLIP_ORDER_LOOP, 6);
}

void HoshiBoshiTransit::processBehavior() {
    _x -= 90000*getFarRate();
    getUvFlipper()->behave();
}

void HoshiBoshiTransit::processJudgement() {
}


HoshiBoshiTransit::~HoshiBoshiTransit() {
}
