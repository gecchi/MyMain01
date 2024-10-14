#include "Shot002.h"

#include "jp/ggaf/dx/actor/supporter/LocusVehicle.h"
#include "jp/ggaf/dx/actor/supporter/Scaler.h"
#include "jp/ggaf/dx/actor/supporter/SeTransmitterForActor.h"
#include "jp/ggaf/lib/util/WorldCollisionChecker.h"
#include "jp/gecchi/VioletVreath/Caretaker.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/MyShipScene.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"



using namespace GgafLib;
using namespace VioletVreath;

Shot002::Shot002(const char* prm_name) :
        VvEnemyActor<DefaultMassMeshActor>(prm_name, "Flora", StatusReset(Shot002)) {
    _class_name = "Shot002";

    GgafDx::SeTransmitterForActor* pSeXmtr = getSeXmtr();
    pSeXmtr->set(0, "SE_EXPLOSION_002");
}

void Shot002::initialize() {
    WorldCollisionChecker* pChecker = getWorldCollisionChecker();
    pChecker->addCollisionArea(1);
    pChecker->setColliAABox(0, -50000, -50000, -50000, 50000, 50000, 50000);
}

void Shot002::onActive() {
    getStatus()->reset();
    setHitAble(true, false);
    setScale(2000);
    GgafDx::LocusVehicle* pLocusVehicle = getLocusVehicle();
    pLocusVehicle->linkFaceAngByMvAng(true);
    pLocusVehicle->setMvVelo(RF_Shot002_MvVelo(G_RANK));
    pLocusVehicle->setRollFaceAngVelo(RF_Shot002_AngVelo(G_RANK));
}

void Shot002::processBehavior() {
    GgafDx::LocusVehicle* pLocusVehicle = getLocusVehicle();
    if (getActiveFrame() == 70) {
        pLocusVehicle->turnMvAngTwd(pMYSHIP,
                              3000, 0,
                              TURN_CLOSE_TO, true);
    }

    if (getActiveFrame() > 70 && !pLocusVehicle->isTurningMvAng()) {
        pLocusVehicle->turnMvAngTwd(pMYSHIP,
                              100, 0,
                              TURN_CLOSE_TO, true);
    }
    //座標に反映
    pLocusVehicle->behave();
    getScaler()->behave();
    getSeXmtr()->behave();
}

void Shot002::processJudgement() {
    if (isOutOfSpacetime()) {
        sayonara();
    }
}

void Shot002::onHit(const GgafCore::Checker* prm_pOtherChecker, const GgafCore::Actor* prm_pOtherActor) {
    bool is_stamina_zero = performEnemyHit((const GgafDx::GeometricActor*)prm_pOtherActor);
    if (is_stamina_zero) {
        //破壊された時(スタミナ <= 0)
        getSeXmtr()->play3D(0);
        sayonara();
    } else {
        //破壊されなかった時(スタミナ > 0)
    }
}

Shot002::~Shot002() {
}
