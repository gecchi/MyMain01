#include "MyBunshinShot001.h"

#include "jp/ggaf/dx/actor/supporter/LocusVehicle.h"
#include "jp/ggaf/dx/actor/supporter/SeTransmitterForActor.h"
#include "jp/ggaf/lib/util/WorldCollisionChecker.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"

using namespace GgafLib;
using namespace VioletVreath;

MyBunshinShot001::MyBunshinShot001(const char* prm_name) :
        VvMyActor<SingleLaser>(prm_name, "MyBunshinShot001", StatusReset(MyBunshinShot001)) { //SingleLaser‚ÍÅ‘å27ƒZƒbƒg‚Å‚ ‚é
    _class_name = "MyBunshinShot001";
}

void MyBunshinShot001::initialize() {
    setHitAble(false);
    _sx = R_SC(45);
    _sy = _sz = R_SC(35);
    setBoundingSphereRadiusRate(45.0f);
    setCullingDraw(false);
    WorldCollisionChecker* pChecker = getWorldCollisionChecker();
    pChecker->addCollisionArea(1);
    pChecker->setColliAABox(0, -PX_C(50), -PX_C(50), -PX_C(50),
                              PX_C(50),  PX_C(50),  PX_C(50));
    getLocusVehicle()->setRollFaceAngVelo(D_ANG(-12));
    getLocusVehicle()->linkFaceAngByMvAng(true);
}

void MyBunshinShot001::onActive() {
    getStatus()->reset();
    setHitAble(true);
}

void MyBunshinShot001::processBehavior() {
    getLocusVehicle()->behave();
}

void MyBunshinShot001::processJudgement() {
    if (isOutOfSpacetime()) {
        sayonara();
    }
}

void MyBunshinShot001::onHit(const GgafCore::Checker* prm_pOtherChecker, const GgafCore::Actor* prm_pOtherActor) {
    setHitAble(false);
    UTIL::activateEffectOf(this, STAT_ExplosionEffectKind);
    sayonara();
}


//void MyBunshinShot001::drawHitArea() {
//    WorldCollisionChecker::drawHitArea(_pWorldCollisionChecker);
//}
MyBunshinShot001::~MyBunshinShot001() {
}
