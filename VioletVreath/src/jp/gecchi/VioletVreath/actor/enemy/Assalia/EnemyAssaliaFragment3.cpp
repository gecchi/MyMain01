#include "stdafx.h"
#include "EnemyAssaliaFragment3.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoA.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxSeTransmitterForActor.h"
#include "jp/ggaf/lib/util/CollisionChecker3D.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

EnemyAssaliaFragment3::EnemyAssaliaFragment3(const char* prm_name) :
        EnemyAssaliaBase(prm_name, "Assalia", STATUS(EnemyAssaliaFragment3)) {
}

void EnemyAssaliaFragment3::onCreateModel() {
}

void EnemyAssaliaFragment3::initialize() {
    setHitAble(true);
    setScaleR(0.04);
    _pColliChecker->makeCollision(1);
    _pColliChecker->setColliSphere(0, PX_C(20));
    _pKurokoA->setFaceAngVelo(D_ANG(0), D_ANG(10), D_ANG(0));
}

void EnemyAssaliaFragment3::onActive() {
    //ステータスリセット
    UTIL::resetEnemyAssaliaFragment3Status(_pStatus);
    setHitAble(true);
}


void EnemyAssaliaFragment3::onInactive() {
    sayonara();
}
void EnemyAssaliaFragment3::processStaminaEnd(GgafDxGeometricActor* prm_pOther) {
    //自機側に撃たれて消滅の場合、
    if (prm_pOther->getKind() & KIND_MY) {
        //アイテム出現
        UTIL::activateItemOf(this);
    }
}

EnemyAssaliaFragment3::~EnemyAssaliaFragment3() {
}
