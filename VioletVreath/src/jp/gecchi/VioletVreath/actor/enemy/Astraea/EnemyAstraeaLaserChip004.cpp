#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;


EnemyAstraeaLaserChip004::EnemyAstraeaLaserChip004(const char* prm_name) :
        HomingLaserChip(prm_name, "AstraeaLaserChip001", STATUS(EnemyAstraeaLaserChip004)) {
    _class_name = "EnemyAstraeaLaserChip004";
    pSplManufCon_ = connectToSplineManufactureManager("GURUGURU");
    pSplSeq_ = pSplManufCon_->fetch()->createSplineSequence(_pKurokoA);
}

void EnemyAstraeaLaserChip004::initialize() {
    registHitAreaCube(20000);
    setHitAble(true, false);
    setScaleR(5.0);
    setAlpha(0.9);
}
void EnemyAstraeaLaserChip004::onActive() {
    HomingLaserChip::onActive();
    //ステータスリセット
    _pStatus->reset();

    _pKurokoA->setMvVelo(10000);
    _pKurokoA->setMvAcce(400);
    _pKurokoA->relateFaceAngWithMvAng(true);
    pSplSeq_->stop();
}

void EnemyAstraeaLaserChip004::executeHitChk_MeAnd(GgafActor* prm_pOtherActor) {
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

void EnemyAstraeaLaserChip004::processBehaviorHeadChip() {
    if (getActivePartFrame() == 2) {
        pSplSeq_->exec(SplineSequence::RELATIVE_DIRECTION); //向いた方向にワールド変換
    }
    pSplSeq_->behave(); //←途中でちょんぎれたらだめじゃん
    _pKurokoA->behave();
}

void EnemyAstraeaLaserChip004::onHit(GgafActor* prm_pOtherActor) {
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

EnemyAstraeaLaserChip004::~EnemyAstraeaLaserChip004() {
    DELETE_IMPOSSIBLE_NULL(pSplSeq_);
    pSplManufCon_->close();
}

