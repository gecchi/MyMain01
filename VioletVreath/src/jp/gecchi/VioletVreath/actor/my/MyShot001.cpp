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

void MyShot001::onHit(const GgafCore::Actor* prm_pOtherActor) {
    GgafDx::GeometricActor* pOther = (GgafDx::GeometricActor*)prm_pOtherActor;
    if (pOther->getDefaultKind() & KIND_CHIKEI) {
        //ヒット相手が地形ならば自機の大きさで判定し、ヒットしなければ消失しない
        MyShip* pMyShip = pMYSHIP;
        WorldCollisionChecker* pMyShipChecker = pMyShip->getWorldCollisionChecker();
        coord x = pMyShip->_x;
        coord y = pMyShip->_y;
        coord z = pMyShip->_z;
        pMyShip->setPositionAt(this); //座標だけすげかえる
        WorldCollisionChecker* pOtherChecker = (WorldCollisionChecker*)pOther->getChecker();
        bool r = pOtherChecker->isHit(pMyShipChecker);
        pMyShip->_x = x;
        pMyShip->_y = y;
        pMyShip->_z = z;
        if (!r) {
            //自機の大きさで判定し、ヒットしないので無問題
            return;
        }
    }
    setHitAble(false);
    UTIL::activateExplosionEffectOf(this);
    sayonara(); //必ず貫通しない
}


//void MyShot001::drawHitArea() {
//    WorldCollisionChecker::drawHitArea(_pWorldCollisionChecker);
//}
MyShot001::~MyShot001() {
}
