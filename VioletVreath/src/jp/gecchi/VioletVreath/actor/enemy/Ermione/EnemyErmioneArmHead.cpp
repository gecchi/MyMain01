#include "EnemyErmioneArmHead.h"
#include "EnemyErmione.h"

#include "jp/ggaf/dx/actor/supporter/SeTransmitterForActor.h"
#include "jp/ggaf/dx/actor/supporter/LocusVehicle.h"
#include "jp/ggaf/dx/actor/supporter/Scaler.h"
#include "jp/ggaf/lib/util/WorldCollisionChecker.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/ggaf/dx/actor/supporter/CoordVehicle.h"
#include "jp/ggaf/lib/actor/laserchip/LaserChipDepository.h"
#include "jp/ggaf/lib/actor/laserchip/StraightLaserChip.h"



using namespace GgafLib;
using namespace VioletVreath;

EnemyErmioneArmHead::EnemyErmioneArmHead(const char* prm_name) :
        EnemyErmioneArm(prm_name, "ErmioneArmHead", StatusReset(EnemyErmioneArmHead)) {
    _class_name = "EnemyErmioneArmHead";
    pDepo_laser_chip_  = nullptr;
}

void EnemyErmioneArmHead::onCreateModel() {
}

void EnemyErmioneArmHead::initialize() {
    EnemyErmioneArm::initialize();
    WorldCollisionChecker* pChecker = getWorldCollisionChecker();
    pChecker->addCollisionArea(1);
    pChecker->setColliAACube(0, 40000);
}

void EnemyErmioneArmHead::processBehavior() {
    GgafCore::Phase* pPhase = getPhase();
    if (pPhase->getCurrent() == PHASE_NOTHING || pPhase->getCurrent() == PHASE_AIMING) { //出現間隔
        if (!pDepo_laser_chip_) {
            pDepo_laser_chip_ = (LaserChipDepository*)UTIL::getDepositoryOf(this);
        }
    } else {
        pDepo_laser_chip_ = nullptr;
    }
    EnemyErmioneArm::processBehavior();
}

void  EnemyErmioneArmHead::processChangeGeoFinal() {
    LaserChip* pChip = nullptr;
    if (pDepo_laser_chip_) {
        pChip = pDepo_laser_chip_->dispatch();
        if (pChip) {
            //DEPO_LASER001の場合
            pChip->setRollPitchYawFaceAng(_rx, _rz, _ry);
            pChip->getLocusVehicle()->setRzRyMvAng(_rz, _ry); //絶対座標系
            pChip->setPositionAt(this);

            //DEPO_LASER002の場合
            //((StraightLaserChip*)pChip)->setSource(this);
        }
    }
}

void EnemyErmioneArmHead::onHit(const GgafCore::Checker* prm_pOtherChecker, const GgafCore::Actor* prm_pOtherActor) {



    GgafDx::GeometricActor* pOther = (GgafDx::GeometricActor*)prm_pOtherActor;
//    if (UTIL::calcEnemyStamina(this, pOther) <= 0) {
//        setHitAble(false);
//        //爆発効果
//        UTIL::activateExplosionEffectOf(this);
//        getSeXmtr()->play3D(SE_EXPLOSION);
//
//        //自機側に撃たれて消滅の場合、
//        if (pOther->_kind & KIND_MY) {
//            //アイテム出現
//            UTIL::activateItemOf(this);
//        }
//        sayonara();
//    } else {
//        //非破壊時
//        effectFlush(2); //フラッシュ
//        getSeXmtr()->play3D(SE_DAMAGED);
//    }
}


EnemyErmioneArmHead::~EnemyErmioneArmHead() {
//    pConn_depo_->close();
}
