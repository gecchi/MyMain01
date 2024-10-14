#include "EnemyHisbeLaserChip003.h"

#include "jp/ggaf/core/actor/SceneChief.h"
#include "jp/ggaf/dx/actor/supporter/SeTransmitterForActor.h"
#include "jp/ggaf/dx/actor/supporter/LocusVehicle.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/gecchi/VioletVreath/Caretaker.h"
#include "jp/ggaf/dx/util/curve/VehicleLeader.h"
#include "jp/ggaf/dx/manager/CurveManufactureConnection.h"
#include "jp/ggaf/lib/scene/DefaultScene.h"

using namespace GgafDx;
using namespace GgafLib;
using namespace VioletVreath;

EnemyHisbeLaserChip003::EnemyHisbeLaserChip003(const char* prm_name) :
        VvEnemyActor<WateringLaserChip>(prm_name, "HisbeLaserChip003", StatusReset(EnemyHisbeLaserChip003)) {
    _class_name = "EnemyHisbeLaserChip003";
    pConn_pCurveManuf_ = connectToCurveManufactureManager("EnemyHisbeLaserChip003"); //ゴスパー曲線
    pVehicleLeader_ = createCurveVehicleLeader(pConn_pCurveManuf_->peek());
    pVehicleLeader_->adjustCoordOffset(PX_C(100), 0, 0);
    pFeatureScene_ = nullptr;
    sp_index_ = 0;
}

void EnemyHisbeLaserChip003::initialize() {
    registerHitAreaCube_AutoGenMidColli(20000);
    setHitAble(true, false);
    setScaleR(5.0);
    setCullingDraw(false);

    getLocusVehicle()->linkFaceAngByMvAng(true);
    sp_index_ = 0;
}

void EnemyHisbeLaserChip003::onActive() {
    WateringLaserChip::onActive();
    //ステータスリセット
    getStatus()->reset();
    pVehicleLeader_->start(RELATIVE_COORD_DIRECTION); //向てる方向にスプライン座標をワールド変換
    sp_index_ = 0;
    setVehicleLeader(pVehicleLeader_);
}

void EnemyHisbeLaserChip003::processBehavior() {
    GgafDx::LocusVehicle* pLocusVehicle = getLocusVehicle();

    if (pFeatureScene_) {
        pVehicleLeader_->_x_start_in_loop -= pFeatureScene_->getFeatureParam1();
    }
    if (sp_index_ > (pVehicleLeader_->_pManufacture->_pCurve->_rnum -1)) {

    } else {
        pLocusVehicle->setMvVelo(pVehicleLeader_->getSegmentDistance(sp_index_));
        sp_index_++;
    }
    //pVehicleLeader_->behave(); 内部で pLocusVehicle->_velo_mv を参照し次フレーム数決定してるので、
    //１フレームで次の点に到達するべく、pVehicleLeader_->behave(); の前に pLocusVehicle->setMvVelo() で設定しなければいけない。
    pVehicleLeader_->behave();
    pLocusVehicle->behave();
    WateringLaserChip::processBehavior();
}
void EnemyHisbeLaserChip003::processSettlementBehavior() {
    //ここだめ_was_paused_flg
//    if (getSceneChief()->getPlatformScene()->_was_paused_flg) {
//        GgafDx::GeometricActor::processSettlementBehavior();
//    } else {
//        LaserChip::processSettlementBehavior();
//    }
    //角を丸めたくないのでオーバーライド
    LaserChip::processSettlementBehavior();
}

void EnemyHisbeLaserChip003::processJudgement() {
    if (pVehicleLeader_->isFinished()) {
        sayonara();
    }

    if (isOutOfSpacetime()) {
        sayonara();
    }
}

void EnemyHisbeLaserChip003::onHit(const GgafCore::Checker* prm_pOtherChecker, const GgafCore::Actor* prm_pOtherActor) {
    bool is_stamina_zero = performEnemyHit((const GgafDx::GeometricActor*)prm_pOtherActor);
    if (is_stamina_zero) {
        //破壊された時(スタミナ <= 0)
        sayonara();
    } else {
        //破壊されなかった時(スタミナ > 0)
    }
}

void EnemyHisbeLaserChip003::onInactive() {
    WateringLaserChip::onInactive();
}

EnemyHisbeLaserChip003::~EnemyHisbeLaserChip003() {
    GGAF_DELETE(pVehicleLeader_);
    pConn_pCurveManuf_->close();
}

