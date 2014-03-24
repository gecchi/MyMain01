#include "stdafx.h"
#include "EnemyEmiliaFragment3.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxSeTransmitterForActor.h"
#include "jp/ggaf/lib/util/CollisionChecker3D.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

EnemyEmiliaFragment3::EnemyEmiliaFragment3(const char* prm_name) :
        EnemyEmiliaBase(prm_name, "Emilia", STATUS(EnemyEmiliaFragment3)) {
}

void EnemyEmiliaFragment3::onCreateModel() {
}

void EnemyEmiliaFragment3::initialize() {
    setHitAble(true);
    setScaleR(0.04);
    CollisionChecker3D* pColliChecker = getCollisionChecker();
    pColliChecker->makeCollision(1);
    pColliChecker->setColliSphere(0, PX_C(20));
    getKuroko()->setFaceAngVelo(D_ANG(0), D_ANG(10), D_ANG(0));
}

void EnemyEmiliaFragment3::onActive() {
    //ステータスリセット
    UTIL::resetEnemyEmiliaFragment3Status(getStatus());
    setHitAble(true);
}


void EnemyEmiliaFragment3::onInactive() {
    sayonara();
}
void EnemyEmiliaFragment3::processStaminaEnd(GgafDxGeometricActor* prm_pOther) {
    //自機側に撃たれて消滅の場合、
    if (prm_pOther->getKind() & KIND_MY) {
        //アイテム出現
        UTIL::activateItemOf(this);
    }
}

EnemyEmiliaFragment3::~EnemyEmiliaFragment3() {
}
