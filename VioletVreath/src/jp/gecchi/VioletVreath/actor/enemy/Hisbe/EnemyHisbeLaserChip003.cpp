#include "EnemyHisbeLaserChip003.h"

#include "jp/ggaf/core/actor/SceneMediator.h"
#include "jp/ggaf/dx/actor/supporter/SeTransmitterForActor.h"
#include "jp/ggaf/dx/actor/supporter/Kuroko.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/ggaf/lib/util/spline/SplineLeader.h"
#include "jp/ggaf/lib/manager/SplineManufactureConnection.h"
#include "jp/ggaf/lib/scene/DefaultScene.h"


using namespace GgafLib;
using namespace VioletVreath;

EnemyHisbeLaserChip003::EnemyHisbeLaserChip003(const char* prm_name) :
        WateringLaserChip(prm_name, "HisbeLaserChip003") {
    _class_name = "EnemyHisbeLaserChip003";
    getStatus()->reset(statusResetFunction(EnemyHisbeLaserChip003));
    pConn_pSplManuf_ = connectToSplineManufactureManager("EnemyHisbeLaserChip003"); //ゴスパー曲線
    pKurokoLeader_ = pConn_pSplManuf_->peek()->createKurokoLeader(getKuroko());
    pKurokoLeader_->adjustCoordOffset(PX_C(100), 0, 0);
    pScrollingScene_ = nullptr;
    sp_index_ = 0;
}

void EnemyHisbeLaserChip003::initialize() {
    registerHitAreaCube_AutoGenMidColli(20000);
    setHitAble(true, false);
    setScaleR(5.0);
    setCullingDraw(false);

    getKuroko()->linkFaceAngByMvAng(true);
    sp_index_ = 0;
}

void EnemyHisbeLaserChip003::onActive() {
    WateringLaserChip::onActive();
    //ステータスリセット
    getStatus()->reset();
    pKurokoLeader_->start(RELATIVE_COORD_DIRECTION); //向てる方向にスプライン座標をワールド変換
    sp_index_ = 0;
    pScrollingScene_ = ((DefaultScene*)(getSceneMediator()->getPlatformScene()))->getNearestScrollingScene();
}

void EnemyHisbeLaserChip003::processBehavior() {
    GgafDx::Kuroko* const pKuroko = getKuroko();

    if (pScrollingScene_) {
        pKurokoLeader_->_x_start_in_loop -= pScrollingScene_->getScrollSpeed();
    }
    if (sp_index_ > (pKurokoLeader_->_pManufacture->_pSpl->_rnum -1)) {

    } else {
        pKuroko->setMvVelo(pKurokoLeader_->getSegmentDistance(sp_index_));
        sp_index_++;
    }
    //pKurokoLeader_->behave(); 内部で pKuroko->_velo_mv を参照し次フレーム数決定してるので、
    //１フレームで次の点に到達するべく、pKurokoLeader_->behave(); の前に pKuroko->setMvVelo() で設定しなければいけない。
    pKurokoLeader_->behave();
    pKuroko->behave();
    WateringLaserChip::processBehavior();
}
void EnemyHisbeLaserChip003::processSettlementBehavior() {
    //角を丸めたくないのでオーバーライド
    if (_was_paused_flg) {
        GgafDx::GeometricActor::processSettlementBehavior();
    } else {
        LaserChip::processSettlementBehavior();
    }
}
void EnemyHisbeLaserChip003::processJudgement() {
    if (pKurokoLeader_->isFinished()) {
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
    GGAF_DELETE(pKurokoLeader_);
    pConn_pSplManuf_->close();
}

