#include "HoshiBoshiRankUp.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxUvFlipper.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/MyShipScene.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

HoshiBoshiRankUp::HoshiBoshiRankUp(const char* prm_name) :
        HoshiBoshi(prm_name, "HoshiBoshiRankUp") {
    _class_name = "HoshiBoshiRankUp";
}

void HoshiBoshiRankUp::initialize() {
    setFarRate(1.0f);
    setCriteriaActor(P_MYSHIP);
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
