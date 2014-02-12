#include "stdafx.h"
#include "EnemyErmioneArmHead.h"
#include "EnemyErmione.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxSeTransmitterForActor.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxScaler.h"
#include "jp/ggaf/lib/util/CollisionChecker3D.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxAxesMover.h"
#include "jp/ggaf/lib/actor/laserchip/LaserChipDepository.h"
#include "jp/ggaf/lib/actor/laserchip/StraightLaserChip.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

EnemyErmioneArmHead::EnemyErmioneArmHead(const char* prm_name) :
        EnemyErmioneArm(prm_name, "ErmioneArmHead", STATUS(EnemyErmioneArmHead)) {
    _class_name = "EnemyErmioneArmHead";
    pDepoLaser_  = nullptr;
}

void EnemyErmioneArmHead::onCreateModel() {
}

void EnemyErmioneArmHead::initialize() {
    EnemyErmioneArm::initialize();
    _pColliChecker->makeCollision(1);
    _pColliChecker->setColliAAB_Cube(0, 40000);
}

void EnemyErmioneArmHead::processBehavior() {
    bool shot = false;
    if (_pProg->get() == PROG_NOTHING || _pProg->get() == PROG_AIMING) { //出現間隔
        shot = true;
        if (pDepoLaser_) {

        } else {
            pDepoLaser_ = (LaserChipDepository*)UTIL::getDepositoryOf(this);
        }
    }

    EnemyErmioneArm::processBehavior();

    if (shot) { //出現間隔
        LaserChip* pChip = nullptr;
        if (pDepoLaser_) {
            pChip = pDepoLaser_->dispatch();
        }

        if (pChip) {
            //DEPO_LASER001の場合
            pChip->setFaceAng(_rx, _ry, _rz);
            pChip->_pKuroko->setRzRyMvAng(_rz, _ry); //RzRyでMoverに設定
            pChip->positionAs(this);

            //DEPO_LASER002の場合
            //((StraightLaserChip*)pChip)->setSource(this);
        }
    }

}


void EnemyErmioneArmHead::onHit(GgafActor* prm_pOtherActor) {
    GgafDxGeometricActor* pOther = (GgafDxGeometricActor*)prm_pOtherActor;
//    if (UTIL::calcEnemyStamina(this, pOther) <= 0) {
//        setHitAble(false);
//        //爆発効果
//        UTIL::activateExplosionEffectOf(this);
//        _pSeTx->play3D(SE_EXPLOSION);
//
//        //自機側に撃たれて消滅の場合、
//        if (pOther->getKind() & KIND_MY) {
//            //アイテム出現
//            UTIL::activateItemOf(this);
//        }
//        sayonara();
//    } else {
//        //非破壊時
//        effectFlush(2); //フラッシュ
//        _pSeTx->play3D(SE_DAMAGED);
//    }
}


EnemyErmioneArmHead::~EnemyErmioneArmHead() {
//    pDepoConnection_->close();
}
