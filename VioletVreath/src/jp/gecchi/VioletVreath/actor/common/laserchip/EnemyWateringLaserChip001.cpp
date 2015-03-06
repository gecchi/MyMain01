#include "EnemyWateringLaserChip001.h"
#include "jp/ggaf/lib/actor/laserchip/WateringLaserChip.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"


using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;



EnemyWateringLaserChip001::EnemyWateringLaserChip001(const char* prm_name) :
        WateringLaserChip(prm_name, "EnemyWateringLaserChip001", STATUS(EnemyWateringLaserChip001)) {
    _class_name = "EnemyWateringLaserChip001";
}

void EnemyWateringLaserChip001::initialize() {
    getKuroko()->relateFaceByMvAng(true);
    registerHitAreaCube_AutoGenMidColli(50000);
    setHitAble(true);
    setScaleR(6.0);
    setAlpha(0.99);
}

void EnemyWateringLaserChip001::onCreateModel() {

}

void EnemyWateringLaserChip001::onActive() {
    WateringLaserChip::onActive();
    getKuroko()->setMvVelo(PX_C(80));
    getKuroko()->setMvAcce(300);
    getStatus()->reset();
}

void EnemyWateringLaserChip001::processBehavior() {
    GgafDxKuroko* pKuroko = getKuroko();
    pKuroko->behave();
    WateringLaserChip::processBehavior();//座標を移動させてから呼び出すこと
}


void EnemyWateringLaserChip001::onHit(GgafActor* prm_pOtherActor) {
    GgafDxGeometricActor* pOther = (GgafDxGeometricActor*)prm_pOtherActor;
    if (getActiveFrame() <= 2 && (pOther->getKind() & KIND_CHIKEI)) {
        //出現2フレーム以内でヒット相手が地形ならば無視（出現即地形による破壊されを回避）
        return;
    }

    bool was_destroyed = UTIL::transactEnemyHit(this, pOther);
    if (was_destroyed) {
        //破壊された時(スタミナ <= 0)
        sayonara();
    } else {
        //破壊されなかった時(スタミナ > 0)
    }
}

void EnemyWateringLaserChip001::onInactive() {
    WateringLaserChip::onInactive();
}


EnemyWateringLaserChip001::~EnemyWateringLaserChip001() {
}

