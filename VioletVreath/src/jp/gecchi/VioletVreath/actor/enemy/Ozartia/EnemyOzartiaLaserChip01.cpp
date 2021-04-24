#include "EnemyOzartiaLaserChip01.h"

#include "jp/ggaf/dx/actor/supporter/SeTransmitterForActor.h"
#include "jp/ggaf/dx/actor/supporter/VecDriver.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"



using namespace GgafLib;
using namespace VioletVreath;

EnemyOzartiaLaserChip01::EnemyOzartiaLaserChip01(const char* prm_name) :
        VvEnemyActor<StraightLaserChip>(prm_name, "EnemyOzartiaLaserChip01", StatusReset(EnemyOzartiaLaserChip01)) {
    _class_name = "EnemyOzartiaLaserChip01";
    setMvVelo(100000);
}

void EnemyOzartiaLaserChip01::initialize() {
    getVecDriver()->setRzRyMvAng(0,0);
    registerHitAreaCube_AutoGenMidColli(20000);
    setHitAble(true, false); //画面外当たり判定は無し
    setScaleR(5.0);
    setCullingDraw(false);
}

void EnemyOzartiaLaserChip01::onActive() {
    StraightLaserChip::onActive();
    GgafDx::VecDriver* const pVecDriver = getVecDriver();
    pVecDriver->setMvVelo(100000);
    pVecDriver->setMvAcce(300);
    getStatus()->reset();
}

void EnemyOzartiaLaserChip01::processJudgement() {
    if (isOutOfSpacetime()) {
        sayonara();
    }
}

void EnemyOzartiaLaserChip01::onHit(const GgafCore::Actor* prm_pOtherActor) {
    bool was_destroyed = UTIL::performEnemyHit(this, (const GgafDx::GeometricActor*)prm_pOtherActor);
    if (was_destroyed) {
        //破壊された時(スタミナ <= 0)
        sayonara();
    } else {
        //破壊されなかった時(スタミナ > 0)
    }
}

EnemyOzartiaLaserChip01::~EnemyOzartiaLaserChip01() {
}

