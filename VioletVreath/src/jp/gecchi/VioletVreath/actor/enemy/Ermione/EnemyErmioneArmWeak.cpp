#include "EnemyErmioneArmWeak.h"

#include "EnemyErmione.h"
#include "jp/ggaf/dx/actor/supporter/SeTransmitterForActor.h"
#include "jp/ggaf/dx/actor/supporter/LocoVehicle.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/ggaf/lib/util/WorldCollisionChecker.h"



using namespace GgafLib;
using namespace VioletVreath;

EnemyErmioneArmWeak::EnemyErmioneArmWeak(const char* prm_name) :
        EnemyErmioneArm(prm_name, "ErmioneArmWeak", StatusReset(EnemyErmioneArmWeak)) {
    _class_name = "EnemyErmioneArmWeak";
}

void EnemyErmioneArmWeak::onCreateModel() {
}

void EnemyErmioneArmWeak::initialize() {
    EnemyErmioneArm::initialize();
    WorldCollisionChecker* pChecker = getWorldCollisionChecker();
    pChecker->addCollisionArea(1);
    pChecker->setColliAACube(0, 40000);
}

void EnemyErmioneArmWeak::onHit(const GgafCore::Actor* prm_pOtherActor) {
    bool was_destroyed = UTIL::performEnemyHit(this, (const GgafDx::GeometricActor*)prm_pOtherActor);
    if (was_destroyed) {
        //�j�󂳂ꂽ��(�X�^�~�i <= 0)
        getSeTransmitter()->play3D(SE_EXPLOSION);
        sayonara();
        //�r�̂ݔ���
        if (getParent()) {
            getParent()->throwEventUpperTree(EVENT_ERMIONE_SAYONARA);
        }
        if (getChildFirst()) {
            getChildFirst()->throwEventLowerTree(EVENT_ERMIONE_SAYONARA);
        }
        //���{��(EnemyErmione) �� EVENT_ERMIONE_SAYONARA �̃C�x���g�����͖����̂�
        //���̏����ŁA�r�̂ݔ����ƂȂ�B
    } else {
        //�j�󂳂�Ȃ�������(�X�^�~�i > 0)
        getSeTransmitter()->play3D(SE_DAMAGED);
    }
}

EnemyErmioneArmWeak::~EnemyErmioneArmWeak() {

}
