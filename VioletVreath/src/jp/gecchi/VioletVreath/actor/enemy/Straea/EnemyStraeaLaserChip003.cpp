#include "EnemyStraeaLaserChip003.h"

#include "jp/ggaf/dx/actor/supporter/SeTransmitterForActor.h"
#include "jp/ggaf/dx/actor/supporter/VecDriver.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/ggaf/dx/util/spline/SplineLeader.h"

using namespace GgafDx;
using namespace GgafLib;
using namespace VioletVreath;

EnemyStraeaLaserChip003::EnemyStraeaLaserChip003(const char* prm_name) :
        VvEnemyActor<WateringLaserChip>(prm_name, "StraeaLaserChip001", StatusReset(EnemyStraeaLaserChip003)) {
    _class_name = "EnemyStraeaLaserChip003";
    pConn_pSplManuf_ = connectToSplineManufactureManager("GURUGURU");
    pVecDriverLeader_ = pConn_pSplManuf_->peek()->createVecDriverLeader(callVecDriver());
}

void EnemyStraeaLaserChip003::initialize() {
    registerHitAreaCube_AutoGenMidColli(20000);
    setHitAble(true, false);
    setScaleR(5.0);
    setCullingDraw(false);
    GgafDx::VecDriver* const pVecDriver = callVecDriver();
    pVecDriver->setMvVelo(30000);
    pVecDriver->linkFaceAngByMvAng(true);
}

void EnemyStraeaLaserChip003::onActive() {
    WateringLaserChip::onActive();
    //ステータスリセット
    getStatus()->reset();
    pVecDriverLeader_->start(RELATIVE_COORD_DIRECTION); //向いた方向にワールド変換
}

void EnemyStraeaLaserChip003::processBehavior() {
    pVecDriverLeader_->behave();
    callVecDriver()->behave();
}

void EnemyStraeaLaserChip003::processJudgement() {
    if (isOutOfSpacetime()) {
        sayonara();
    }
}

void EnemyStraeaLaserChip003::onHit(const GgafCore::Actor* prm_pOtherActor) {
    bool was_destroyed = UTIL::performEnemyHit(this, (const GgafDx::GeometricActor*)prm_pOtherActor);
    if (was_destroyed) {
        //破壊された時(スタミナ <= 0)
        sayonara();
    } else {
        //破壊されなかった時(スタミナ > 0)
    }
}
void EnemyStraeaLaserChip003::onInactive() {
    WateringLaserChip::onInactive();
}

EnemyStraeaLaserChip003::~EnemyStraeaLaserChip003() {
    GGAF_DELETE(pVecDriverLeader_);
    pConn_pSplManuf_->close();
}

