#include "EnemyErmioneArmWeak.h"

#include "EnemyErmione.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxSeTransmitterForActor.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/ggaf/lib/util/CollisionChecker3D.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

EnemyErmioneArmWeak::EnemyErmioneArmWeak(const char* prm_name) :
        EnemyErmioneArm(prm_name, "ErmioneArmWeak", STATUS(EnemyErmioneArmWeak)) {
    _class_name = "EnemyErmioneArmWeak";
}

void EnemyErmioneArmWeak::onCreateModel() {
}

void EnemyErmioneArmWeak::initialize() {
    EnemyErmioneArm::initialize();
    CollisionChecker3D* pChecker = getCollisionChecker();
    pChecker->makeCollision(1);
    pChecker->setColliAAB_Cube(0, 40000);
}

void EnemyErmioneArmWeak::onHit(GgafActor* prm_pOtherActor) {
    const bool was_destroyed = UTIL::transactEnemyHit(this, (GgafDxGeometricActor*)prm_pOtherActor);
    if (was_destroyed) {
        //�j�󂳂ꂽ��(�X�^�~�i <= 0)
        getSeTx()->play3D(SE_EXPLOSION);
        sayonara();
        //�r�̂ݔ���
        if (getParent()) {
            getParent()->throwEventUpperTree(EVENT_ERMIONE_SAYONARA);
        }
        if (getSubFirst()) {
            getSubFirst()->throwEventLowerTree(EVENT_ERMIONE_SAYONARA);
        }
        //���{��(EnemyErmione) �� EVENT_ERMIONE_SAYONARA �̃C�x���g�����͖����̂�
        //���̏����ŁA�r�̂ݔ����ƂȂ�B
    } else {
        //�j�󂳂�Ȃ�������(�X�^�~�i > 0)
        getSeTx()->play3D(SE_DAMAGED);
    }
}

EnemyErmioneArmWeak::~EnemyErmioneArmWeak() {

}
