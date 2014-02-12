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
    if (_pProg->get() == PROG_NOTHING || _pProg->get() == PROG_AIMING) { //�o���Ԋu
        shot = true;
        if (pDepoLaser_) {

        } else {
            pDepoLaser_ = (LaserChipDepository*)UTIL::getDepositoryOf(this);
        }
    }

    EnemyErmioneArm::processBehavior();

    if (shot) { //�o���Ԋu
        LaserChip* pChip = nullptr;
        if (pDepoLaser_) {
            pChip = pDepoLaser_->dispatch();
        }

        if (pChip) {
            //DEPO_LASER001�̏ꍇ
            pChip->setFaceAng(_rx, _ry, _rz);
            pChip->_pKuroko->setRzRyMvAng(_rz, _ry); //RzRy��Mover�ɐݒ�
            pChip->positionAs(this);

            //DEPO_LASER002�̏ꍇ
            //((StraightLaserChip*)pChip)->setSource(this);
        }
    }

}


void EnemyErmioneArmHead::onHit(GgafActor* prm_pOtherActor) {
    GgafDxGeometricActor* pOther = (GgafDxGeometricActor*)prm_pOtherActor;
//    if (UTIL::calcEnemyStamina(this, pOther) <= 0) {
//        setHitAble(false);
//        //��������
//        UTIL::activateExplosionEffectOf(this);
//        _pSeTx->play3D(SE_EXPLOSION);
//
//        //���@���Ɍ�����ď��ł̏ꍇ�A
//        if (pOther->getKind() & KIND_MY) {
//            //�A�C�e���o��
//            UTIL::activateItemOf(this);
//        }
//        sayonara();
//    } else {
//        //��j��
//        effectFlush(2); //�t���b�V��
//        _pSeTx->play3D(SE_DAMAGED);
//    }
}


EnemyErmioneArmHead::~EnemyErmioneArmHead() {
//    pDepoConnection_->close();
}
