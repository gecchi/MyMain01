#include "EnemyStraeaLaserChip001.h"

#include "jp/ggaf/dx/actor/supporter/SeTransmitterForActor.h"
#include "jp/ggaf/dx/actor/supporter/Rikisha.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/MyShipScene.h"



using namespace GgafLib;
using namespace VioletVreath;

EnemyStraeaLaserChip001::EnemyStraeaLaserChip001(const char* prm_name) :
        VvEnemyActor<HomingLaserChip>(prm_name, "StraeaLaserChip001", StatusReset(EnemyStraeaLaserChip001)) {
    _class_name = "EnemyStraeaLaserChip001";
}

void EnemyStraeaLaserChip001::initialize() {
    registerHitAreaCube_AutoGenMidColli(20000);
    setHitAble(true, false);
    setScaleR(5.0);
    setCullingDraw(false);
}

void EnemyStraeaLaserChip001::onActive() {
    HomingLaserChip::onActive();
    //ステータスリセット
    getStatus()->reset();
    GgafDx::Rikisha* const pRikisha = callRikisha();
    pRikisha->setMvVelo(10000);
    pRikisha->setMvAcce(400);
    pRikisha->linkFaceAngByMvAng(true);
}

void EnemyStraeaLaserChip001::processBehaviorHeadChip() {
    GgafDx::Rikisha* const pRikisha = callRikisha();
    if (getActiveFrame() == 40) {
        pRikisha->turnMvAngTwd(pMYSHIP,
                              7000, 0,
                              TURN_ANTICLOSE_TO, false);
    }
    if (!pRikisha->isTurningMvAng()) {
        pRikisha->turnMvAngTwd(pMYSHIP,
                              100, 0,
                              TURN_CLOSE_TO, false);
    }
//
//    if (frame_of_behaving_from_onActive_ == 35) {
//        pRikisha->turnMvAngTwd(
//                    pMYSHIP,
//                    20000, TURN_ANTICLOSE_TO);
//    }

    pRikisha->behave();
}

void EnemyStraeaLaserChip001::processJudgement() {
    if (isOutOfSpacetime()) {
        sayonara();
    }
}

void EnemyStraeaLaserChip001::onHit(const GgafCore::Actor* prm_pOtherActor) {
    bool was_destroyed = UTIL::performEnemyHit(this, (const GgafDx::GeometricActor*)prm_pOtherActor);
    if (was_destroyed) {
        //破壊された時(スタミナ <= 0)
        sayonara();
    } else {
        //破壊されなかった時(スタミナ > 0)
    }
}

EnemyStraeaLaserChip001::~EnemyStraeaLaserChip001() {

}

