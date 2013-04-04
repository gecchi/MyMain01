#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;


EnemyThisbeLaserChip003::EnemyThisbeLaserChip003(const char* prm_name) :
        WateringLaserChip(prm_name, "ThisbeLaserChip003", STATUS(EnemyThisbeLaserChip003)) {
    _class_name = "EnemyThisbeLaserChip003";
    pSplManufConnection_ = connectToSplineManufactureManager("EnemyThisbeLaserChip003"); //ゴスパー曲線
    pKurokoStepper_ = pSplManufConnection_->peek()->createSplineKurokoStepper(_pKurokoA);
    pKurokoStepper_->adjustCoordOffset(PX_C(100), 0, 0);
    sp_index_ = 0;
    pNearestScrollingScene_ = nullptr;
}

void EnemyThisbeLaserChip003::initialize() {
    registHitAreaCube_AutoGenMidColli(20000);
    setHitAble(true, false);
    setScaleR(5.0);
    setAlpha(0.9);

    _pKurokoA->relateMvFaceAng(true);
    sp_index_ = 0;
    pNearestScrollingScene_ = ((DefaultScene*)getPlatformScene())->getNearestScrollingScene();
}

void EnemyThisbeLaserChip003::onActive() {
    WateringLaserChip::onActive();
    //ステータスリセット
    _pStatus->reset();
    pKurokoStepper_->start(SplineKurokoStepper::RELATIVE_DIRECTION); //向てる方向にスプライン座標をワールド変換
    sp_index_ = 0;
}

void EnemyThisbeLaserChip003::processBehavior() {
    if (pNearestScrollingScene_->_pFuncScrolling == WalledScene::scrollX) {
        pKurokoStepper_->_X_begin -= pNearestScrollingScene_->getScrollSpeed();
    }

    if (pKurokoStepper_->isStepping()) {
        _pKurokoA->setMvVelo(pKurokoStepper_->getSegmentDistance(sp_index_));
        sp_index_++;
    } else {
        sayonara();
    }
    //pKurokoStepper_->behave(); 内部で pKurokoA->_veloMv を参照し次フレーム数決定してるので、
    //１フレームで次の点に到達するべく、pKurokoStepper_->behave(); の前に pKurokoA->setMvVelo() で設定しなければいけない。
    pKurokoStepper_->behave();
    _pKurokoA->behave();
    WateringLaserChip::processBehavior();
}
void EnemyThisbeLaserChip003::processSettlementBehavior() {
    //角を丸めたくないのでオーバーライド
    if (_was_paused_flg) {
        GgafDxGeometricActor::processSettlementBehavior();
    } else {
        LaserChip::processSettlementBehavior();
    }
}

void EnemyThisbeLaserChip003::onHit(GgafActor* prm_pOtherActor) {
    GgafDxGeometricActor* pOther = (GgafDxGeometricActor*)prm_pOtherActor;
    //ヒット時
    //体力計算
    int sta = UTIL::calcEnemyStamina(this, pOther);
    if (sta <= 0) {
        //ヒットして消滅時
        sayonara();
    } else {
        //ヒットして生存時
    }
}
void EnemyThisbeLaserChip003::onInactive() {
    WateringLaserChip::onInactive();
}

EnemyThisbeLaserChip003::~EnemyThisbeLaserChip003() {
    GGAF_DELETE(pKurokoStepper_);
    pSplManufConnection_->close();
}

