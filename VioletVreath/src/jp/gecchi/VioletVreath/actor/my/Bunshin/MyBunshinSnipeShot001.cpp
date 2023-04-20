#include "MyBunshinSnipeShot001.h"

#include "jp/ggaf/dx/actor/supporter/LocoVehicle.h"
#include "jp/ggaf/dx/actor/supporter/SeTransmitterForActor.h"
#include "jp/ggaf/lib/util/WorldCollisionChecker.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"



using namespace GgafLib;
using namespace VioletVreath;

MyBunshinSnipeShot001::MyBunshinSnipeShot001(const char* prm_name) :
        VvMyActor<SingleLaser>(prm_name, "MyBunshinSnipeShot001", StatusReset(MyBunshinSnipeShot001)) { //SingleLaserは最大27セットである
    _class_name = "MyBunshinSnipeShot001";
}

void MyBunshinSnipeShot001::initialize() {
    setHitAble(false);
    setScaleR(4.0);
    setCullingDraw(false);
    WorldCollisionChecker* pChecker = getWorldCollisionChecker();
    pChecker->addCollisionArea(1);
    pChecker->setColliAABox(0, -PX_C(50), -PX_C(50), -PX_C(50),
                              PX_C(50),  PX_C(50),  PX_C(50));
    getLocoVehicle()->setRollFaceAngVelo(D_ANG(12));
    getLocoVehicle()->linkFaceAngByMvAng(true);
}

void MyBunshinSnipeShot001::onActive() {
    getStatus()->reset();
    setHitAble(true);
}

void MyBunshinSnipeShot001::processBehavior() {
    getLocoVehicle()->behave();
}

void MyBunshinSnipeShot001::processJudgement() {
    if (isOutOfSpacetime()) {
        sayonara();
    }
}

void MyBunshinSnipeShot001::onHit(const GgafCore::Actor* prm_pOtherActor) {
    setHitAble(false);
    UTIL::activateExplosionEffectOf(this);
    sayonara();
}


//void MyBunshinSnipeShot001::drawHitArea() {
//    WorldCollisionChecker::drawHitArea(_pColliCollisionChecker);
//}
MyBunshinSnipeShot001::~MyBunshinSnipeShot001() {
}
