#include "stdafx.h"
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
    _pKuroko->relateFaceWithMvAng(true);
    registerHitAreaCube_AutoGenMidColli(50000);
    setHitAble(true);
    setScaleR(6.0);
    setAlpha(0.99);
}

void EnemyWateringLaserChip001::onCreateModel() {

}

void EnemyWateringLaserChip001::onActive() {
    WateringLaserChip::onActive();
    _pKuroko->setMvVelo(PX_C(80));
    _pKuroko->setMvAcce(300);
    _pStatus->reset();
}

void EnemyWateringLaserChip001::processBehavior() {
    if (getActiveFrame() == 1) {
        //初期設定の座標からいきなりズレるのを防止
        coord tmp_x = _x;
        coord tmp_y = _y;
        coord tmp_z = _z;
        _pKuroko->behave();
        position(tmp_x, tmp_y, tmp_z);
    } else {
        _pKuroko->behave();
    }
    WateringLaserChip::processBehavior();//座標を移動させてから呼び出すこと
}


void EnemyWateringLaserChip001::onHit(GgafActor* prm_pOtherActor) {
    GgafDxGeometricActor* pOther = (GgafDxGeometricActor*)prm_pOtherActor;
    if (UTIL::calcEnemyStamina(this, pOther) <= 0) {
        setHitAble(false); //以降同一フレーム内でヒットさせない。
        UTIL::activateExplosionEffectOf(this); //爆発エフェクト出現
        sayonara();
    }
}

void EnemyWateringLaserChip001::onInactive() {
    WateringLaserChip::onInactive();
}


EnemyWateringLaserChip001::~EnemyWateringLaserChip001() {
}

