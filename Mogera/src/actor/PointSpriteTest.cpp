#include "PointSpriteTest.h"

#include "jp/ggaf/dx/actor/supporter/UvFlipper.h"
#include "jp/ggaf/dx/actor/supporter/AlphaFader.h"
#include "jp/ggaf/dx/actor/supporter/LocoVehicle.h"
#include "jp/ggaf/dx/actor/supporter/Scaler.h"
#include "jp/ggaf/dx/actor/supporter/SeTransmitterForActor.h"
#include "jp/ggaf/lib/util/WorldCollisionChecker.h"
#include "jp/ggaf/dx/util/curve/VehicleLeader.h"
#include "jp/ggaf/lib/actor/DefaultGeometricActor.h"



using namespace GgafLib;
using namespace Mogera;

PointSpriteTest::PointSpriteTest(const char* prm_name) :
        DefaultPointSpriteSetActor(prm_name, "PTEST2") {
    _class_name = "PointSpriteTest";
//    effectBlendOne(); //‰ÁŽZ‡¬
    setAlpha(0.8);
    setHitAble(false);
}

int PointSpriteTest::isOutOfView() {
    //‰æ–ÊŠO”»’è–³‚µ
    return 0;
}

bool PointSpriteTest::isOutOfSpacetime() const {
    //ƒQ[ƒ€À•W”ÍˆÍŠO”»’è–³‚µ
    return false;
}
void PointSpriteTest::initialize() {
    getLocoVehicle()->setRollPitchYawFaceAngVelo(30, 50, 70);
    setScale(0);
    getScaler()->transitionAcceUntilVelo(-R_SC(0.01) , R_SC(0.1), -R_SC(0.001));
}

void PointSpriteTest::onActive() {
    getUvFlipper()->exec(FLIP_ORDER_LOOP, 1);
}

void PointSpriteTest::processBehavior() {
//    if (!pScaler_->isTransitioning()) {
//        sayonara();
//    }
    getUvFlipper()->behave();
    getLocoVehicle()->behave();
    getScaler()->behave();
}

void PointSpriteTest::processJudgement() {
}

PointSpriteTest::~PointSpriteTest() {
}
