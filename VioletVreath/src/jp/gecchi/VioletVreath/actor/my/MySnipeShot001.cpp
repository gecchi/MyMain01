#include "MySnipeShot001.h"

#include "jp/ggaf/dx/actor/supporter/Kuroko.h"
#include "jp/ggaf/dx/actor/supporter/SeTransmitterForActor.h"
#include "jp/ggaf/lib/util/CollisionChecker.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"



using namespace GgafLib;
using namespace VioletVreath;

MySnipeShot001::MySnipeShot001(const char* prm_name) :
        SingleLaser(prm_name, "MySnipeShot001") { //SingleLaserは最大27セットである
    _class_name = "MySnipeShot001";
    getStatus()->reset(statusResetFunction(MySnipeShot001));
}

void MySnipeShot001::initialize() {
    setHitAble(false);
    setScaleR(4.0);
    setCullingDraw(false);
    CollisionChecker* pChecker = getCollisionChecker();
    pChecker->createCollisionArea(1);
    pChecker->setColliAABox(0, -PX_C(80), -PX_C(5), -PX_C(5),
                                PX_C(80),  PX_C(5),  PX_C(5));
    getKuroko()->setRollFaceAngVelo(D_ANG(12));
    getKuroko()->linkFaceAngByMvAng(true);
}

void MySnipeShot001::onActive() {
    getStatus()->reset();
    setHitAble(true);
}

void MySnipeShot001::processBehavior() {
    getKuroko()->behave();
}

void MySnipeShot001::processJudgement() {
    if (isOutOfSpacetime()) {
        sayonara();
    }
}

void MySnipeShot001::onHit(const GgafCore::Actor* prm_pOtherActor) {
    GgafDx::GeometricActor* pOther = (GgafDx::GeometricActor*)prm_pOtherActor;
    setHitAble(false);
    UTIL::activateExplosionEffectOf(this);
    sayonara(); //貫通しない
}


//void MySnipeShot001::drawHitArea() {
//    CollisionChecker::drawHitArea(_pColliChecker);
//}
MySnipeShot001::~MySnipeShot001() {
}
