#include "Shot002.h"

#include "jp/ggaf/dx/actor/supporter/VecDriver.h"
#include "jp/ggaf/dx/actor/supporter/Scaler.h"
#include "jp/ggaf/dx/actor/supporter/SeTransmitterForActor.h"
#include "jp/ggaf/lib/util/CollisionChecker.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/MyShipScene.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"



using namespace GgafLib;
using namespace VioletVreath;

Shot002::Shot002(const char* prm_name) :
        VvEnemyActor<DefaultMassMeshActor>(prm_name, "Flora", StatusReset(Shot002)) {
    _class_name = "Shot002";

    GgafDx::SeTransmitterForActor* pSeTx = getSeTransmitter();
    pSeTx->set(0, "WAVE_EXPLOSION_002");
}

void Shot002::initialize() {
    CollisionChecker* pChecker = getCollisionChecker();
    pChecker->createCollisionArea(1);
    pChecker->setColliAABox(0, -50000, -50000, -50000, 50000, 50000, 50000);
}

void Shot002::onActive() {
    getStatus()->reset();
    setHitAble(true, false);
    setScale(2000);
    GgafDx::VecDriver* const pVecDriver = callVecDriver();
    pVecDriver->linkFaceAngByMvAng(true);
    pVecDriver->setMvVelo(RF_Shot002_MvVelo(G_RANK));
    pVecDriver->setRollFaceAngVelo(RF_Shot002_AngVelo(G_RANK));
}

void Shot002::processBehavior() {
    GgafDx::VecDriver* const pVecDriver = callVecDriver();
    if (getActiveFrame() == 70) {
        pVecDriver->turnMvAngTwd(pMYSHIP,
                              3000, 0,
                              TURN_CLOSE_TO, true);
    }

    if (getActiveFrame() > 70 && !pVecDriver->isTurningMvAng()) {
        pVecDriver->turnMvAngTwd(pMYSHIP,
                              100, 0,
                              TURN_CLOSE_TO, true);
    }
    //座標に反映
    pVecDriver->behave();
    getScaler()->behave();
    getSeTransmitter()->behave();
}

void Shot002::processJudgement() {
    if (isOutOfSpacetime()) {
        sayonara();
    }
}

void Shot002::onHit(const GgafCore::Actor* prm_pOtherActor) {
    bool was_destroyed = UTIL::performEnemyHit(this, (const GgafDx::GeometricActor*)prm_pOtherActor);
    if (was_destroyed) {
        //破壊された時(スタミナ <= 0)
        getSeTransmitter()->play3D(0);
        sayonara();
    } else {
        //破壊されなかった時(スタミナ > 0)
    }
}

Shot002::~Shot002() {
}
