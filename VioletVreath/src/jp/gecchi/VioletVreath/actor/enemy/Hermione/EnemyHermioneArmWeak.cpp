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
        //爆発効果
        UTIL::activateExplosionEffectOf(this);
        _pSeTxer->play3D(SE_EXPLOSION);

        //自機側に撃たれて消滅の場合、
        if (pOther->getKind() & KIND_MY) {
            //アイテム出現
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
        //非破壊時
        effectFlush(2); //フラッシュ
        UTIL::activateExplosionEffectOf(this);
        _pSeTxer->play3D(SE_DAMAGED);
    }
}


EnemyHermioneArmWeak::~EnemyHermioneArmWeak() {

}
