#include "HoshiBoshiRankUp.h"

#include "jp/ggaf/dx/actor/supporter/UvFlipper.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/MyShipScene.h"



using namespace GgafLib;
using namespace VioletVreath;

HoshiBoshiRankUp::HoshiBoshiRankUp(const char* prm_name) :
        HoshiBoshi(prm_name, "HoshiBoshiRankUp") {
    _class_name = "HoshiBoshiRankUp";
}

void HoshiBoshiRankUp::initialize() {
    setFarRate(1.0f);
    setCriteriaActor(pMYSHIP);
}

void HoshiBoshiRankUp::onActive() {
    getUvFlipper()->exec(FLIP_ORDER_LOOP, 36);
}

void HoshiBoshiRankUp::processBehavior() {
    _x += 90000*getFarRate();

    getUvFlipper()->behave();
}

void HoshiBoshiRankUp::processJudgement() {
}


HoshiBoshiRankUp::~HoshiBoshiRankUp() {
}
