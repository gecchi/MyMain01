#include "EnemyHisbeLaserChip002.h"

#include "jp/ggaf/core/actor/SceneChief.h"
#include "jp/ggaf/dx/actor/supporter/LocusVehicle.h"
#include "jp/ggaf/dx/actor/supporter/SeTransmitterForActor.h"
#include "jp/ggaf/dx/scene/Spacetime.h"
#include "jp/ggaf/dx/manager/CurveManufactureConnection.h"
#include "jp/ggaf/lib/scene/DefaultScene.h"
#include "jp/ggaf/dx/util/curve/VehicleLeader.h"
#include "jp/gecchi/VioletVreath/Caretaker.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"

using namespace GgafDx;
using namespace GgafLib;
using namespace VioletVreath;

EnemyHisbeLaserChip002::EnemyHisbeLaserChip002(const char* prm_name) :
        VvEnemyActor<RefractionLaserChip>(prm_name, "HisbeLaserChip002", StatusReset(EnemyHisbeLaserChip002)) {
    _class_name = "EnemyHisbeLaserChip002";
    pConn_pCurveManuf_ = connectToCurveManufactureManager("EnemyHisbeLaserChip002"); //ヒルベルト曲線
    pVehicleLeader_ = createCurveVehicleLeader(pConn_pCurveManuf_->peek());
    pVehicleLeader_->adjustCoordOffset(PX_C(100), 0, 0);
    pFeatureScene_ = nullptr;
    getLocusVehicle()->setMvAngByFaceAng();
    getLocusVehicle()->linkFaceAngByMvAng(true);
}

void EnemyHisbeLaserChip002::initialize() {
    registerHitAreaCube_AutoGenMidColli(20000);
    setHitAble(true, false);
    setScaleR(5.0);
    setCullingDraw(false);
}

void EnemyHisbeLaserChip002::onActive() {
    RefractionLaserChip::onActive();
    //ステータスリセット
    getStatus()->reset();
    pFeatureScene_ = ((DefaultScene*)(getSceneChief()->getPlatformScene()))->getNearestFeatureScene();
}

void EnemyHisbeLaserChip002::onRefractionInto(int prm_num_refraction)  {

}

void EnemyHisbeLaserChip002::onRefractionOutOf(int prm_num_refraction)  {
    if (prm_num_refraction == 0) {
        pVehicleLeader_->start(RELATIVE_COORD_DIRECTION); //向てる方向にスプライン座標をワールド変換
    }
    pVehicleLeader_->behave();
    if (pVehicleLeader_->isFinished()) {
        sayonara();
    }
}

void EnemyHisbeLaserChip002::processBehavior() {
    if (_is_leader) {
        if (pFeatureScene_) {
            pVehicleLeader_->_x_start_in_loop -= pFeatureScene_->getFeatureParam1();
        }
    }
    RefractionLaserChip::processBehavior();
}

void EnemyHisbeLaserChip002::processJudgement() {
    if (getActiveFrame() >= getRefractionFinishFrames()) {
        sayonara();
    }
    if (isOutOfSpacetime()) {
        sayonara();
    }
}

EnemyHisbeLaserChip002::~EnemyHisbeLaserChip002() {
    GGAF_DELETE(pVehicleLeader_);
    pConn_pCurveManuf_->close();
}


