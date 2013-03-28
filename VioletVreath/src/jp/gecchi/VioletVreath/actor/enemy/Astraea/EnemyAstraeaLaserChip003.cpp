#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;


EnemyAstraeaLaserChip003::EnemyAstraeaLaserChip003(const char* prm_name) :
        WateringLaserChip(prm_name, "AstraeaLaserChip001", STATUS(EnemyAstraeaLaserChip003)) {
    _class_name = "EnemyAstraeaLaserChip003";
    pSplManufConnection_ = connectToSplineManufactureManager("GURUGURU");
    pSplSeq_ = pSplManufConnection_->peek()->createSplineSequence(_pKurokoA);
}

void EnemyAstraeaLaserChip003::initialize() {
    registHitAreaCube_AutoGenMidColli(20000);
    setHitAble(true, false);
    setScaleR(5.0);
    setAlpha(0.9);
    _pKurokoA->setMvVelo(30000);
    _pKurokoA->relateMvFaceAng(true);
}

void EnemyAstraeaLaserChip003::onActive() {
    WateringLaserChip::onActive();
    //ステータスリセット
    _pStatus->reset();
    pSplSeq_->exec(SplineSequence::RELATIVE_DIRECTION); //向いた方向にワールド変換
}

void EnemyAstraeaLaserChip003::processBehavior() {
    pSplSeq_->behave();
    _pKurokoA->behave();
    WateringLaserChip::processBehavior();
}

void EnemyAstraeaLaserChip003::onHit(GgafActor* prm_pOtherActor) {
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
void EnemyAstraeaLaserChip003::onInactive() {
    WateringLaserChip::onInactive();
}

EnemyAstraeaLaserChip003::~EnemyAstraeaLaserChip003() {
    GGAF_DELETE(pSplSeq_);
    pSplManufConnection_->close();
}

