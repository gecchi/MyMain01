#include "EnemyStraeaLaserChip003.h"

#include "jp/ggaf/dx/actor/supporter/SeTransmitterForActor.h"
#include "jp/ggaf/dx/actor/supporter/LocusVehicle.h"
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
    GgafDx::LocusVehicle* pLocusVehicle = getLocusVehicle();
    pLocusVehicle->setMvVelo(30000);
    pLocusVehicle->linkFaceAngByMvAng(true);
}

void EnemyStraeaLaserChip003::onActive() {
    WateringLaserChip::onActive();
    //ステータスリセット
    getStatus()->reset();
    pVehicleLeader_->start(RELATIVE_COORD_DIRECTION); //向いた方向にワールド変換
}

void EnemyStraeaLaserChip003::processBehavior() {
    pVehicleLeader_->behave();
    getLocusVehicle()->behave();
}

void EnemyStraeaLaserChip003::processJudgement() {
    if (isOutOfSpacetime()) {
        sayonara();
    }
}

void EnemyStraeaLaserChip003::onInactive() {
    WateringLaserChip::onInactive();
}

EnemyStraeaLaserChip003::~EnemyStraeaLaserChip003() {
    GGAF_DELETE(pVehicleLeader_);
    pConn_pCurveManuf_->close();
}

