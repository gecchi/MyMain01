#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

EnemyMassaliaFragment::EnemyMassaliaFragment(const char* prm_name) :
        EnemyMassaliaBase(prm_name, "Massalia", STATUS(EnemyMassaliaFragment)) {
}

void EnemyMassaliaFragment::onCreateModel() {
}

void EnemyMassaliaFragment::initialize() {
    setHitAble(true);
    setScaleR(0.3);
    _pColliChecker->makeCollision(1);
    _pColliChecker->setColliSphere(0, PX_C(50));
    _pKurokoA->setFaceAngVelo(D_ANG(0), D_ANG(10), D_ANG(0));
}

void EnemyMassaliaFragment::onActive() {
    //ステータスリセット
    UTIL::resetEnemyMassaliaFragmentStatus(_pStatus);
    setHitAble(true);
}

void EnemyMassaliaFragment::onInactive() {
    sayonara();
}
void EnemyMassaliaFragment::processStaminaEnd(GgafDxGeometricActor* prm_pOther) {
    appearFragment("DpCon_MassaliaFragment2");
}

EnemyMassaliaFragment::~EnemyMassaliaFragment() {
}
