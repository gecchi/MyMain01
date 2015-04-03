#include "EnemyStraeaLaserChip001.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxSeTransmitterForActor.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/MyShipScene.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

EnemyStraeaLaserChip001::EnemyStraeaLaserChip001(const char* prm_name) :
        HomingLaserChip(prm_name, "StraeaLaserChip001", STATUS(EnemyStraeaLaserChip001)) {
    _class_name = "EnemyStraeaLaserChip001";
}

void EnemyStraeaLaserChip001::initialize() {
    registerHitAreaCube_AutoGenMidColli(20000);
    setHitAble(true, false);
    setScaleR(5.0);
    setAlpha(0.9);
}

void EnemyStraeaLaserChip001::onActive() {
    HomingLaserChip::onActive();
    //ステータスリセット
    getStatus()->reset();
    GgafDxKuroko* const pKuroko = getKuroko();
    pKuroko->setMvVelo(10000);
    pKuroko->setMvAcce(400);
    pKuroko->linkFaceAngByMvAng(true);
}

void EnemyStraeaLaserChip001::processBehaviorHeadChip() {
    GgafDxKuroko* const pKuroko = getKuroko();
    if (getActiveFrame() == 40) {
        pKuroko->turnMvAngTwd(P_MYSHIP,
                              7000, 0,
                              TURN_ANTICLOSE_TO, false);
    }
    if (!pKuroko->isTurningMvAng()) {
        pKuroko->turnMvAngTwd(P_MYSHIP,
                              100, 0,
                              TURN_CLOSE_TO, false);
    }
//
//    if (frame_of_behaving_from_onActive_ == 35) {
//        pKuroko->turnMvAngTwd(
//                    P_MYSHIP,
//                    20000, TURN_ANTICLOSE_TO);
//    }

    pKuroko->behave();
}

void EnemyStraeaLaserChip001::onHit(const GgafActor* prm_pOtherActor) {
    const bool was_destroyed = UTIL::transactEnemyHit(this, (const GgafDxGeometricActor*)prm_pOtherActor);
    if (was_destroyed) {
        //破壊された時(スタミナ <= 0)
        sayonara();
    } else {
        //破壊されなかった時(スタミナ > 0)
    }
}

EnemyStraeaLaserChip001::~EnemyStraeaLaserChip001() {

}

