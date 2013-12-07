#include "stdafx.h"
#include "EnemyHisbeLaserChip003.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxSeTransmitterForActor.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/ggaf/lib/util/spline/SplineKurokoLeader.h"
#include "jp/ggaf/lib/manager/SplineManufactureConnection.h"
#include "jp/ggaf/lib/scene/DefaultScene.h"
#include "jp/ggaf/lib/scene/WalledScene.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

EnemyHisbeLaserChip003::EnemyHisbeLaserChip003(const char* prm_name) :
        WateringLaserChip(prm_name, "HisbeLaserChip003", STATUS(EnemyHisbeLaserChip003)) {
    _class_name = "EnemyHisbeLaserChip003";
    pSplManufConnection_ = connect_SplineManufactureManager("EnemyHisbeLaserChip003"); //ゴスパー曲線
    pKurokoLeader_ = pSplManufConnection_->peek()->createKurokoLeader(_pKuroko);
    pKurokoLeader_->adjustCoordOffset(PX_C(100), 0, 0);
    sp_index_ = 0;
    pNearestScrollingScene_ = nullptr;
}

void EnemyHisbeLaserChip003::initialize() {
    registerHitAreaCube_AutoGenMidColli(20000);
    setHitAble(true, false);
    setScaleR(5.0);
    setAlpha(0.9);

    _pKuroko->relateFaceWithMvAng(true);
    sp_index_ = 0;
    pNearestScrollingScene_ = ((DefaultScene*)getPlatformScene())->getNearestScrollingScene();
}

void EnemyHisbeLaserChip003::onActive() {
    WateringLaserChip::onActive();
    //ステータスリセット
    _pStatus->reset();
    pKurokoLeader_->start(SplineKurokoLeader::RELATIVE_DIRECTION); //向てる方向にスプライン座標をワールド変換
    sp_index_ = 0;
}

void EnemyHisbeLaserChip003::processBehavior() {
    if (pNearestScrollingScene_ && pNearestScrollingScene_->_pFuncScrolling == WalledScene::scrollX) {
        pKurokoLeader_->_x_start -= pNearestScrollingScene_->getScrollSpeed();
    }
    if (sp_index_ > (pKurokoLeader_->_pManufacture->_sp->_rnum -1)) {

    } else {
        _pKuroko->setMvVelo(pKurokoLeader_->getSegmentDistance(sp_index_));
        sp_index_++;
    }
    //pKurokoLeader_->behave(); 内部で pKuroko->_veloMv を参照し次フレーム数決定してるので、
    //１フレームで次の点に到達するべく、pKurokoLeader_->behave(); の前に pKuroko->setMvVelo() で設定しなければいけない。
    pKurokoLeader_->behave();
    _pKuroko->behave();
    WateringLaserChip::processBehavior();
}
void EnemyHisbeLaserChip003::processSettlementBehavior() {
    //角を丸めたくないのでオーバーライド
    if (_was_paused_flg) {
        GgafDxGeometricActor::processSettlementBehavior();
    } else {
        LaserChip::processSettlementBehavior();
    }
}
void EnemyHisbeLaserChip003::processJudgement() {
    if (pKurokoLeader_->isFinished()) {
        sayonara();
    }
}

void EnemyHisbeLaserChip003::onHit(GgafActor* prm_pOtherActor) {
    GgafDxGeometricActor* pOther = (GgafDxGeometricActor*)prm_pOtherActor;
    if (UTIL::calcEnemyStamina(this, pOther) <= 0) {
        sayonara();
    }
}

void EnemyHisbeLaserChip003::onInactive() {
    WateringLaserChip::onInactive();
}

EnemyHisbeLaserChip003::~EnemyHisbeLaserChip003() {
    GGAF_DELETE(pKurokoLeader_);
    pSplManufConnection_->close();
}

