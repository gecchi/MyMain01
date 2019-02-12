#include "MyBunshinSnipeShot001.h"

#include "jp/ggaf/dx/actor/supporter/Kuroko.h"
#include "jp/ggaf/dx/actor/supporter/SeTransmitterForActor.h"
#include "jp/ggaf/lib/util/CollisionChecker.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"



using namespace GgafLib;
using namespace VioletVreath;

MyBunshinSnipeShot001::MyBunshinSnipeShot001(const char* prm_name) :
        SingleLaser(prm_name, "MyBunshinSnipeShot001", STATUS(MyBunshinSnipeShot001)) { //SingleLaserは最大27セットである
    _class_name = "MyBunshinSnipeShot001";
}

void MyBunshinSnipeShot001::initialize() {
    setHitAble(false);
    setScaleR(4.0);
    setCullingDraw(false);
    CollisionChecker* pChecker = getCollisionChecker();
    pChecker->createCollisionArea(1);
    pChecker->setColliAABox(0, -PX_C(50), -PX_C(50), -PX_C(50),
                              PX_C(50),  PX_C(50),  PX_C(50));
    getKuroko()->setRollFaceAngVelo(D_ANG(12));
    getKuroko()->linkFaceAngByMvAng(true);
}

void MyBunshinSnipeShot001::onActive() {
    getStatus()->reset();
    setHitAble(true);
}

void MyBunshinSnipeShot001::processBehavior() {
    getKuroko()->behave();
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
//    CollisionChecker::drawHitArea(_pColliChecker);
//}
MyBunshinSnipeShot001::~MyBunshinSnipeShot001() {
}
