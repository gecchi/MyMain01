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
        //破壊された時(スタミナ <= 0)
        getSeTx()->play3D(SE_EXPLOSION);
        sayonara();
        //腕のみ爆発
        if (getParent()) {
            getParent()->throwEventUpperTree(EVENT_ERMIONE_SAYONARA);
        }
        if (getSubFirst()) {
            getSubFirst()->throwEventLowerTree(EVENT_ERMIONE_SAYONARA);
        }
        //↑本体(EnemyErmione) に EVENT_ERMIONE_SAYONARA のイベント処理は無いので
        //この処理で、腕のみ爆発となる。
    } else {
        //破壊されなかった時(スタミナ > 0)
        getSeTx()->play3D(SE_DAMAGED);
    }
}

EnemyErmioneArmWeak::~EnemyErmioneArmWeak() {

}
