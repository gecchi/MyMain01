#include "MyShot001.h"

#include "jp/ggaf/dx/actor/supporter/LocusVehicle.h"
#include "jp/ggaf/dx/actor/supporter/SeTransmitterForActor.h"
#include "jp/ggaf/lib/util/WorldCollisionChecker.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/MyShipScene.h"

using namespace GgafLib;
using namespace VioletVreath;

MyShot001::MyShot001(const char* prm_name) :
        VvMyActor<SingleLaser>(prm_name, "MyShot001", StatusReset(MyShot001)) { //SingleLaserは最大27セットである
    _class_name = "MyShot001";
}

void MyShot001::initialize() {
    setHitAble(false);
    _sx = R_SC(45);
    _sy = _sz = R_SC(35);
    setBoundingSphereRadiusRate(45.0f);
    setCullingDraw(false);
    WorldCollisionChecker* pChecker = getWorldCollisionChecker();
    pChecker->addCollisionArea(1);
    pChecker->setColliAABox(0, -PX_C(50), -PX_C(50), -PX_C(50),
                                PX_C(50),  PX_C(50),  PX_C(50));

    // 拡張
    WorldCollisionChecker* pExChecker = (WorldCollisionChecker*)pChecker->addExChecker(KIND_CHECK_CHIKEI_HIT);
    pExChecker->addCollisionArea(1);
    //自機 pChecker->setColliAACube(0, PX_C(40));
    pExChecker->setColliAACube(0, PX_C(40));

    getLocusVehicle()->setRollFaceAngVelo(D_ANG(12));
    getLocusVehicle()->linkFaceAngByMvAng(true);
}

void MyShot001::onActive() {
    getStatus()->reset();
    setHitAble(true);
}

void MyShot001::processBehavior() {
    getLocusVehicle()->behave();
}

void MyShot001::processJudgement() {
    if (isOutOfSpacetime()) {
        sayonara();
    }
}

void MyShot001::onHit(const GgafCore::Checker* prm_pThisHitChecker, const GgafCore::Checker* prm_pOppHitChecker) {
    GgafDx::GeometricActor* pOther = (GgafDx::GeometricActor*)(prm_pOppHitChecker->_pActor);
    setHitAble(false);
    UTIL::activateCommonEffectOf(this, STAT_ExplosionEffectKind);
    sayonara();
}


//void MyShot001::drawHitArea() {
//    WorldCollisionChecker::drawHitArea(_pWorldCollisionChecker);
//}
MyShot001::~MyShot001() {
}
