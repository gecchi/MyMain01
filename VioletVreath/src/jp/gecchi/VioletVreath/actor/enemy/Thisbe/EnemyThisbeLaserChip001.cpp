#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;


EnemyThisbeLaserChip001::EnemyThisbeLaserChip001(const char* prm_name) :
        HomingLaserChip(prm_name, "ThisbeLaserChip001", STATUS(EnemyThisbeLaserChip001)) {
    _class_name = "EnemyThisbeLaserChip001";
    pSplManufCon_ = connectToSplineManufactureManager("Hilbert"); //ヒルベルト曲線
    pSplSeq_ = pSplManufCon_->fetch()->createSplineSequence(_pKurokoA);
}

void EnemyThisbeLaserChip001::initialize() {
//    registHitAreaCube_AutoGenMidColli(20000);
    setScaleR(5.0);
    setAlpha(0.9);
}
void EnemyThisbeLaserChip001::onActive() {
    HomingLaserChip::onActive();
    //ステータスリセット
    _pStatus->reset();
    _pKurokoA->setMvVelo(30000);
    _pKurokoA->relateFaceAngWithMvAng(true);
    //位置と向きはEnemyThisbeが設定
    pSplSeq_->stop();
}

void EnemyThisbeLaserChip001::executeHitChk_MeAnd(GgafActor* prm_pOtherActor) {
    if (((GgafMainActor*)prm_pOtherActor)->getKind() & KIND_CHIKEI) {
        if (_chip_kind != 2 || _can_chikei_hit) {
            GgafDxDrawableActor::executeHitChk_MeAnd(prm_pOtherActor);
        } else {
            return;
        }
    } else {
        GgafDxDrawableActor::executeHitChk_MeAnd(prm_pOtherActor);
    }
}

void EnemyThisbeLaserChip001::processBehaviorHeadChip() {
    if (getActivePartFrame() == 2) {
        pSplSeq_->exec(SplineSequence::RELATIVE_DIRECTION); //向いた方向にワールド変換
    }
    pSplSeq_->behave();
    _pKurokoA->behave();
}

void EnemyThisbeLaserChip001::onHit(GgafActor* prm_pOtherActor) {
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

EnemyThisbeLaserChip001::~EnemyThisbeLaserChip001() {
    GGAF_DELETE(pSplSeq_);
    pSplManufCon_->close();
}

