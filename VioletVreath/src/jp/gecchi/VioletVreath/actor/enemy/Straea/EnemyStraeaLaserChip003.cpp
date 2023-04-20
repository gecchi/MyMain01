#include "EnemyStraeaLaserChip003.h"

#include "jp/ggaf/dx/actor/supporter/SeTransmitterForActor.h"
#include "jp/ggaf/dx/actor/supporter/LocoVehicle.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/gecchi/VioletVreath/Caretaker.h"
#include "jp/ggaf/dx/util/curve/VehicleLeader.h"

using namespace GgafDx;
using namespace GgafLib;
using namespace VioletVreath;

EnemyStraeaLaserChip003::EnemyStraeaLaserChip003(const char* prm_name) :
        VvEnemyActor<WateringLaserChip>(prm_name, "StraeaLaserChip001", StatusReset(EnemyStraeaLaserChip003)) {
    _class_name = "EnemyStraeaLaserChip003";
    pConn_pCurveManuf_ = connectToCurveManufactureManager("GURUGURU");
    pVehicleLeader_ = createCurveVehicleLeader(pConn_pCurveManuf_->peek());
}

void EnemyStraeaLaserChip003::initialize() {
    registerHitAreaCube_AutoGenMidColli(20000);
    setHitAble(true, false);
    setScaleR(5.0);
    setCullingDraw(false);
    GgafDx::LocoVehicle* pLocoVehicle = getLocoVehicle();
    pLocoVehicle->setMvVelo(30000);
    pLocoVehicle->linkFaceAngByMvAng(true);
}

void EnemyStraeaLaserChip003::onActive() {
    WateringLaserChip::onActive();
    //ステータスリセット
    getStatus()->reset();
    pVehicleLeader_->start(RELATIVE_COORD_DIRECTION); //向いた方向にワールド変換
}

void EnemyStraeaLaserChip003::processBehavior() {
    pVehicleLeader_->behave();
    getLocoVehicle()->behave();
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
    GGAF_DELETE(pVehicleLeader_);
    pConn_pCurveManuf_->close();
}

