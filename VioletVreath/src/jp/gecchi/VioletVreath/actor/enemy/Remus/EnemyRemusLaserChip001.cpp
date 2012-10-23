#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;


EnemyRemusLaserChip001::EnemyRemusLaserChip001(const char* prm_name) :
        WateringLaserChip(prm_name, "RemusLaserChip001", STATUS(EnemyRemusLaserChip001)) {
    _class_name = "EnemyRemusLaserChip001";
}

void EnemyRemusLaserChip001::initialize() {
    registHitAreaCube(20000);
    setHitAble(true, false);
    setScaleR(5.0);
    setAlpha(0.9);
    _pKurokoA->setMvVelo(300000);
    _pKurokoA->relateFaceAngWithMvAng(true);
}

void EnemyRemusLaserChip001::onActive() {
    WateringLaserChip::onActive();
    //ステータスリセット
    _pStatus->reset();
}

void EnemyRemusLaserChip001::processBehavior() {
    _pKurokoA->behave();
    WateringLaserChip::processBehavior();
}

void EnemyRemusLaserChip001::onHit(GgafActor* prm_pOtherActor) {
    GgafDxGeometricActor* pOther = (GgafDxGeometricActor*)prm_pOtherActor;
    if (getActivePartFrame() < 30 && (pOther->getKind() & KIND_CHIKEI)) {
        //出現30フレーム以内でヒット相手が地形ならば無視（出現即地形による破壊されを回避）
        return;
    }
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
void EnemyRemusLaserChip001::onInactive() {
    WateringLaserChip::onInactive();
}

EnemyRemusLaserChip001::~EnemyRemusLaserChip001() {
}

