#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;


EnemyHermioneArmWeak::EnemyHermioneArmWeak(const char* prm_name) :
        EnemyHermioneArm(prm_name, "HermioneArmWeak", STATUS(EnemyHermioneArmWeak)) {
    _class_name = "EnemyHermioneArmWeak";
}

void EnemyHermioneArmWeak::onCreateModel() {
}

void EnemyHermioneArmWeak::initialize() {
    EnemyHermioneArm::initialize();
    _pColliChecker->makeCollision(1);
    _pColliChecker->setColliAAB_Cube(0, 40000);
}

void EnemyHermioneArmWeak::onHit(GgafActor* prm_pOtherActor) {
    GgafDxGeometricActor* pOther = (GgafDxGeometricActor*)prm_pOtherActor;
    if (UTIL::calcEnemyStamina(this, pOther) <= 0) {
        setHitAble(false);
        //��������
        UTIL::activateExplosionEffectOf(this);
        _pSeTxer->play3D(SE_EXPLOSION);

        //���@���Ɍ�����ď��ł̏ꍇ�A
        if (pOther->getKind() & KIND_MY) {
            //�A�C�e���o��
            UTIL::activateItemOf(this);
        }

        if (getParent()) {
            getParent()->throwEventUpperTree(EVENT_HERMIONE_SAYONARA);
        }
        if (getSubFirst()) {
            getSubFirst()->throwEventLowerTree(EVENT_HERMIONE_SAYONARA);
        }

        sayonara();
    } else {
        //��j��
        effectFlush(2); //�t���b�V��
        UTIL::activateExplosionEffectOf(this);
        _pSeTxer->play3D(SE_DAMAGED);
    }
}


EnemyHermioneArmWeak::~EnemyHermioneArmWeak() {

}
