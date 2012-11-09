#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;


EnemyHermioneArmBody::EnemyHermioneArmBody(const char* prm_name) :
        EnemyHermioneArm(prm_name, "HermioneArmBody", STATUS(EnemyHermioneArmBody)) {
    _class_name = "EnemyHermioneArmBody";
}

void EnemyHermioneArmBody::onCreateModel() {
}

void EnemyHermioneArmBody::initialize() {
    EnemyHermioneArm::initialize();
    _pColliChecker->makeCollision(1);
    _pColliChecker->setColliAAB_Cube(0, 40000);
}


void EnemyHermioneArmBody::onHit(GgafActor* prm_pOtherActor) {
    GgafDxGeometricActor* pOther = (GgafDxGeometricActor*)prm_pOtherActor;
//
//    if (UTIL::calcEnemyStamina(this, pOther) <= 0) {
//        setHitAble(false);
//        //��������
//        UTIL::activateExplosionEffectOf(this);
//        _pSeTxer->play3D(SE_EXPLOSION);
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
//        _pSeTxer->play3D(SE_DAMAGED);
//    }
}


EnemyHermioneArmBody::~EnemyHermioneArmBody() {

}
