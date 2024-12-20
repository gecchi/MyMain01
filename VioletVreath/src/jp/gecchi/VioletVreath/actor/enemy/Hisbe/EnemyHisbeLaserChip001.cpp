#include "EnemyHisbeLaserChip001.h"

#include "jp/ggaf/core/actor/SceneChief.h"
#include "jp/ggaf/dx/actor/supporter/LocusVehicle.h"
#include "jp/ggaf/dx/actor/supporter/SeTransmitterForActor.h"
#include "jp/ggaf/dx/scene/Spacetime.h"
#include "jp/ggaf/lib/scene/DefaultScene.h"
#include "jp/ggaf/dx/util/curve/VehicleLeader.h"
#include "jp/gecchi/VioletVreath/Caretaker.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"

using namespace GgafDx;
using namespace GgafLib;
using namespace VioletVreath;

EnemyHisbeLaserChip001::EnemyHisbeLaserChip001(const char* prm_name) :
        VvEnemyActor<HomingLaserChip>(prm_name, "HisbeLaserChip001", StatusReset(EnemyHisbeLaserChip001)) {
    _class_name = "EnemyHisbeLaserChip001";
    pConn_pCurveManuf_ = connectToCurveManufactureManager("EnemyHisbeLaserChip002"); //ヒルベルト曲線
    pVehicleLeader_ = createCurveVehicleLeader(pConn_pCurveManuf_->peek());
    pFeatureScene_ = nullptr;
    getLocusVehicle()->setMvAngByFaceAng();
    getLocusVehicle()->linkFaceAngByMvAng(true);
}

void EnemyHisbeLaserChip001::initialize() {
    registerHitAreaCube_AutoGenMidColli(20000);
    setHitAble(true, false);
    setScaleR(5.0);
    setCullingDraw(false);
}

void EnemyHisbeLaserChip001::onActive() {
    HomingLaserChip::onActive();
    //ステータスリセット
    getStatus()->reset();
    setVehicleLeader(pVehicleLeader_);
}

void EnemyHisbeLaserChip001::onInactive() {
    HomingLaserChip::onInactive();
    pVehicleLeader_->stop();
}

void EnemyHisbeLaserChip001::processBehaviorHeadChip() {
    if (getActiveFrame() == 1) {
        return;
    }

    if (getActiveFrame() == 2) {
        pVehicleLeader_->start(RELATIVE_COORD_DIRECTION); //向いた方向にワールド変換
    }
    pVehicleLeader_->behave();
    getLocusVehicle()->behave();
    if (pVehicleLeader_->isFinished()) {
        sayonara();
    }
}

void EnemyHisbeLaserChip001::processJudgement() {
    if (isOutOfSpacetime()) {
        sayonara();
    }
}

EnemyHisbeLaserChip001::~EnemyHisbeLaserChip001() {
    GGAF_DELETE(pVehicleLeader_);
    pConn_pCurveManuf_->close();
}

