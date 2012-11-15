#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;


EnemyThisbeLaserChip003::EnemyThisbeLaserChip003(const char* prm_name) :
        WateringLaserChip(prm_name, "ThisbeLaserChip003", STATUS(EnemyThisbeLaserChip003)) {
    _class_name = "EnemyThisbeLaserChip003";
    pSplManufCon_ = connectToSplineManufactureManager("EnemyThisbeLaserChip003"); //ヒルベルト曲線
    pSplSeq_ = pSplManufCon_->fetch()->createSplineSequence(_pKurokoA);
    pSplSeq_->adjustCoordOffset(PX_C(100), 0, 0);
    setMiddleColliAble(true); //チップ間当たり判定自動発生
}

void EnemyThisbeLaserChip003::initialize() {
    registHitAreaCube(20000);
    setHitAble(true, false);
    setScaleR(5.0);
    setAlpha(0.9);

    _pKurokoA->relateFaceAngWithMvAng(true);
    sp_index_ = 0;
}

void EnemyThisbeLaserChip003::onActive() {
    WateringLaserChip::onActive();
    //ステータスリセット
    _pStatus->reset();
    pSplSeq_->exec(SplineSequence::RELATIVE_DIRECTION); //向てる方向にスプライン座標をワールド変換
    sp_index_ = 0;
}

void EnemyThisbeLaserChip003::processBehavior() {
    if (pSplSeq_->isExecuting()) {
        _pKurokoA->setMvVelo(pSplSeq_->getSegmentDistance(sp_index_));
        sp_index_++;
    } else {
        sayonara();
    }
    //pSplSeq_->behave(); 内部で pKurokoA->_veloMv を参照し次フレーム数決定してるので、
    //１フレームで次の点に到達するべく、pSplSeq_->behave(); の前に pKurokoA->setMvVelo() で設定しなければいけない。
    pSplSeq_->behave();
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
    DELETE_IMPOSSIBLE_NULL(pSplSeq_);
    pSplManufCon_->close();
}

