#include "EnemyHisbeLaserChip003.h"

#include "jp/ggaf/core/actor/SceneMediator.h"
#include "jp/ggaf/dx/actor/supporter/SeTransmitterForActor.h"
#include "jp/ggaf/dx/actor/supporter/VecDriver.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/ggaf/dx/util/curve/DriverLeader.h"
#include "jp/ggaf/dx/manager/CurveManufactureConnection.h"
#include "jp/ggaf/lib/scene/DefaultScene.h"

using namespace GgafDx;
using namespace GgafLib;
using namespace VioletVreath;

EnemyHisbeLaserChip003::EnemyHisbeLaserChip003(const char* prm_name) :
        VvEnemyActor<WateringLaserChip>(prm_name, "HisbeLaserChip003", StatusReset(EnemyHisbeLaserChip003)) {
    _class_name = "EnemyHisbeLaserChip003";
    pConn_pCurveManuf_ = connectToCurveManufactureManager("EnemyHisbeLaserChip003"); //ゴスパー曲線
    pDriverLeader_ = createCurveDriverLeader(pConn_pCurveManuf_->peek());
    pDriverLeader_->adjustCoordOffset(PX_C(100), 0, 0);
    pFeatureScene_ = nullptr;
    sp_index_ = 0;
}

void EnemyHisbeLaserChip003::initialize() {
    registerHitAreaCube_AutoGenMidColli(20000);
    setHitAble(true, false);
    setScaleR(5.0);
    setCullingDraw(false);

    getVecDriver()->linkFaceAngByMvAng(true);
    sp_index_ = 0;
}

void EnemyHisbeLaserChip003::onActive() {
    WateringLaserChip::onActive();
    //ステータスリセット
    getStatus()->reset();
    pDriverLeader_->start(RELATIVE_COORD_DIRECTION); //向てる方向にスプライン座標をワールド変換
    sp_index_ = 0;
    setDriverLeader(pDriverLeader_);
}

void EnemyHisbeLaserChip003::processBehavior() {
    GgafDx::VecDriver* const pVecDriver = getVecDriver();

    if (pFeatureScene_) {
        pDriverLeader_->_x_start_in_loop -= pFeatureScene_->getFeatureParam1();
    }
    if (sp_index_ > (pDriverLeader_->_pManufacture->_pCurve->_rnum -1)) {

    } else {
        pVecDriver->setMvVelo(pDriverLeader_->getSegmentDistance(sp_index_));
        sp_index_++;
    }
    //pDriverLeader_->behave(); 内部で pVecDriver->_velo_mv を参照し次フレーム数決定してるので、
    //１フレームで次の点に到達するべく、pDriverLeader_->behave(); の前に pVecDriver->setMvVelo() で設定しなければいけない。
    pDriverLeader_->behave();
    pVecDriver->behave();
    WateringLaserChip::processBehavior();
}
void EnemyHisbeLaserChip003::processSettlementBehavior() {
    //角を丸めたくないのでオーバーライド
//    if (_was_paused_flg) {
//        GgafDx::GeometricActor::processSettlementBehavior();
//    } else {
        LaserChip::processSettlementBehavior();
//    }
}
void EnemyHisbeLaserChip003::processJudgement() {
    if (pDriverLeader_->isFinished()) {
        sayonara();
    }

    if (isOutOfSpacetime()) {
        sayonara();
    }
}

void EnemyHisbeLaserChip003::onHit(const GgafCore::Actor* prm_pOtherActor) {
    bool was_destroyed = UTIL::performEnemyHit(this, (const GgafDx::GeometricActor*)prm_pOtherActor);
    if (was_destroyed) {
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
    GGAF_DELETE(pDriverLeader_);
    pConn_pCurveManuf_->close();
}

