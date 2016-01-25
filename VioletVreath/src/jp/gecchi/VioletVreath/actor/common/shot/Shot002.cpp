#include "Shot002.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxScaler.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxSeTransmitterForActor.h"
#include "jp/ggaf/lib/util/CollisionChecker3D.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/MyShipScene.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

Shot002::Shot002(const char* prm_name) :
        DefaultMeshSetActor(prm_name, "Flora", STATUS(Shot002)) {
    _class_name = "Shot002";
    pScaler_ = NEW GgafDxScaler(this);

    GgafDxSeTransmitterForActor* pSeTx = getSeTx();
    pSeTx->set(0, "WAVE_EXPLOSION_002");
}

void Shot002::initialize() {
    CollisionChecker3D* pChecker = getCollisionChecker();
    pChecker->createCollisionArea(1);
    pChecker->setColliAABox(0, -50000, -50000, -50000, 50000, 50000, 50000);
}

void Shot002::onActive() {
    getStatus()->reset();
    setHitAble(true);
    setScale(2000);
    GgafDxKuroko* const pKuroko = getKuroko();
    pKuroko->linkFaceAngByMvAng(true);
    pKuroko->setMvVelo(RF_Shot002_MvVelo(G_RANK));
    pKuroko->setRollFaceAngVelo(RF_Shot002_AngVelo(G_RANK));
}

void Shot002::processBehavior() {
    GgafDxKuroko* const pKuroko = getKuroko();
    if (getActiveFrame() == 70) {
        pKuroko->turnMvAngTwd(P_MYSHIP,
                              3000, 0,
                              TURN_CLOSE_TO, true);
    }

    if (getActiveFrame() > 70 && !pKuroko->isTurningMvAng()) {
        pKuroko->turnMvAngTwd(P_MYSHIP,
                              100, 0,
                              TURN_CLOSE_TO, true);
    }
    //座標に反映
    pKuroko->behave();
    pScaler_->behave();
    getSeTx()->behave();
}

void Shot002::processJudgement() {
    if (isOutOfSpacetime()) {
        sayonara();
    }
}

void Shot002::onHit(const GgafActor* prm_pOtherActor) {
    bool was_destroyed = UTIL::transactEnemyHit(this, (const GgafDxGeometricActor*)prm_pOtherActor);
    if (was_destroyed) {
        //破壊された時(スタミナ <= 0)
        getSeTx()->play3D(0);
        sayonara();
    } else {
        //破壊されなかった時(スタミナ > 0)
    }
}

Shot002::~Shot002() {
    GGAF_DELETE(pScaler_);
}
