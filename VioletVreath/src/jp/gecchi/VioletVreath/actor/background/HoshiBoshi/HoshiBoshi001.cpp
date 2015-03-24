#include "HoshiBoshi001.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxUvFlipper.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/MyShipScene.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

HoshiBoshi001::HoshiBoshi001(const char* prm_name) :
        HoshiBoshi(prm_name, "HoshiBoshi001") {
    _class_name = "HoshiBoshi001";
}

void HoshiBoshi001::initialize() {
    setFarRate(30.0f);
    setCriteriaActor(P_MYSHIP);
}

void HoshiBoshi001::onActive() {
    getUvFlipper()->exec(FLIP_ORDER_LOOP, 6);
}

void HoshiBoshi001::processBehavior() {
    _x -= 1000*getFarRate();
    getUvFlipper()->behave();
}

void HoshiBoshi001::processJudgement() {
}

HoshiBoshi001::~HoshiBoshi001() {
}
