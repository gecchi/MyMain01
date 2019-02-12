#include "HoshiBoshiTransit.h"

#include "jp/ggaf/dx/actor/supporter/UvFlipper.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/MyShipScene.h"



using namespace GgafLib;
using namespace VioletVreath;

HoshiBoshiTransit::HoshiBoshiTransit(const char* prm_name) :
        HoshiBoshi(prm_name, "HoshiBoshiTransit") {
    _class_name = "HoshiBoshiTransit";
}

void HoshiBoshiTransit::initialize() {
    setFarRate(10.0f);
    setCriteriaActor(pMYSHIP);
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
