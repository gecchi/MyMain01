#include "stdafx.h"
#include "EnemyHermioneArmWeak.h"
#include "EnemyHermione.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxSeTransmitterForActor.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoA.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/ggaf/lib/util/CollisionChecker3D.h"

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
        //破壊時
        _pSeTx->play3D(SE_EXPLOSION);

        //腕のみ爆発
        if (getParent()) {
            getParent()->throwEventUpperTree(EVENT_HERMIONE_SAYONARA);
        }
        if (getSubFirst()) {
            getSubFirst()->throwEventLowerTree(EVENT_HERMIONE_SAYONARA);
        }
        //↑本体(EnemyHermione) に EVENT_HERMIONE_SAYONARA のイベント処理は無いので
        //この処理で、腕のみ爆発となる。
    } else {
        //非破壊時
        _pSeTx->play3D(SE_DAMAGED);
    }
}


EnemyHermioneArmWeak::~EnemyHermioneArmWeak() {

}
