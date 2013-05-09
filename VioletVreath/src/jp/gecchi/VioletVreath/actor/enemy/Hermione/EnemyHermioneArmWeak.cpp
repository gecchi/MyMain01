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

    bool was_destroyed = UTIL::proceedEnemyHit(this, (GgafDxGeometricActor*)prm_pOtherActor);
    if (was_destroyed) {
        //�j��
        _pSeTx->play3D(SE_EXPLOSION);

        //�r�̂ݔ���
        if (getParent()) {
            getParent()->throwEventUpperTree(EVENT_HERMIONE_SAYONARA);
        }
        if (getSubFirst()) {
            getSubFirst()->throwEventLowerTree(EVENT_HERMIONE_SAYONARA);
        }
        //���{��(EnemyHermione) �� EVENT_HERMIONE_SAYONARA �̃C�x���g�����͖����̂�
        //���̏����ŁA�r�̂ݔ����ƂȂ�B
    } else {
        //��j��
        _pSeTx->play3D(SE_DAMAGED);
    }
}


EnemyHermioneArmWeak::~EnemyHermioneArmWeak() {

}
