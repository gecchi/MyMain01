#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

EnemyMassaliaFragment3::EnemyMassaliaFragment3(const char* prm_name) :
        EnemyMassaliaBase(prm_name, "Massalia", STATUS(EnemyMassaliaFragment3)) {
}

void EnemyMassaliaFragment3::onCreateModel() {
}

void EnemyMassaliaFragment3::initialize() {
    setHitAble(true);
    setScaleR(0.04);
    _pColliChecker->makeCollision(1);
    _pColliChecker->setColliSphere(0, PX_C(20));
    _pKurokoA->setFaceAngVelo(D_ANG(0), D_ANG(10), D_ANG(0));
}

void EnemyMassaliaFragment3::onActive() {
    //ステータスリセット
    UTIL::resetEnemyMassaliaFragment3Status(_pStatus);
    setHitAble(true);
}


void EnemyMassaliaFragment3::onInactive() {
    sayonara();
}
void EnemyMassaliaFragment3::processStaminaEnd(GgafDxGeometricActor* prm_pOther) {
    //自機側に撃たれて消滅の場合、
    if (prm_pOther->getKind() & KIND_MY) {
        //アイテム出現
        Item* pItem = UTIL::activateItem(_pStatus);
        if (pItem) {
            pItem->locateWith(this);
        }
    }
}

EnemyMassaliaFragment3::~EnemyMassaliaFragment3() {
}
